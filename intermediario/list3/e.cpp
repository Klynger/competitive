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
Node ans;

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

void query(int node, int l, int r, int ql, int qr) {

	if(tree[node].lazy != NEUTRAL_VALUE)
		spreadLazy(node, l, r);

	if(qr < l || r < ql)
		return;

	if(ql <= l && r <= qr) {
		ans.value += tree[node].value;
		ans.mod1 += tree[node].mod1;
		ans.mod2 += tree[node].mod2;
		return;
	}
	
	int mid = (l+r)>>1;
	query(left(node), l, mid, ql, qr);
	query(right(node), mid+1, r, ql, qr);

}// query

inline void cleanTree(int n) {
	for(int i = 0; i <= n*4; i++) {
		tree[i].value = 0;
		tree[i].mod1 = 0;
		tree[i].mod2 = 0;
		tree[i].lazy = 0;
	}
}

int main() {

	int n, queries;

		while(scanf("%d %d", &n, &queries) != EOF) {
		
		cleanTree(n);
		create(ROOT, 1, n);

		char op;
		int l, r;
		ll value;
		while(queries--) {
			scanf("\n%c %d %d", &op, &l, &r);
			if(op == 'M') {
				update(ROOT, 1, n, l, r, 1);
			} else {
				ans.value = 0; ans.lazy = 0; ans.mod1 = 0; ans.mod2 = 0;
				query(ROOT, 1, n, l, r);
				printf("%d %d %d\n", ans.value, ans.mod1, ans.mod2);
			}
		}

		printf("\n");
	}
	return 0;
}