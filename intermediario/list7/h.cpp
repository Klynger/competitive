#include<bits/stdc++.h>

using namespace std;

#define MAX_NUMBER 10000000

int minorPrime[MAX_NUMBER+1];

void getMinorPrimes(const int N) {
	minorPrime[0] = 1;
	minorPrime[1] = 1;

	for (int i = 2; i <= N; i++) 
		if (minorPrime[i] == 0) 
			for (int j = i; j <= N; j += i)
				if (minorPrime[j] == 0)
					minorPrime[j] = i;
}



int main () {
	int n;
	getMinorPrimes(MAX_NUMBER);
	while(scanf("%d", &n) != EOF) {

		printf("1");
		
		while(n > 1) {
			printf(" x %d", minorPrime[n]);
			n /= minorPrime[n];
		}

		printf("\n");

	}
	return 0;
}