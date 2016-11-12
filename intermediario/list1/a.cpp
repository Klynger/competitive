#include<bits/stdc++.h>

using namespace std;

typedef long long ll;



#define MAXN 100002
#define GROUP 317 //~ sqrt(MAXN)

/*
#define MAXN 9
#define GROUP 3
*/

ll arr[MAXN];
vector<ll> groups[GROUP];


inline int binarySearch(int g, ll value) {

	int l = 0;
	int r = groups[g].size()-1;
	int mid;

	while(l <= r) {

		mid = (l+r)/2;
		if(groups[g][mid] < value) 
			l = mid+1;
		else if(value < groups[g][mid]) 
			r = mid-1;
		
		else {
			while(mid+1 < groups[g].size() && 
				groups[g][mid+1] == value) mid++;
			return mid;
		}// if-elseif-else
		
	}// while

	if(groups[g][mid] > value && mid > 0) mid--;

	return mid;


}// binarySearch

/*
void printArr(int n) {
	for(int i = 0; i < n; i++)
		printf("%lld ", arr[i]);

	printf("\n");
}

void printGroups() {
	for(int i = 0; i < MAXN/GROUP; i++) {

		for(int j = 0; j < (int)groups[i].size(); j++)
			printf("%lld ", groups[i][j]);
		printf("\n");
	}
}
*/




inline void changeValue(int index, ll newValue) {
	groups[index/GROUP][binarySearch(index/GROUP, arr[index])] = newValue;
	arr[index] = newValue;
	sort(groups[index/GROUP].begin(), groups[index/GROUP].end());
}// changeValue

inline int getAns(int l, int r, ll value) {
	int ans = 0;

	for(int i = l; i <= r;) {

		if(i % GROUP == 0 && i + GROUP -1 <= r) {
			
			if(groups[i/GROUP][0] <= value)
				ans += binarySearch(i/GROUP, value)+1;

			i += GROUP;

		} else {
			if(arr[i] <= value)
				ans++;
			i++;
		}

	}// for

	return ans;

}// getAns

int main() {

	int n, q;
	scanf("%d%d", &n, &q);

	for(int i = 0; i < n; i++) {
		
		scanf("%lld", &arr[i]);
		groups[i/GROUP].push_back(arr[i]);
	}

	for(int i = 0; i < GROUP; i++)
		sort(groups[i].begin(), groups[i].end());

	char op;
	int l, r;
	ll value;
	for(int k = 0; k < q; k++) {
		scanf("\n%c", &op);

		if(op == 'C') {
		
			scanf("%d %d %lld", &l, &r, &value);
			printf("%d\n", getAns(l-1, r-1, value));
		
		} else {

			scanf("%d %lld", &l, &value);
			changeValue(l-1, value);
		}
	}

	return 0;
}
