#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

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

    sql = "CREATE TABLE COMPANY("
          "ID INT PRIMARY KEY     NOT NULL,"
          "NAME           TEXT    NOT NULL,"
          "AGE            INT     NOT NULL,"
          "ADDRESS        CHAR(50),"
          "SALARY         REAL );";
/****//*12346*/
    /* Execute SQL statement */
    ret = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db); //关闭数据库
    return 0;
}
/**//**//**/