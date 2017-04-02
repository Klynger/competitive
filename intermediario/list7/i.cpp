#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcdExtended(ll a, ll b, ll &x, ll &y) {
	if(b == 0) {
		y = 0;
		x = 1;
		return a;
	}

	ll x1, y1, gcd = gcdExtended(b, a % b, x1, y1);
	// Update x and y using results of recursive
	x = y1;
	y = x1 - (a/b) * y1;

	return gcd;

}

int main () {
	ll a, b, c, n;
	ll x, y, gcd;
	ll p, q;
	int t;
	scanf("%d", &t);
	for(int k = 0; k < t; k++) {

		scanf("%lld%lld", &a, &b);

		c = a;
		a = (ll) floor((double) c/b);
		b = (ll) ceil((double) c/b);

		gcd = gcdExtended(a, b, x, y);

		n = (ll) ceil((x * (double) c/gcd) / -b);
		p = (x * c/gcd) + b * n;
		q = (y * c/gcd) - a * n;

		printf("%lld %lld\n", p, q);

	}
	 
	return 0;
}