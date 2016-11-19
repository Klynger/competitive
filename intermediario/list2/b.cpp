#include<bits/stdc++.h>
 
using namespace std;
 
#define N 100005
#define ROOT 1
#define NEUTRAL_VALUE 1
 
typedef int ll;
 
ll arr[N];
ll tree[N*4];
 
void printTree(int n) {
	printf("\n");
	for(int i = 1; i <= n*3; i++)
		printf("%d ", tree[i]);
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

inline int getValue(const ll v) {
	if(v < 0)
		return -1;
	else if(v > 0)
		return 1;
	else
		return 0;
}

void create(int node, int l, int r) {
 
	if(l == r) {
			tree[node] = getValue(arr[l]);
	
	} else {
 
		int mid = (l+r)>>1;
		create(left(node), l, mid);
		create(right(node), mid+1, r);
		tree[node] = tree[left(node)] * tree[right(node)];
	}
 
}
 
ll query(int node, int l, int r, int ql, int qr) {
	if(r < ql || qr < l) {
		return NEUTRAL_VALUE;
	
	} else if(ql <= l && r <= qr) {
		return tree[node];
	
	} 
 
	int mid = (l+r)>>1;
	ll q1 = query(left(node), l, mid, ql, qr);
	ll q2 = query(right(node), mid+1, r, ql, qr);
 
	return q1 * q2;
}
 
void update(int node, int l, int r, int index, ll value) {
	
	if(index < l || r < index)
		return;
 
	else if(l != r) {
		int mid = (l+r)>>1;
		update(left(node), l, mid, index, value);
		update(right(node), mid+1, r, index, value);
		tree[node] = tree[left(node)] * tree[right(node)];
	} else {
		tree[node] = getValue(value);
		arr[index] = getValue(value);
	}
	
}

inline char getAns(const ll value) {
	if(value <  0)
		return '-';
	else if(value > 0)
		return '+';
	else
		return '0';
}

int main() {
	int n, k;

	while(scanf("%d%d", &n, &k) != EOF) {

		for(int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);

		create(ROOT, 1, n);

		char op;
		int i, j;
		while(k--) {
			scanf("\n%c %d %d", &op, &i, &j);


			if(op == 'P') 
				printf("%c", getAns(query(ROOT, 1, n, i, j)));
			else {
				update(ROOT, 1, n, i, j);
			}

		}
		printf("\n");
	}// test case
	return 0;
}// main
