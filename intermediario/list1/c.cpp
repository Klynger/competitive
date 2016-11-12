#include<bits/stdc++.h>

using namespace std;

#define MAXN 30002
#define GROUP 174// ~sqrt(MAXN)
#define MAX_QUERIES 200002
#define MAX_NUM 1000002

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
int freq[MAX_NUM];
vector<Query> queries;
int ans[MAX_QUERIES], answer = 0;


inline void add(int index) {
	freq[arr[index]]++;
	if(freq[arr[index]] == 1) answer++;
}

inline void remove(int index) {
	freq[arr[index]]--;
	if(freq[arr[index]] == 0) answer--;
}

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

	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	int q;
	scanf("%d", &q);

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
		printf("%d\n", ans[j]);

	return 0;
}