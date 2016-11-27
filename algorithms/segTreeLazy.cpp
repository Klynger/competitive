#include<bits/stdc++.h>

using namespace std;

#define N 100002
#define NEUTRAL_VALUE 0
#define ROOT 1

typedef long long ll;

struct Node {
	ll value, lazy;
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

inline void spreadLazy(int node, int l, int r) {
	if(l == r) {
		tree[node].value += tree[node].lazy;
	
	} else {
		tree[node].value += (tree[node].lazy*(r - l + 1));
		tree[left(node)].lazy += tree[node].lazy;
		tree[right(node)].lazy += tree[node].lazy;
	}

	tree[node].lazy = NEUTRAL_VALUE;
}// spreadLazy

inline void setValue(int node) {
	tree[node].value = tree[left(node)].value + tree[right(node)].value;
}

void create(int node, int l, int r) {

	if(l == r) {
		tree[node].value = arr[l];
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

inline void trivialUpdate(int ul, int rl, ll value) {
	for(int i = ul; i <= rl; i++)
		arr[i] += value;
}

inline ll trivialQuery(int ql, int qr) {

	ll ans = 0;

	for(int i = ql; i <= qr; i++)
		ans += arr[i];

	return ans;
}

int main() {

	int n, queries;
	scanf("%d %d", &n, &queries);
	
	for(int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	
	create(ROOT, 1, n);


	int op, l, r;
	ll value;
	while(queries--) {
		scanf("%d %d %d", &op, &l, &r);
		if(op == 0) {
			scanf("%lld", &value);
			update(ROOT, 1, n, l, r, value);
			trivialUpdate(l, r, value);
		} else {
			printf("MyQuery is %lld, trivialQuery is %lld\n", query(ROOT, 1, n, l, r), trivialQuery(l, r));
		}

	}

	return 0;
}