#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 200002

ll _mergeSort(ll arr[], ll temp[], int left, int right);
ll _merge(ll arr[], ll temp[], int left, int mid, int right);

ll mergeSort(ll arr[], int arraySize) {

	ll *temp = (ll *)malloc(sizeof(ll)*arraySize);
	return _mergeSort(arr, temp, 0, arraySize-1);
}

ll _mergeSort(ll arr[], ll temp[], int left, int right) {

	ll invCount = 0;
	if(left < right) {
		
		int mid = (left + right) >> 1;

		invCount = _mergeSort(arr, temp, left, mid);
		invCount += _mergeSort(arr, temp, mid+1, right);
		invCount += _merge(arr, temp, left, mid+1, right);
	}

	return invCount;
}// _mergeSort


ll _merge(ll arr[], ll temp[], int left, int mid, int right) {
	
	ll invCount = 0;
	int i = left;
	int j = mid;
	int k = left;
	while(i <= mid-1 && j <= right) {
		if(arr[i] <= arr[j]) 
			temp[k++] = arr[i++];
		else {
			temp[k++] = arr[j++];
			invCount += (mid - i);
		}
		
	}// while

	while(i <= mid-1) 
		temp[k++] = arr[i++];
	while(j <= right)
		temp[k++] = arr[j++];

for(i = left; i <= right; i++)
	arr[i] = temp[i];
	
	return invCount;
}// merge

int main() {

	ll arr[N];

	int t, n;
	scanf("%d", &t);

	while(t--) {
		scanf("%d", &n);

		for(int i = 0; i < n; i++)
			scanf("%lld", &arr[i]);

		printf("%lld\n", mergeSort(arr, n));

	}

	return 0;
}