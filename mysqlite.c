#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "proto.h"
#include "mysqlite.h"

int creat_table(sqlite3 *db, char *table);

int main(int argc, char **argv)
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int ret;
    char *sql;

    //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
    ret = sqlite3_open("test.db", &db);
    if (ret)
    {
        fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    else
        printf("open DB test ok \r\n");
 

    creat_table(db,"test1");
    sqlite3_close(db); //关闭数据库
    return 0;
}

//创建表
int creat_table(sqlite3 *db, char *table)
{
    int ret=0;
    char sql[512]={0};
    char *errmsg=NULL;
    
    sprintf(sql, "create table if not exists %s (\
    id integer primary key, device_id integer, \
    device_addr text, temp interger, hum interger, \
    dp_temp interger, dip_fire integer, smog integer,\
    PM25 integer);", table);
	ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
 
	if(ret != SQLITE_OK)
	{
        #ifdef DEBUG
		    printf("create table error : %s\n",errmsg);
		#endif
        return ret;
	}
    #ifdef DEBUG
        printf("create table ok : %s\n",errmsg);
    #endif
    
    return ret;
}

//表中插入数据
int insert_data(sqlite3 *db, char *table, const DEVICE_DATA * device)
{
    int ret=0;
    char sql[512];
    char *errmsg=NULL;

   /*INSERT INTO TABLE_NAME [(column1, column2, column3,...columnN)]  
   VALUES (value1, value2, value3,...valueN);*/

    sprintf(sql, "INSERT INTO %s (device_id integer, \
    device_addr text, temp interger, hum interger, \
    dp_temp interger, dip_fire integer, smog integer,\
    PM25 integer), VALUES(%d, %s, %d, %d, %d, %d, %d, %d)", \
    device->device_name, device->device_id, device->temp, device->hum, device->dp_temp, device->dip_fire, device->smog, device->PM25);
    
    ret=sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    
    #ifdef DEBUG
        printf("insert err:%s\r\n", errmsg);
    #endif

    return ret;
}

//删除表中数据
int del_data(sqlite3 *db, char *table, DEVICE_DATA device)
{
    int ret=0;


    return ret;
}

//查询数据   condition查询条件  []=[]
int select_data(sqlite3 *db, char *table, char *condition, DEVICE_DATA *device_buf)
{
    int ret=0;
    char sql[128]={0};
    char *errmsg=NULL;

    sprintf(sql, "SELECT *FROM %s WHERE %s", table, condition);
    ret=sqlite3_exec(db, sql, sqlite_callback, device_buf, &errmsg);
    
    #ifdef DEBUG
        sprintf(stderr, "select err %s", errmsg);
    #endif

    return ret;
}

//回调函数
static int sqlite_callback(void* para, int columnCount, char** columnValue, char** columnName)
{
    int ret=0;
    int i=0;
    for (i = 0; i < columnCount; i++)
    {
        
    }
    

    return ret;
}

