#include "proto.h"

#define MOST_PROC_NR 30
#define MOST_FREE_NR 8
#define MIN_FREE_NR 5

#define NOTIFY_SIG SIGUSR1

enum
{
	STATE_FREE = 1, // accept() 阻塞
	STATE_BUSY		// accept() 返回
};

struct pool_st
{
	pid_t pid; // 子进程号
	int state;
};

static struct pool_st *pool = NULL;
static int free_cnt, busy_cnt;

static int add2pool(int sd);
static int del_from_pool(void);

static void user1_handler(int s)
{
	;
}

static int count_reg(reg_date_t *user_date);

int mian1(void)
{
	int sd;
	struct sockaddr_in laddr;
	struct sigaction act, oldact;
	struct sigaction act_usr1, oldact_usr1;
	sigset_t set, oldset;
	int f_cnt, b_cnt;
	int ret;

	// 进程池中子进程的状态
	pool = mmap(NULL, sizeof(struct pool_st) * MOST_PROC_NR, PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (MAP_FAILED == pool)
	{
		perror("mmap()");
		exit(1);
	}
	// 初始化进程池
	for (int i = 0; i < MOST_PROC_NR; i++)
	{
		pool[i].pid = -1;
		pool[i].state = STATE_FREE;
	}

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket()");
		goto ERROR1;
	}

	// 设置套接字选项，允许重复bind
	int val = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1)
	{
		perror("setsockopt()");
		goto ERROR2;
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(QQ_REG_SERVER_PORT);
	laddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1)
	{
		perror("bind()");
		goto ERROR2;
	}

	if (listen(sd, 200) == -1)
	{
		perror("listen()");
		goto ERROR2;
	}

	// 使得进程池中的子进程终止时不变僵尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, &oldact);

	// 约定父子进程间发通知的信号
	act_usr1.sa_handler = user1_handler;
	act_usr1.sa_flags = 0;
	sigemptyset(&act_usr1.sa_mask);
	sigaction(NOTIFY_SIG, &act_usr1, &oldact_usr1);

	// 向进程池中添加任务子进程
	for (int i = 0; i < MIN_FREE_NR; i++)
	{
		if ((ret = add2pool(sd)) != 0)
		{
			fprintf(stderr, "add2pool():%s\n", strerror(ret));
			goto ERROR3;
		}
	}

	// 信号集
	sigemptyset(&set);
	sigaddset(&set, NOTIFY_SIG);
	sigprocmask(SIG_BLOCK, &set, &oldset);
	// 管理进程池
	while (1)
	{
		sigsuspend(&oldset);
		// 遍历进程池
		f_cnt = 0;
		b_cnt = 0;
		for (int i = 0; i < MOST_PROC_NR; i++)
		{
			if (pool[i].pid == -1)
				continue;
			if (pool[i].state == STATE_FREE)
				f_cnt++;
			else if (pool[i].state == STATE_BUSY)
				b_cnt++;
		}
		free_cnt = f_cnt;
		busy_cnt = b_cnt;
		if (free_cnt < MIN_FREE_NR)
		{
			if ((ret = add2pool(sd)) != 0)
			{
				fprintf(stderr, "add2pool():%s\n", strerror(ret));
				goto ERROR3;
			}
		}

		if (free_cnt > MOST_FREE_NR)
		{
			for (int i = 0; i < free_cnt - MOST_FREE_NR; i++)
			{
				del_from_pool();
			}
		}

		// 调试
		for (int i = 0; i < MOST_PROC_NR; i++)
		{
			if (pool[i].pid > 0 && pool[i].state == STATE_FREE)
				putchar('F');
			else if (pool[i].pid > 0 && pool[i].state == STATE_BUSY)
				putchar('B');
			else
				putchar('-');
		}
		putchar('\n');
	}

	exit(0);
ERROR3:
	sigaction(SIGCHLD, &oldact, NULL);
ERROR2:
	close(sd);
ERROR1:
	munmap(pool, sizeof(struct pool_st) * MOST_PROC_NR);
	exit(1);
}

static int add2pool(int sd)
{
	pid_t pid;
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	int i;
	char buf[MAX_LEN] = {};
	int newsd;

	if (busy_cnt + free_cnt >= MOST_PROC_NR)
		return ENOSPC;

	pid = fork();
	if (pid == -1)
	{
		return errno;
	}
	if (pid == 0)
	{
		// child
		for (i = 0; i < MOST_PROC_NR; i++)
		{
			if (pool[i].pid == -1)
			{
				pool[i].pid = getpid();
				break;
			}
		}
		raddrlen = sizeof(raddr);
		while (1)
		{
			pool[i].state = STATE_FREE;
			// sig--->parent
			kill(getppid(), NOTIFY_SIG);
			newsd = accept(sd, (void *)&raddr, &raddrlen);
			if (newsd == -1)
			{
				return errno;
			}
			pool[i].state = STATE_BUSY;
			kill(getppid(), NOTIFY_SIG);

			printf("accept client request ip:%s, port:%d\n", inet_ntoa(raddr.sin_addr),ntohs(raddr.sin_port));
			/*向数据库添加新账号信息*/

			close(newsd);
		}
	}

	return 0;
}
/*向用户信息表中添加新用户信息*/
static int count_reg(reg_date_t *user_date)
{
	int cnt;
	sqlite3 *QQ_db=NULL;
	sqlite3_stmt *stmt=NULL;
	int ret;
	char sql[128]={};
	char *errmsg=NULL;
	int id;
	int flg=0;	

	/*打开数据库*/
	if(sqlite3_open("./QQ.db",&QQ_db)!=SQLITE_OK)
	{
		fprintf(stderr,"sqlite_open() failed\n");
		return 1;
	}
/*	//如果没有创建用户信息表则创建
	sql="creat table if not exists QQ_reg(\
	id integer primary key autoincrement,\
	name text not null,\
	count integer not null,\
	pwd text not null);";
*/
	if (sqlite3_exec(QQ_db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_exec() failed: %s\n", errmsg);
		goto ERROR;
	}

	/*随机生成账号*/
	/*查询表中是否有此账号*/
	srand(time(NULL));	
	do
	{
		cnt=rand()%30000+10000;    //生成随机账号
		sprintf(sql,"select * from QQ_reg where count=%d;",cnt);  //生成账号查询语句
		sqlite3_prepare_v2(QQ_db, sql, -1, &stmt, NULL); 
		
	} while (sqlite3_step(stmt)==SQLITE_OK);	
	/*生成的账号写入用户账号*/
	snprintf(user_date->count, CNT_SIZE,"%d", cnt);

	/*向表中添加用户信息*/
	sprintf(sql,"insert into register(name, count, pwd) values('%s', '%s', '%s');",user_date->name, user_date->count, user_date->pwd);
	if (sqlite3_exec(QQ_db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_exec() failed: %s\n", errmsg);
		goto ERROR;
	}

	sqlite3_close(QQ_db);
	return 0;
	
	ERROR:
		return 1; 
}

/*删除进程池*/
static int del_from_pool(void)
{
	int i;

	for (i = 0; i < MOST_PROC_NR; i++)
	{
		if (pool[i].pid > 0 && pool[i].state == STATE_FREE)
		{
			kill(pool[i].pid, SIGTERM);
			pool[i].pid = -1;
			break;
		}
	}
	return 0;
}
