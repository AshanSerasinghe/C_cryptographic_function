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
            printf("%s\n", call);
        }
        else
        {
            call = encode(N,input);
            call = encrypt(N*8,k-1,call); // N is length of the msg
                                          // then N*8 is the length of the bitq
            printf("%s\n", call);
        }
       
	    
        
    }
    else if (form == 'C'){
        scanf("%i%i%i",&N,&L,&k);  // N = lenth of the original msg
        scanf(" %[^\n]%*c",input); // L = length of the bit sequence

        if (k==0)
        {
            call = decode(N*8, input);
            printf("%s\n",call);
        }
        else
        {
            call = decrypt(L, k-1, input); // k-1 , to adjest the output 
            call = decode(N*8, call); // N is the length of the msg. 
            
            printf("%s\n", call );
        }    
    }
    
    return 0;    
}
/*......................@@@@@@@@@@@@@@@@@@@@@@@@@@................*/




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




