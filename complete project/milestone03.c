#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int number_of_parity(int m);
char *paritybitsq(char *bitsq);
char parityfinder(char *array, int k);

char paritysearch(char * bitsq, int k);
char * errorfinder(char *bitsq);
int bitsqTOnum(char *array);

/*THIS FUNCTION FIND THE NUMBER OF PARITY BITS*/
int number_of_parity(int m)
{
	int r = 0;
	while(pow(2,r)<r+m+1) {   r++;  } // the equation 2^p >= p + d + 1 was used to find r
	return r;
}
/* THIS FUNCRION RETURN THE FINAL PARITY BIT SEQUENCE*/
char *paritybitsq(char *bitsq)
{
	static char modbitsq[10000] = {'P'};
	int i = 0, j = 2,l = 0, r = number_of_parity(strlen(bitsq));
	char pbit;
	
	while(j<strlen(bitsq) + r + 1)
	{
		if (pow(2,(int)log2(j)) == j)
		{
			modbitsq[j-1] = 'P';  // append char P insted of grabage values 
		}
		else
		{
			modbitsq[j-1] = bitsq[l]; // take the given array 
			l++;
		}
		j++; 
	}
	modbitsq[j-1]='\0';

	
	while (i<r)
	{     
		modbitsq[(int)pow(2,i)-1] = parityfinder(modbitsq,pow(2,i));    i++; // append parity to final array	   
	}
	
	return modbitsq;  // return final array 
}
/*THIS FUNCTION RETURN THE PARITY BIT OF GIVEN POSSITHON*/
char parityfinder(char *array ,int k)
{
	int i = 0, j = k+1,ans , p = 0;  
	
	while (i<strlen(array) - k+1   && j<strlen(array)+1+1)
	{
		ans = 0;
		while(ans == 0 && j<strlen(array)+1+1 ) // 1+1 to get an aditional index
		{
			ans = j&(1<<( (int)log2(k) ) );     j++; // shift int 1 to get the required value	
		}
		
		p = p + (int)(array[j-2] - 48 );  // take the addition of corrousponding elements
		
		i++;
	}
	p = p - (int)(array[j-2] -48); // drop the aditional index 
	
	return (char)(p%2+48);
}


/*................ ####################  ...............*/


char paritysearch(char * array, int k)
{
	int i = 0, j = k,ans , p = 0;  
	
	while (i< (strlen(array) - k+1+1)  && j<strlen(array)+1+1)
	{
		ans = 0;
		while(ans == 0 && j<strlen(array)+1+1) // 1+1 to get an aditional index
		{
			ans = j&(1<<( (int)log2(k) ) );     j++; // shift int 1 to get the required value	
		}
		//printf("%i\n",j-1);
		p = p + (int)(array[j-2] - 48 );  // take the addition of corrousponding elements
		i++;
		//printf("%i\n",p);
	}
	p = p - (int)(array[j-2] -48); // drop the aditional index 
	
	
	return (char)(p%2+48);
}

char * errorfinder(char *bitsq)
{
	int r = number_of_parity(strlen(bitsq)), i = 0, pnum = 0, j = 3,j2 = 0;
	char position[32];
	static char correctedbitsq[10000];
	while(r>0)
	{
		position[i] = paritysearch(bitsq,pow(2,r-1));  
		r--; i++;
		
	}
	position[i]='\0';
	
	pnum = bitsqTOnum(position);
	
	if (pnum)
	{
		bitsq[pnum-1] = (char)( ( (int)bitsq[pnum-1] ^ (int)'1' ) + 48 ); // flip the bit of REAL bitsq #not a copy#
		printf("Error detected and corrected!\n");
	}
	
	while(j<strlen(bitsq)+1 )
	{
		if ( pow(2,(int)log2(j)) != j )
		{
			correctedbitsq[j2] = bitsq[j-1]; 
			j2++;
		}
		j++; 
	}
	correctedbitsq[j2] = '\0';
	
	return correctedbitsq;	
}


/*THIS FUNCTION CONVERTS A GIVEN BINARY ARRAY TO ITS EQUIVALANT DECIMEL VALUE*/
int bitsqTOnum(char *array)
{
	int sum = 0, i;
	for(i=0;i<strlen(array);i++)
	{   sum += (int)(array[i] - 48) * pow(2, strlen(array) - i -1);  } 
		 
	return sum;
}



