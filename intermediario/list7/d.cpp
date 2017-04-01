#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcdExtended(ll a, ll b, ll &x, ll &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}

	ll x1, y1, gcd = gcdExtended(b, a % b, x1, y1);
	// Update x and y using results of recursive
	x = y1;
	y = x1 - (a/b) * y1;

	return gcd;

}

int main () {
	ll a, b, d;
	ll x, y;
	while(scanf("%lld%lld", &a, &b) != EOF) {
		d = gcdExtended(a, b, x, y);
		printf("%lld %lld %lld\n", x, y, d);
	}
	return 0;
}