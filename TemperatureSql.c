#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
	//khoi tao ket noi toi MySQL
	MYSQL *con = mysql_init(NULL);
	if(con == NULL)
	{
		printf("Error connection to mysql \n");
		return -1;
	}
	//ket noi voi file database
		//host name: localhost
		//user name: pi
		//password: pi
		//database name : TempDB
	if(mysql_real_connect(con,"localhost","pi","pi","TempDB",0,NULL,0)== NULL)
	{
		printf("error connect to TempDB database \n");
		return -1;
	}
	// Tao 1 table ten la TempMeas
	if(mysql_query(con,"CREATE TABLE IF NOT EXISTS TempMeas(MeasTime DATETIME,temp DOUBLE)"))
	{
		printf("Error cannot create table \n");
		mysql_close(con);
		return -1;
	}
	//Khoi tao mysql statement de chuan bi ghi data
	MYSQL_STMT *stmt = mysql_stmt_init(con);
	if(stmt ==NULL)
	{
		printf("Error init stmt \n");
		mysql_close(con);
		return -1;
	}
	//thiet lap 1 cau query de ghi data
	const char * query="INSERT INTO TempMeas(MeasTime,Temp) VALUE(NOW(),?)";
	//chuan bi cau statemante
	if(mysql_stmt_prepare(stmt,query,strlen(query)))
	{
		printf("Error prepare stmt \n");
		mysql_close(con);
		return -1;
	}
	
	//Tao MYSQL bind structure de luu data du dinh insert vao mysql table
	double temp=0.0;
	MYSQL_BIND bind;
	memset(&bind,0,sizeof(bind));
	bind.buffer_type= MYSQL_TYPE_DOUBLE;
	bind.buffer= (char *) &temp;
	bind.length=sizeof(double);
	
	//Ket noi data structure vao MySQL statement
	if(mysql_stmt_bind_param(stmt,&bind))
	{
		
		printf("Error prepare stmt \n");
		mysql_close(con);
		return -1;
	}
	
	//ghi 10 record vao database
	for(int i=0; i<10 ; i++)
	{
		temp= (double)i;
		//excute data
		mysql_stmt_execute(stmt);
	}
	mysql_close(con);
	return 0; 	
}
