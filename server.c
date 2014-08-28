#include "csapp.h"

char intToChar(int num){
	char c = num;
	return c;
}

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
		letter = intToChar(ascii);
		decrypted[i]=letter;
		token = strtok(NULL," ");
		i++;
	}
}

int main(int argc, char **argv){
	int listenfd, connfd, port, clientlen,e,c,d,dc;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;
	char* buf;
	buf = malloc(10000*sizeof(char));

	if (argc != 6) {
		fprintf(stderr, "usage: %s <port> <E> <C> <D> <DC>\n", argv[0]);
		exit(0);
	}	

	port = atoi(argv[1]);
	e = atoi(argv[2]);
	c = atoi(argv[3]);
	d = atoi(argv[4]);
	dc = atoi(argv[5]);

	listenfd = Open_listenfd(port);
	char input[300];
	char encrypted[10000];
	char decrypted[300];
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* Determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
	sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);

	do{
		Read(connfd,buf,1024);
		decrypt(buf,d,c,decrypted);
		printf("They wrote: %s\n",decrypted);
      printf("Type, enter .bye to quit\n");
		fgets(input,300,stdin);
		memset(decrypted,'\0',300);
		memset(encrypted,'\0',10000);
		encrypt(input,e,dc,encrypted);
		Write(connfd, encrypted, strlen(encrypted));
		printf("You wrote: %s\n",input);
	}while (strcmp(input,".bye\n")!=0);

	Close(connfd);
	
	free(buf);
	exit(0);
}
