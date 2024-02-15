#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main(void)
{
	printf("%s\n",mysql_get_client_info());
	return 0 ;
}
