#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{

	FILE * fd;

	char Name[32] = "\0";
	char Gender[10] = "\0";
	char Stuid[32] = "\0";
	char Birthday[20] ="\0";
	char Address[30] ="\0";
	char Score[30]="\0";
	char Cname[30]="\0";
	char Credit[30]="\0";
	int status = 0;
	char ch;

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);

	status = cgiFormString("Name",Name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Name error!\n");
		return 1;
	}

	status = cgiFormString("Gender",Gender, 10);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Gender error!\n");
		return 1;
	}

	status = cgiFormString("Stuid",Stuid, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Stu_id error!\n");
		return 1;
	}
	status = cgiFormString("Address",Address, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Address error!\n");
		return 1;
	}
	status = cgiFormString("Birthday",Birthday, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Birthday error!\n");
		return 1;
	}
	status = cgiFormString("Score",  Score, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Score error!\n");
		return 1;
	}
	status = cgiFormString("Cname",  Cname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cname error!\n");
		return 1;
	}
	status = cgiFormString("Credit",  Credit, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Credit error!\n");
		return 1;
	}


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	//int ret;
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







	sprintf(sql, "insert into Student(Stu_id,Name,Gender,Birthday,Address) values (%s, '%s', '%s','%s','%s')", Stuid, Name, Gender,Birthday,Address);
	sprintf(sql,"insert into Grade(Score) values('%s')",Score);
	sprintf(sql,"insert into Course(Cname,Credit) values('%s',‘%s’)",Cname,Credit);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
