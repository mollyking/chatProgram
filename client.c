#include "csapp.h"
#include <stdlib.h>
#include <stdio.h>
long modulo(long a, long b, long c){
	long result = 1;
	
	while(b >0){
		if((b & 1)==1){
			result = (result*a)%c;
		}
		a = (a*a) % c;
		b >>= 1;
	}
	return result;
}

long endecrypt(long msg, int key, int c){
	long keyI = (long)key;
	long cI = (long)c;
	return modulo(msg,keyI,cI);
}

char intToChar(int num){
	char c = num;
	return c;
}

void decrypt(char msg[], int d, int c, char decrypted[]){
	int i=0;
	long ascii;
	
	int temp;
	char *token;
	char letter;
	token = strtok(msg," ");
	while (token != NULL){
		temp = atoi(token);
		ascii = endecrypt(temp,d,c);
		ascii = (int) ascii;
		letter =	intToChar(ascii);
		decrypted[i]=letter;
		token = strtok(NULL," ");
		i++;
	}
}


int charToInt(char let){
	int num = (int)let;
	return num;
}

void encrypt(char msg[], int e, int c, char encrypted[]){
	int i=0, j=0;
	long ascii,temp;
	char test[10];
	while(msg[i]!=0){
		temp = (long)msg[i];
		ascii = endecrypt(temp,e,c);
		ascii = (int)ascii;
		sprintf(test,"%ld", ascii);
		strcat(encrypted,test);
		strcat(encrypted," ");
		i++;
	}
}

int main(int argc, char **argv)
{
	int clientfd, port,e,c,d,dc, writeToServer,readResponse;
	char *host, *buf;

	buf = malloc(10000*sizeof(char));
	if (argc != 7) {
		fprintf(stderr, "usage: %s <host> <port> <E> <C> <D> <DC>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = atoi(argv[2]);
	e = atoi(argv[3]);
	c = atoi(argv[4]);
	d = atoi(argv[5]);
	dc = atoi(argv[6]);
	
	clientfd = Open_clientfd(host, port);
	char input[300];
	char encrypted[10000];
   char decrypted[300];
	printf("Type, enter .bye to quit\n");
	fgets(input,300,stdin);
	while(strcmp(input,".bye\n")!=0){
//		decrypted[0]='\0';
		memset(decrypted,'\0',300);
		memset(encrypted,'\0',10000);
		encrypt(input,e,dc,encrypted);
		Write(clientfd,encrypted,strlen(encrypted));
		printf("You wrote: %s\n",input);
		Read(clientfd,buf,1024);
		decrypt(buf,d,c,decrypted);
		printf("They wrote: %s\n",decrypted);
   	printf("Type, enter .bye to quit\n");
		fgets(input,300,stdin);
	}
	Close(clientfd);
	exit(0);
}
