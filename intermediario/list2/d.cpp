#include<bits/stdc++.h>
 
using namespace std;
 
#define N 502
#define ROOT 1
#define INF 100000

typedef int ll;
 
ll arr[N];
pair<ll, ll> tree[N][N*4];
  
inline int father(int i) {
	return i>>1; // i / 2
}
 
inline int left(int i) {
	return i<<1; // i*2
}
 
inline int right(int i) {
	return i<<1 | 1; // i*2+1
}
 
void create(int node, int l, int r, int i) {
 
	if(l == r) {
			tree[i][node].first = arr[l];
			tree[i][node].second = arr[l];
	
	} else {
 
		int mid = (l+r)>>1;
		create(left(node), l, mid, i);
		create(right(node), mid+1, r, i);
		tree[i][node].first = max(tree[i][left(node)].first, 
			tree[i][right(node)].first);
		tree[i][node].second = min(tree[i][left(node)].second, 
			tree[i][right(node)].second);
	}
 
}
 
pair<ll, ll> query(int node, int l, int r, int ql, int qr, int i) {
	if(r < ql || qr < l) {
		return {-INF, INF};
	
	} else if(ql <= l && r <= qr) {
		return tree[i][node];
	
	} 
 
	int mid = (l+r)>>1;
	pair<ll, ll> q1 = query(left(node), l, mid, ql, qr, i);
	pair<ll, ll> q2 = query(right(node), mid+1, r, ql, qr, i);
 
	pair<ll, ll> ans;
	ans.first = max(q1.first, q2.first);
	ans.second = min(q1.second, q2.second);

	return ans;
}
 
void update(int node, int l, int r, int index, ll value, int i) {
	
	if(index < l || r < index)
		return;
 
	else if(l != r) {
		int mid = (l+r)>>1;
		update(left(node), l, mid, index, value, i);
		update(right(node), mid+1, r, index, value, i);

		tree[i][node].first = max(tree[i][left(node)].first, 
			tree[i][right(node)].first);
		tree[i][node].second = min(tree[i][left(node)].second, 
			tree[i][right(node)].second);

	} else {
		tree[i][node].first = value;
		tree[i][node].second = value;
	}
	
}

int main() {

	int n;
	scanf("%d", &n);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			scanf("%d", &arr[j]);

		create(ROOT, 1, n, i);
	}

	int queries;
	scanf("%d", &queries);

	char op;
	int x1, y1, x2, y2;
	int x, y;
	ll value;
	pair<ll, ll> aux;
	while(queries--) {

		scanf("\n%c", &op);

		if(op == 'q') {
			pair<ll, ll> ans = {-INF, INF};

			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

			for(int i = x1; i <= x2; i++) {
				aux = query(ROOT, 1, n, y1, y2, i);
				ans.first = max(ans.first, aux.first);
				ans.second = min(ans.second, aux.second);
			}// for

			printf("%d %d\n", ans.first, ans.second);

		} else {
			scanf("%d %d %d", &x, &y, &value);
			update(ROOT, 1, n, y, value, x);
		}// if-else
	}// while

	return 0;
}
