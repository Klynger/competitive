#include<bits/stdc++.h>
 
using namespace std;
 
#define N 100005
#define ROOT 1
 
typedef int ll;

struct Node {

	ll totalSum, bestSum;
	int l, r;

}tree[N*4];


ll arr[N];

 
inline int father(int i) {
	return i>>1; // i / 2
}
 
inline int left(int i) {
	return i<<1; // i*2
}
 
inline int right(int i) {
	return i<<1 | 1; // i*2+1
}


inline void sumSides(int node) {
	tree[node].l = tree[left(node)].l;
	tree[node].r = tree[right(node)].r;
	tree[node].bestSum = tree[left(node)].bestSum + 
	tree[right(node)].bestSum;
}
inline void sidedBestSum(int node, int side) {
	tree[node].l = tree[side].l;
	tree[node].r = tree[size].r;
	tree[node].bestSum = tree[side].bestSum;
}

inline void bestSumTotalSum(int node, int l, int r) {
	tree[node].l = l;
	tree[node].r = r;
	tree[node].bestSum = tree[node].totalSum;
}

inline void setBestSum(int node, int l, int r) {

	tree[node].totalSum = tree[left(node)].totalSum + 
	tree[right(node)].totalSum;

	if(tree[node].totalSum > tree[left(node)].bestSum + 
		tree[right(node)].bestSum) {
		bestSumTotalSum(node, l, r);

	} else if(tree[left(node)].r+1 == tree[right(node)].l) {
		if(tree[left(node)].bestSum >= 0) {
			if(tree[right(node)].bestSum >= 0) 
				sumSides(node);
			else {
				sidedBestSum(node, left(node));
			}
		
		} else if(tree[right(node)].bestSum >= 0) {
			sidedBestSum(node, right(node));
		}
	
	} else {
		if(tree[left(node)].bestSum >= tree[right(node)].bestSum) {
			tree[node].bestSum = tree[left(node)].bestSum;
			tree[node].l = tree[left(node)].l;
			tree[node].r = tree[left(node)].r
		} else {
			tree[node].bestSum = tree[right(node)].bestSum;
			tree[node].l = tree[right(node)].l;
			tree[node].r = tree[right(node)].r
		}
	}


}// setBestSum

void create(int node, int l, int r) {
 
	if(l == r) {
			tree[node].bestSum = arr[l];
			tree[node].totalSum = arr[l];
			tree[node].l = l; tree[node].r = r;
	
	} else {
 
		int mid = (l+r)>>1;
		create(left(node), l, mid);
		create(right(node), mid+1, r);
		setBestSum(node, l, r);
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



	return 0;
}
