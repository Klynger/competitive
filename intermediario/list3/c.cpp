#include<bits/stdc++.h>

using namespace std;

typedef int ll;

#define MAX_X 1025
#define MAX_Y 1025

ll tree[MAX_X][MAX_Y];
ll m[MAX_X][MAX_Y];

inline void updateY(int x, int y, ll val, int i, int j) {
	while( y < MAX_Y) {
		tree[x][y] += (val - m[i][j]);
		y += (y & -y);
	}
}

void update(int x, int y, ll val) {
	int i = x;
	int j = y;
	while(x < MAX_X) {
		updateY(x, y, val, i, j);
		x += (x & -x);
	}
	m[i][j] = val;
}

inline ll queryY(int x, int y) {
	ll ans = 0;
	while(0 < y) {
		ans += tree[x][y];
		y -= (y & -y);
	}

	return ans;
}

ll query(int x, int y) {
	ll ans = 0;
	while(0 < x) {
		ans += queryY(x, y);
		x -= (x & -x);
	}

	return ans;
}

void printMatrix(int n) {
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++)
			printf("%d ", tree[i][j]);
		printf("\n");
	}
}


int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		memset(tree, 0, sizeof(tree));
		memset(m, 0, sizeof(m));
		int n;

		scanf("%d", &n);
		char op[4];
		strcpy(op, "AAA\0");
		int x, y, x2, y2;
		ll num, ans;
		while(strcmp(op, "END") != 0) {
			scanf("%s", op);
			if(strcmp(op, "SET") == 0) {
				scanf("%d%d%d", &x, &y, &num);
				update(y+1, x+1, num);
			} else if(strcmp(op, "SUM") == 0) {
				scanf("%d%d%d%d", &x, &y, &x2, &y2);
				ans = query(y2+1,x2+1) - query(y2+1, x) - query(y, x2+1) + 
				query(y, x);
				printf("%d\n", ans);
			}
		}


	}

	return 0;
}