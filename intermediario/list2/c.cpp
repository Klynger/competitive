#include<bits/stdc++.h>
 
using namespace std;
 
#define N 100005
#define ROOT 1
 
typedef long long ll;
 
ll arr[N];
ll tree[N*4];
 
void printTree(int n) {
	for(int i = 1; i <= n*3; i++)
		printf("%lld ", tree[i]);
	printf("\n");
}
 
inline int father(int i) {
	return i>>1; // i / 2
}
 
inline int left(int i) {
	return i<<1; // i*2
}
 
inline int right(int i) {
	return i<<1 | 1; // i*2+1
}
 
void create(int node, int l, int r) {
 
	if(l == r) {
			tree[node] = arr[l];
	
	} else {
 
		int mid = (l+r)>>1;
		create(left(node), l, mid);
		create(right(node), mid+1, r);
		tree[node] = max(tree[left(node)], tree[right(node)]);
	}
 
}
 
ll query(int node, int l, int r, int ql, int qr) {
	if(r < ql || qr < l) {
		return 0;
	
	} else if(ql <= l && r <= qr) {
		return tree[node];
	
	} 
 
	int mid = (l+r)>>1;
	ll q1 = query(left(node), l, mid, ql, qr);
	ll q2 = query(right(node), mid+1, r, ql, qr);
 
	return max(q1, q2);
}
 
void update(int node, int l, int r, int index, ll value) {
	
	if(index < l || r < index)
		return;
 
	else if(l != r) {
		int mid = (l+r)>>1;
		update(left(node), l, mid, index, value);
		update(right(node), mid+1, r, index, value);
		tree[node] = max(tree[left(node)], tree[right(node)]);
	} else {
		tree[node] = value;
		arr[index] = value;
	}
	
}
 
int main() {
 
	int t;
	scanf("%d", &t);
 
 
	int n, q;
	ll actualBalloons;
	for(int test = 0; test < t; test++) {
 
		printf("Testcase %d:\n", test);
 
		scanf("%d %lld", &n, &actualBalloons);
		for(int i = 1; i <= n; i++)
			scanf("%lld", &arr[i]);
 
		create(ROOT, 1, n);
		scanf("%d", &q);
 
		char op;
		int i, j;
		ll k;
		while(q--) {
			scanf("\n%c", &op);
 
			if(op == 'A') {
 
				scanf("%lld", &k);
				actualBalloons += k;
 
			} else if(op == 'B') {
				
				scanf("%d %d", &j, &i);
				update(ROOT, 1, n, j+1, i);
 
			} else {
				scanf("%d %d", &i, &j);
				printf("%lld\n", 
					abs(actualBalloons-query(ROOT, 1, n, i+1, j+1)));
			}
		}
		printf("\n");
	}// for tests
	return 0;
} 