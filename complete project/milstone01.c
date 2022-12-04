#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * binTOchar(char *array);
char *decode (int l,char *bitsq);
char *charTObin(char ch);
char *encode(int n,char *msg);


/* $$$$$$$$$$$$   ENCODING  $$$$$$$$$$$$$$$$*/
char *encode(int n,char *msg)
{
    static char binArray[10000];
    int i=0;
	//take characters one by one
    while(i<n)
    {
        strcat(binArray,charTObin(msg[i]));
        i++;
    }
return binArray; //return made binary array
}

//convert charater to binary 
char *charTObin(char ch)
{
    static char bin[8];
	int i = 7,j=0;
	
	while (i>=0)
	{
		if (ch&((1<<i))){  bin[j] = '1';  }
		else{   bin[j] = '0';  }
		i--;  j++;	
	}
	bin[j]='\0';
	
    return bin;
}

/*$$$$$$$$$$$$$$   DECODING    $$$$$$$$$$$$$$$$$$*/
char *decode (int l,char *bitsq)  
{
	int i=0,j,k=0;
	char part[8];
	static char msg[1000];
	
	while(i<l/8)
	{
		j = 0;
		while (j<8)
		{
			part[j]=bitsq[k];
			j++;k++;
		}
		part[j]='\0';
		strcat(msg,binTOchar(part));
		
		i++;	
	}
	
	return msg;
}

//convert give binary array to its corrousponding charater
char * binTOchar(char *array)
{
	int i = 0,num=0;
	static char ch[2];
	while(i<8)
	{
		num = num + (array[i]-48)*pow(2,(7-i));
		i++;
	}
	
	ch[0] = num;
	ch[1] = '\0';
	return ch;
}


