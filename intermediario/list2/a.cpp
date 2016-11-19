#include<bits/stdc++.h>
 
using namespace std;
 
#define N 100005
#define ROOT 1
#define NEUTRAL_VALUE 0
 
typedef long long ll;

pair<ll, ll> tree[N*4];
ll arr[N];
pair<ll, ll> neutralNode;
 
inline int father(int i) {
	return i>>1; // i / 2
}
 
inline int left(int i) {
	return i<<1; // i*2
}
 
inline int right(int i) {
	return i<<1 | 1; // i*2+1
}


inline pair<ll, ll> getBiggestsNumbers(pair<ll, ll> n1, pair<ll, ll> n2) {
	pair<ll, ll> ans;

	ll orderedArr[4];
	orderedArr[0] = n1.first; orderedArr[1] = n1.second;
	orderedArr[2] = n2.first; orderedArr[3] = n2.second;

	sort(orderedArr, orderedArr+4);
	ans.first = orderedArr[3];
	ans.second = orderedArr[2];

	return ans;
}

void create(int node, int l, int r) {
 
	if(l == r) {
			tree[node].first = arr[l];
			tree[node].second = NEUTRAL_VALUE;
	
	} else {
 
		int mid = (l+r)>>1;
		create(left(node), l, mid);
		create(right(node), mid+1, r);

		if(l == mid) {
			tree[node].first = tree[left(node)].first;
			tree[node].second = tree[right(node)].first; 
		}

		else {
			pair<ll, ll> res = getBiggestsNumbers(tree[left(node)], 
				tree[right(node)]);

			tree[node].first = res.first;
			tree[node].second = res.second;
		}

	}// if-else
 
}// create
 
pair<ll, ll> query(int node, int l, int r, int ql, int qr) {
	if(r < ql || qr < l) {
		return neutralNode;
	
	} else if(ql <= l && r <= qr) {
		return tree[node];
	
	} 
 
	int mid = (l+r)>>1;
	pair<ll, ll> q1 = query(left(node), l, mid, ql, qr);
	pair<ll, ll> q2 = query(right(node), mid+1, r, ql, qr);
 
	pair<ll, ll> res = getBiggestsNumbers(q1, q2);

	return res;
}
 
void update(int node, int l, int r, int index, ll value) {
	
	if(index < l || r < index)
		return;
 
	else if(l != r) {
		int mid = (l+r)>>1;
		update(left(node), l, mid, index, value);
		update(right(node), mid+1, r, index, value);
		
		if(l == mid) {
			tree[node].first = tree[left(node)].first;
			tree[node].second = tree[right(node)].first;
		}
		else {
			pair<ll, ll> res = getBiggestsNumbers(tree[left(node)], 
				tree[right(node)]);

			tree[node].first = res.first;
			tree[node].second = res.second;
		}


	} else {
		tree[node].first = value; tree[node].second = NEUTRAL_VALUE;
		arr[index] = value;
	}
	
}


int main() {
	neutralNode.first = 0;
	neutralNode.second = 0;
	int n;
	scanf("%d", &n);

	for(int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);

	int q;
	scanf("%d", &q);

	create(ROOT, 1, n);

	char op;
	int x, y;
	ll z;
	while(q--) {
		scanf("\n%c %d", &op, &x);

		if(op == 'Q') {
			scanf("%d", &y);
			pair<ll, ll> ans = query(ROOT, 1, n, x, y);
			printf("%lld\n", ans.first + ans.second);
		}

		else {
			scanf("%lld", &z);
			update(ROOT, 1, n, x, z);
		}
	}



	return 0;
}
