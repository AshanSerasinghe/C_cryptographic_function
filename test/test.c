#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//char* function(char* t);
int main()
{
	int x = 10;
	int *p;
	p = &x;
	char xx[100] = "azxzfff";
	char *c;
	
	printf("%X\n",xx);
	//c = function(xx);
	//printf("%c\n",c[1]);
	//free(c);
	
	
	/*
	char x = 'A' , y[10] = "abcxx";
	printf("%d\n",strlen(y));
	
	float i = 4.5;
	printf("%f",ceil(i));
	*/
	
	printf("%d\n",printf("%d\n",sizeof(long)));   
	exit(2);
	
	return 0;
}
/*
char* function(char* t)
{
	//static char yy[10];
	char* yy = (char*)malloc(sizeof(char)*10);
	yy[0]= t[0];
	yy[1]= t[2];
	//*t = *t+4;
	//printf("%c\n",*t);
	return yy;
}
*/
