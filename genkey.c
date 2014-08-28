#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int findNprime(int n){
	int count = 1;
	int number = 1;
	int i;
	bool isPrime = true;
	if (n == 1){
		return 1;
	}

	while(count < n){
		number++;
		for (i=2; i<number; i++){
			if(number%i == 0){
				isPrime=false;
				break;
			}
			isPrime=true;
		}
		if(isPrime){
			count++;
		}
	}
	
	return number;
}

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
	int i;
	int count=0;
	for (i=1; i<n; i++){
		if(gcd(i,n)==1){
			count++;
		}
	}

	return count;
}

int findCoprimeOf2(int m,int n){
	int i=0,j=0;
	int mPrimes[5000];
	int nPrimes[5000];
	int m2=m*2;
	mPrimes[0]=coprime(m2);
	nPrimes[0]=coprime(n);

	while(mPrimes[i]!=0){
		j=0;
		while(nPrimes[j]!=0){
			if(mPrimes[i]==nPrimes[j]){
				return mPrimes[i];
			}
			j++;
		}
		i++;
		if(mPrimes[i]==0){
			mPrimes[i]=coprime(m2);
			mPrimes[j]=coprime(n);
			i=0;
		}
	}
}

int coprime(int n){
	int number = rand()%n+1;
	while(1){
	//	printf("COPRIME: %d  ALSO: %d\n",number,gcd(n,number));
		if(gcd(n,number)==1){
			return number;
		}
		number = rand()%n+1;
	}	
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


int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Error: must give two numbers as arguments\n");
		return 1;
	}

	int val1, val2;

	sscanf(argv[1],"%d", &val1);
	sscanf(argv[2],"%d", &val2);	

	int a = findNprime(val1);
	int b = findNprime(val2);

	printf("%dth prime: = %d\n",val1,a);
	printf("%dth prime: = %d\n",val2,b);

	int c = a * b;
	printf("c = %d\n",c);
	int m = (a-1) * (b-1);
	printf("m = %d\n",m);
//	int e = findCoprimeOf2(8,15);	
	int e = findCoprimeOf2(c,m);	
	printf("e = %d\n",e);
	int d = mod_inverse(e,m);
//	int d = mod_inverse(451,2520);
	printf("d = %d\n",d);
	printf("Public Key = (%d, %d)\n",e,c);
	printf("Private Key = (%d, %d)\n",d,c);
//	printf("COPRIME = %d\n",coprime(15));
//	printf("gcd = %d\n",gcd(23,8));
	
	
//	printf("Please enter the public key:");
//	printf("e: ");
//	e=451;
//	c=2623;
	long test = endecrypt(72,e,c);
	printf("encrypt 72: %d\n",test);
	test = endecrypt(721,d,c);
	printf("decrypt 721: %d\n",test);
	//	scanf("%s",&publicKey);

}
