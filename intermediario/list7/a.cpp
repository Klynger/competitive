#include<bits/stdc++.h>

using namespace std;

int gcd (int a, int b) {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int main () {
	int n;
	scanf("%d", &n);
	int a, b, c;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a, &b, &c);

		printf("Case %d: %s\n", i, c % gcd(a,b) == 0 ? "Yes" : "No");
	}
	return 0;
}