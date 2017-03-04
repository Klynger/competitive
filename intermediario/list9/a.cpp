#include<bits/stdc++.h>

using namespace std;

#define N 1000002

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%s\n", n % (m+1) == 0  ? "Carlos" : "Paula");

	return 0;
}