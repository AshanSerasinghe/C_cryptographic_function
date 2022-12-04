#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int XOR(int a,int b);
char *takin_xor(int size, int times, char *encripted, char *bitsq);
char * encrypt(int n, int k, char *bitsq);
char* decrypt(int l, int k, char* encryptedBitsq); 

int colum_xor(char array[1000][1000],int column,int ro, int shift, char bitsqBit);
char* decrypt(int l, int k, char* encryptedBitsq);


char* decrypt(int l, int k, char* encryptedBitsq)
{
	char result[1000][1000];
	static char last_row[10000];
	
	int i, j,col,n,dummy ,call, col_shift = 1;

	i = 0;
	
	//printf("%i\n",55); //////////////////////////////

	while(i<k+1) // k+1 tp complete last row
	{
		result[i][0] = encryptedBitsq[0];
		i++;
	}
	
	col = 1;
	while(col<l-k) // k+1 due to col is 1
	{
		if( col == 1)
		{
			call = XOR( encryptedBitsq[1] , result[1][0] );
			dummy = 1;
		}
		else if( col < k+1) 
		{
			call = colum_xor(result, (col-col_shift), col , k,  encryptedBitsq[col]);
			dummy = col;
		}
		else
		{
			call = colum_xor(result, (col-k) , dummy , k,  encryptedBitsq[col]);
		}
		
		j = 0;
		while(j<k+1)// k+1 to fill the last column
		{
			result[j][col] = call;
			j++; 
		}
		
		col++; col_shift++;
	}
	
	n = 0;
	while(n<l-k)
	{
		last_row[n] = result[0][n];
		n++;
	}
	last_row[n] = '\0';
	
	
	return last_row;
}



int colum_xor(char array[1000][1000],int column,int ro, int shift, char bitsqBit)
{
	int j,k;
	
	if (shift == 1)
	{
		k = array[ro][column];////////////////////////
	}
	else
	{
		k = XOR( array[ro][column]  ,  array[ro-1][column+1] ); 
	}
	
	j = 1;
	while(ro-2> 0)
	{
		k = XOR( k ,  array[ro-2][column+1+j] );
		ro--; j++;
	}
		
	k = XOR(k , bitsqBit);
	
	
	return k;
}









/* THIS FUNCTION ENCRYPTS GIVEN BIT SEQUENCE*/
char * encrypt(int n, int k, char *bitsq)
{
	char *x;
	int i = 0;
	
	x = takin_xor( n ,1,bitsq,bitsq); // zetoth shift 
	
	while(i<k-1)
	{
		x = takin_xor( n , i+2 ,x ,bitsq); // takes first shift onwords 
		i++;
	}
	//printf("%i\n",strlen(x));
	return x;
}

/* THIS FUNCTION TAKE THE BITWISE XOR BETWEEN GIVEN TWO BIT SEQUENCES */
char *takin_xor(int size, int times, char *encripted, char *bitsq)
{
	//char *result = malloc(sizeof(char)*(size+3));
	static char result[100000]; 
	int i=0, j=0;
	
	while(i<times)
	{
		result[i] = encripted[i];
		i++;
	}
	
	while (j<size-1)
	{
		result[i] = XOR(encripted[i] , bitsq[j]);
		i++; j++;
	}
	result[i] = bitsq[j]; // 
	result[i+1] = '\0';
	
	return result;
}


/* THIS FUNCTION TAKES LOGICAL XOR OF GIVEN INPUTS ( '0' and '1')*/
int XOR(int a,int b)
{
	int ans=0;
	
	a = a-48;  b = b-48;
	
	if (a+b == 2 || a+b == 0)
	{
		ans = 0;
	}
	else if(a+b == 1)
	{
		ans = 1;
	}
	
	return ans+48;
}






