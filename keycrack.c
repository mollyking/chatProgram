#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int gcd(int m, int n){
	if (m==0){
		return n;
	}
	else if(n==0){
		return m;
	}
	else if(n==1 || m==1){
		return 1;
	}
	else if(n<m){
		return gcd(n,m%n);
	}
	else{
		return gcd(m,n%m);
	}
}

// returns a count of how many numbers are coprime to n
int totient(int n){
	int count = 0;
	int i;
	for (i=1; i<n; i++){
		if(gcd(i,n)==1){
			count++;
		}
	}

	return count;
}

//returns true if m and n are coprimes of each other
bool isCoprime(int m, int n){
	if(gcd(m,n)==1){
		return true;
	}
	return false;
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

long mod_inverse(long base, long m){
	int mI = (int)m;
	int totI = totient(mI)-1;
	long tot = (long)totI;
	return modulo(base,tot,m);
}

long endecrypt(long msg, int key, int c){
	long keyI = (long)key;
	long cI = (long)c;
	return modulo(msg,keyI,cI);
}


//returns true if a is prime
bool isPrime(int a){
	int i;
	for(i=2; i<a; i++){
		if(a%i ==0){
			return false;
		}
	}

	return true;
}

//finds a and b from a given c,m,and e
void findAB(int c, int m, int e, int returnVals[]){
	int i,j,index=2;
	int number=3;
	int primes[m+c];
	primes[0]=1;
	primes[1]=2;

	//gets all primes from 1-m
	for(i=3; i<m; i++){
		if(isPrime(i)){
			primes[index]=i;
			index++;
		}
	}

	for (i=0; i<index;i++){
		for(j=0; j<index;j++){
			if(i!=j && (primes[i]*primes[j]==c)){ //if a*b=c
				if((primes[i]-1)*(primes[j]-1)==m){ //if m= (a-1)(b-1)
					if(isCoprime(e,primes[i])){		//if e is coprime to a
						returnVals[0]=primes[i];
						returnVals[1]=primes[j];
						return;
					}
					else if(isCoprime(e,primes[j])){
						returnVals[0]=primes[j];
						returnVals[1]=primes[i];
						return;
					}
				}
			}
		}
	}
}

char intToChar(int num){
	char c = num;
	return c;
}

int charToInt(char let){
	int num = (int)let;
	return num;
}

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Error: must give two numbers as arguments (e, then c)\n");
		return 1;
	}

	int e,c,m,i;
	long d;
	sscanf(argv[1],"%d", &e);
	sscanf(argv[2],"%d", &c);	
	
	m = totient(c);
	printf("M: %d\n", m);
	m=(long)m;
	e=(long)e;
	d = mod_inverse(e,m);
	printf("D was found to be %ld\n",d);
	int ab[2];
	findAB(c,m,e,ab);
	printf("A was %d and B was %d\n",ab[0],ab[1]);
	
	d=(int)d;
	long msg = endecrypt(1148,1531,2623);
	printf("1148:\n");
	printf("This char is decrypted to %d\n",msg);
	printf("The letter is %c\n", intToChar(msg));
}
