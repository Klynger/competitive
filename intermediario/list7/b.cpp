#include<bits/stdc++.h>

using namespace std;

#define MAX_NUMBER 1000000000
#define BIGGEST_POSSIBLE_DIV 32000 // ~qrt(MAX_NUMBER)

typedef long long ll;

bool isPrime[BIGGEST_POSSIBLE_DIV + 1];
vector<int> primes;

void crivo(const ll N) {
	
	isPrime[0] = true;
	isPrime[1] = true;

	for(int i = 2; i <= N; i++) {
		if(!isPrime[i]) {
			primes.push_back(i);
			for(int j = i<<1; j <= N; j += i)
				isPrime[j] = true;
		}
	}
}

int getQuantDivs(ll number) {
	int ans = 1;
	int multiplier;
	
	for(int i = 0; i < (int)primes.size() && number > 1; i++) {
		
		if(number % primes[i] == 0) {
			
			multiplier = 1;
			while(number % primes[i] == 0) {
				number /= primes[i];
				multiplier++;
			}// while
			ans *= multiplier;
		}// if
	}// for

	return ans;
}

int main() {
	int n;
	ll a, b;

	pair<ll, ll> range;
	ll number;
	int quantDivs = 0, aux;

	
	scanf("%d", &n);
	
	crivo(BIGGEST_POSSIBLE_DIV);
	
	for(int t = 0; t < n; t++) {
		scanf("%lld %lld", &a, &b);

		for(int i = a; i <= b; i++) {
			aux = getQuantDivs(i);
			
			if(quantDivs < aux) {
				quantDivs = aux;
				range.first = a; range.second = b;
				number = i;

			}// if
		}// for
		printf("Between %lld and %lld, %lld has a maximum of %d divisors.\n", 
			range.first, range.second, number, quantDivs);

	}

	return 0;
}