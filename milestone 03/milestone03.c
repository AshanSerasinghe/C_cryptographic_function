#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* prototypes of funcions used */

char *decode (int l,char *bitsq);
char * binTOchar(char *array);
char *charTObin(char ch);
char *encode(int n,char *msg);

int XOR(int a,int b);
char *takin_xor(int size, int times, char *encripted, char *bitsq);
char * encrypt(int n, int k, char *bitsq);
int colum_xor(char **array,int column,int ro,int shift, char bitsqBit);
char* decrypt(int l, int k,  char* encryptedBitsq);

int number_of_parity(int m);
char *paritybitsq(char *bitsq);
char parityfinder(char *array,int k);

char paritysearch(char * bitsq, int k);
int bitsqTOnum(char *array);
char * errorfinder(char *bitsq);

int main()
{
    char form, input[100000], *call;
    int N,k,L;
    scanf("%c",&form);

    if (form == 'P'){
        scanf("%i%i",&N,&k);
        scanf(" %[^\n]%*c",input);
        
        if(k==0)
        {
            call = encode(N,input);
            call = paritybitsq(call);
            printf("%s\n", call);
        }
        else
        {
            call = encode(N,input);
            call = encrypt(N*8,k-1,call); // N is length of the msg
                                          // then N*8 is the length of the bitq
            call = paritybitsq(call);
            printf("%s\n", call);
        }
       
	    
        
    }
    else if (form == 'C'){
        scanf("%i%i%i",&N,&L,&k);  // N = lenth of the original msg
        scanf(" %[^\n]%*c",input); // L = length of the bit sequence
		
        if (k==0)
        {
            call = errorfinder(input);
			call = decode(N*8, call);
            printf("%s\n",call);
        }
        else
        {
            call = errorfinder(input); // remove parity bits and correct the sequence
			call = decrypt(L, k-1, call); // k-1 , to adjest the output 
            call = decode(N*8, call); // N is the length of the msg. 
            
            printf("%s\n", call );
        }  
		
    }
    
    return 0;    
}
/*......................@@@@@@@@@@@@@@@@@@@@@@@@@@................*/



/* @@@@@@@@@@@@@@@@@@.............MILESTONE 03.............. @@@@@@@@@@@@@@@@@@@@@@*/

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
	int i = 0, j = 2,l = 0, r = number_of_parity(strlen(bitsq)); //take number of parity
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
	modbitsq[j-1]='\0'; // append the null character to end of the array 

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

/*THIS FUNCTION RETURNS ERROR VALUE E1 E2...  etc. */
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
		p = p + (int)(array[j-2] - 48 );  // take the addition of corrousponding elements
		i++;
	}
	p = p - (int)(array[j-2] -48); // drop the aditional index 
	
	return (char)(p%2+48);
}

/*THIS FUNCTION CORRECTS ANY ERROR IN BITSEQUENCE AND RETURNS A SEQUENCE WITHOUT PARITY*/
char * errorfinder(char *bitsq)
{
	int r = number_of_parity(strlen(bitsq)), i = 0, pnum = 0, j = 3,j2 = 0;
	char position[32];
	static char correctedbitsq[10000];
	while(r>0)
	{
		position[i] = paritysearch(bitsq,pow(2,r-1));   r--; i++;	// take the error position in bin form
	}
	position[i]='\0';
	
	pnum = bitsqTOnum(position); //get the error position as int 
	
	if (pnum)
	{
		bitsq[pnum-1] = (char)( ( (int)bitsq[pnum-1] ^ (int)'1' ) + 48 ); // flip the bit of REAL bitsq #not a copy#
		printf("Error detected and corrected!\n");
	}
	
	while(j<strlen(bitsq)+1 )
	{
		if ( pow(2,(int)log2(j)) != j )
		{
			correctedbitsq[j2] = bitsq[j-1]; j2++; // extract the bit sequence 	
		}
		j++; 
	}
	correctedbitsq[j2] = '\0';
	
	return correctedbitsq;	
}

/* THIS FUNCTION RETURNS THE DECIMAL VALUE OF GIVEN BIT SEQUENCE*/
int bitsqTOnum(char *array)
{
	int sum = 0, i = 0;
	while(i<strlen(array))
	{
		sum = sum + (int)(array[i]-48) * pow(2, strlen(array) - i -1);  
		i++;
	} 
	
	return sum;
}




/* ................@@@@@@@@@@@@@@@@@@@.........................*/


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@  MILSTONE 02   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/* THIS FUNCTION ENCRIPTS GIVEN BIT SEQUENCE*/
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

    return x;
}

/* THIS FUNCTION TAKE THE BITWISE XOR BETWEEN GIVEN TWO BIT SEQUENCES */
char *takin_xor(int size, int times, char *encripted, char *bitsq)
{
    //char *result = malloc(sizeof(char)*(size+3));
    static char result[1000000]; 
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
    result[i] = bitsq[j]; 
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




/*THE FUNCTION DECRYPT GIVEN ENCRYPTED BIT SEQUENCE */
char* decrypt(int l, int k, char* encryptedBitsq)
{
    // allocate memory for  2D array   
    char **result;
    int mem;

    result = (char**)malloc(sizeof(char*) * 10000);// <stdlib.h> for malloc

    for (mem = 0; mem < 10000; mem++)
    {
        result[mem] = (char*)malloc(sizeof(char) * 10000);
    }
               
    static char last_row[10000]; // return the last row of 2D array 
    
    int i, j,col,n,dummy ,call, col_shift = 1;

    i = 0;
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
            dummy = col; // make a dummy value for rows
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

    free(result); // free allocated 2D array
    return last_row;
}


/* THIS FUNCTION TAKES THE LOGICAL XOR OF GIVEN COLUMN OF A GIVEN 2D ARRAY */
int colum_xor(char **array,int column,int ro, int shift, char bitsqBit)
{
    int j,k;
    
    if (shift == 1)
    {
        k = array[ro][column]; // handle the shift = 1 case
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


/*......................@@@@@@@@@@@@@@@@@@@@@@@@@@2................*/




/*@@@@@@@@@@@@@@@@@@@@@@@@@@@  MILSTONE 01   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

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

/*....................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................... */




