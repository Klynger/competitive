#include<bits/stdc++.h>

using namespace std;

#define MAX_VERTICES 200002

typedef long long ll;

vector<int> graph[MAX_VERTICES];
ll values[MAX_VERTICES];
ll edges[MAX_VERTICES];
int ans[MAX_VERTICES];
int parents[MAX_VERTICES];

void dfs(int node) {

	int current = node;

	ll dist = 0;
	while(parents[current] != parents[1]) {
		if(dist + edges[current] <= values[current])
			ans[parents[current]]++;
		dist += edges[current];
		current = parents[current];
	}

	for(int i = 0; i < (int)graph[node].size(); i++) 
			dfs(graph[node][i]);
	
}

int main() {
	int n;
	scanf("%d", &n);

	for(int i = 1; i <= n; i++)
		scanf("%I64d", &values[i]);

	int p;
	ll w;

	for(int i = 2; i <= n; i++) {
		scanf("%d %I64d", &p, &w);

		graph[p].push_back(i);
		edges[i] = w;
		parents[i] = p;
	}

	parents[1] = n+1;
	dfs(1);

	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);

	printf("\n");

	return 0;
}