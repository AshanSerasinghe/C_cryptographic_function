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
