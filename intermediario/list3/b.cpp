#include<bits/stdc++.h>

using namespace std;

#define N 100002
#define NEUTRAL_VALUE 0
#define ROOT 1
#define MOD 3

typedef int ll;

struct Node {
	ll value, lazy, mod2, mod1;
};

typedef struct Node Node;

Node tree[N*4];
ll arr[N];

inline int left(int i) {
	return i<<1;
}

inline int right(int i) {
	return i<<1 | 1;
}

inline void swapValues(int node) {
	if(tree[node].lazy == 1) {
		int aux = tree[node].value;
		tree[node].value = tree[node].mod2;
		tree[node].mod2 = tree[node].mod1;
		tree[node].mod1 = aux;
	} else if(tree[node].lazy == 2) {
		int aux = tree[node].value;
		tree[node].value = tree[node].mod1;
		tree[node].mod1 = tree[node].mod2;
		tree[node].mod2 = aux;
	}
	
	
}

inline void spreadLazy(int node, int l, int r) {
	if(l == r) {
		tree[node].lazy %= MOD;
		swapValues(node);
	
	} else {
		
		tree[node].lazy %= MOD;
		swapValues(node);
		tree[left(node)].lazy += tree[node].lazy;
		tree[right(node)].lazy += tree[node].lazy;
	}

	tree[node].lazy = NEUTRAL_VALUE;
}// spreadLazy

inline void setValue(int node) {
	tree[node].value = tree[left(node)].value + tree[right(node)].value;
	tree[node].mod2 = tree[left(node)].mod2 + tree[right(node)].mod2;
	tree[node].mod1 = tree[left(node)].mod1 + tree[right(node)].mod1;
}

void create(int node, int l, int r) {

	if(l == r) {
		tree[node].value++;
	} else {
		int mid = (l+r)>>1;

		create(left(node), l, mid);
		create(right(node), mid+1, r);

		setValue(node);
	}
}// create

void update(int node, int l, int r, int ul, int ur, ll value) {

	if(tree[node].lazy != NEUTRAL_VALUE) {
		spreadLazy(node, l, r);
	}

	if(ur < l || r < ul)
		return;

	if(ul <= l && r <= ur) {
		tree[node].lazy += value;
		spreadLazy(node, l, r);
	} else {
		int mid = (l+r)>>1;
		update(left(node), l, mid, ul, ur, value);
		update(right(node), mid+1, r, ul, ur, value);

		setValue(node);
	}

}// update

ll query(int node, int l, int r, int ql, int qr) {

	if(tree[node].lazy != NEUTRAL_VALUE)
		spreadLazy(node, l, r);

	if(qr < l || r < ql)
		return NEUTRAL_VALUE;

	if(ql <= l && r <= qr) 
		return tree[node].value;
	
	int mid = (l+r)>>1;
	ll q1 = query(left(node), l, mid, ql, qr);
	ll q2 = query(right(node), mid+1, r, ql, qr);

	return q1 + q2;

}// query

inline void naiveHUpdate(int ul, int rl, ll value) {
	for(int i = ul; i <= rl; i++)
		arr[i] += value;
}

inline ll naiveHQuery(int ql, int qr) {

	ll ans = 0;
	for(int i = ql; i <= qr; i++)
		ans += arr[i] % MOD == 0 ? 1 : 0;

	return ans;
}

int main() {

	int n, queries;
	scanf("%d %d", &n, &queries);
	
	create(ROOT, 1, n);

	int op, l, r;
	ll value;
	while(queries--) {
		scanf("%d %d %d", &op, &l, &r);
		if(op == 0) {
			update(ROOT, 1, n, l+1, r+1, 1);
//			naiveHUpdate(l+1, r+1, 1);
		} else {
//			printf("MyQuery is %d, naiveHQuery is %d\n", query(ROOT, 1, n, l+1, r+1), naiveHQuery(l+1, r+1));
			printf("%d\n", query(ROOT, 1, n, l+1, r+1));
		}

	}

	return 0;
}