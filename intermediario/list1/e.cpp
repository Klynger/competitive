#include<bits/stdc++.h>

using namespace std;

#define MAXN 200002
#define GROUP 418// ~sqrt(MAXN)
#define MAX_QUERIES 200002
#define MAX_NUM 1000000

typedef long long ll;

struct Query {
	int i, l, r;

	Query(){}
	Query(int i, int l, int r) : i(i), l(l), r(r){}


	bool operator < (const Query &q) const {
		if(l/GROUP != q.l/GROUP)
			return l/GROUP < q.l/GROUP;
		else
			return r < q.r;
	}

};

int arr[MAXN];
int freq[MAX_NUM+1];
vector<Query> queries;
ll ans[MAX_QUERIES], answer = 0;


inline void add(int index) {
		ll k = freq[arr[index]];
		ll s = arr[index];
		answer += (((s*k)<<1) + s);

		freq[arr[index]]++;
		
}//add

inline void remove(int index) {
	
	ll k = freq[arr[index]];
	ll s = arr[index];
	answer -= (((s*k)<<1) - s);	
	
	freq[arr[index]]--;
	
}// remove

/*
inline void add(int index) {
	answer += (freq[arr[index]]+1)*(freq[arr[index]]+1)*arr[index] - 
	freq[arr[index]]*freq[arr[index]]*arr[index];
	freq[arr[index]]++;
}

inline void remove(int index) {
	answer += (freq[arr[index]]-1)*(freq[arr[index]]-1)*arr[index] - 
	freq[arr[index]]*freq[arr[index]]*arr[index];
	freq[arr[index]]--;

}
*/

inline void setAns(int &l, int &r, int index) {
	int currentL = queries[index].l;
	int currentR = queries[index].r;

	while(l < currentL) {
		remove(l);
		l++;
	}// while

	while(currentL < l) {
		add(l-1);
		l--;
	}// while

	while(r <= currentR) {
		add(r);
		r++;
	}// while

	while(currentR+1 < r) {
		remove(r-1);
		r--;
	}// while

	ans[queries[index].i] = answer;
}// setAns

int main() {

	int n, q;
	scanf("%d%d", &n, &q);

	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);


	int currentL, currentR;
	for(int j = 0; j < q; j++) {
		scanf("%d%d", &currentL, &currentR);
		queries.push_back(Query(j, currentL-1, currentR-1));
	}

	sort(queries.begin(), queries.end());

	int l = 0, r = 0;
	for(int i = 0; i < q; i++) 
		setAns(l, r, i);
	
	for(int j = 0; j < q; j++)
		printf("%I64d\n", ans[j]);

	return 0;
}