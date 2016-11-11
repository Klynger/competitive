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
ll groups[GROUP];
ll addGroups[GROUP];


void printArr(int n) {
	for(int i = 0; i < n; i++)
		printf("%lld ", arr[i]);

	printf("\n");
}

void printGroups(int n) {
	for(int i = 0; i < n/GROUP; i++)
		printf("%lld ", groups[i]);

	printf("\n");
}


void addValue(ll value, int l, int r, int n) {
	for(int i = l; i <= r;) {

		if(i % GROUP == 0 && i + GROUP -1 <= r) {
			groups[i/GROUP] += value;
			i += GROUP;
		} else {
			arr[i] += value;
			addGroups[i/GROUP] += value;
			i++;
		}

	}// for
}// addValue

ll getAns(int l, int r, int n) {
	ll ans = 0;

	for(int i = l; i <= r;) {

		if(i % GROUP == 0 && i + GROUP -1 <= r) {
			ans += (groups[i/GROUP]*GROUP +  addGroups[i/GROUP]);
			i += GROUP;

		} else {
			ans += (arr[i] + groups[i/GROUP]);
			i++;
		}

	}// for

	return ans;

}// getAns


int main() {

	int t;
	scanf("%d", &t);


	int n, c;
	int op, l, r;
	ll value;
	for(int test = 0; test < t; test++) {
		
		memset(arr, 0, sizeof(arr));
		memset(groups, 0, sizeof(groups));
		memset(addGroups, 0, sizeof(addGroups));
		

		scanf("%d%d", &n, &c);

		for(int i = 0; i < c; i++) {
			scanf("%d%d%d", &op, &l, &r);

			if(op == 0) {

				scanf("%lld", &value);
				addValue(value, l-1, r-1, n);

			} else {

				printf("%lld\n", getAns(l-1, r-1, n));

			}// if-else

		}// for test

	}// for t

	return 0;
}// for