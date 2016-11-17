#include<bits/stdc++.h>

using namespace std;


int main() {
	int arr[4];

	for(int i = 0; i < 4; i++)
		scanf("%d", &arr[i]);


	int indices[4] = {0,1,2,3};
	vector<int> ans;
	do {
		ans.push_back(abs(arr[indices[0]] + arr[indices[1]] - arr[indices[2]] - arr[indices[3]]));
	} while (next_permutation(indices, indices+4));


	sort(ans.begin(), ans.end());
/*
	for(int i = 0; i < ans.size(); i++)
		printf("%d ", ans[i]);
	printf("\n");
*/
	printf("%d\n", ans[0]);
	return 0;
}