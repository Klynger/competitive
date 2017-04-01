#include<bits/stdc++.h>

using namespace std;

typedef long long ll;


bool isPrime(ll n) {
	if (n % 2 == 0)
		return false;
	ll lim = ceil(sqrt(n));
	for (ll num = 3; num <= lim; num += 2) {
		if (n % num == 0)
			return false;
	}

	return true;
}

ll getBiggestLovelyNumber(ll n) {
	ll ans = 1;
	
	if(n % 2 == 0) {
		ans *= 2;
		while(n % 2 == 0)
			n /= 2;
	}

	ll lim = ceil(sqrt(n));
	for(int div = 3; div <= lim; div += 2) {
		if(n % div == 0) {
			ans *= div;
			while(n % div == 0)
				n /= div;
		}
	}
	if(isPrime(n))
		ans *= n;
	return ans;
}

int main() {
	ll n;
	scanf("%I64d", &n);

	printf("%I64d\n", getBiggestLovelyNumber(n));

	return 0;
}