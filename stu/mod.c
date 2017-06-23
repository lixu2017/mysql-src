#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char Name[32] = "\0";
	char Gender[10] = "\0";
	char Stu_id[32] = "\0";
	char Birthday[20] ="\0";
	char Address[30] ="\0";
	int status = 0;

	status = cgiFormString("Name",  Name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Name error!\n");
		return 1;
	}

	status = cgiFormString("Gender",  Gender, 10);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Gender error!\n");
		return 1;
	}

	status = cgiFormString("Stu_id",  Stu_id, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Stu_id error!\n");
		return 1;
	}
	status = cgiFormString("Address",  Address, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Address error!\n");
		return 1;
	}
	status = cgiFormString("Birthday",  Birthday, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Birthday error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "1", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	//sprintf(sql,"update Student set Name='%s', Address= '%s',Gender=‘%s’,Birthday='%s' where Stu_id = %d ",Name,Address,Gender,Birthday,atoi(Stu_id));
	sprintf(sql,"update Student set Name = '%s',Address = '%s',Gender = '%s', Birthday = '%s' where Stu_id = '%s'",Name,Address,Gender,Birthday,Stu_id);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
};
