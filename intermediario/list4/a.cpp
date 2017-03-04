#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 1001
#define LOGN 20
#define ROOT 1
#define NOT_SET -1

vector<int> graph[N];
int table[N][LOGN+1];
int parent[N];
int level[N];

inline void swap(int *p, int *q) {
	int temp = *p;
	*p = *q;
	*q = temp;
}

void setLevels(int node) {
	
	level[node] = level[parent[node]] + 1;

	for(int i = 0; i < (int)graph[node].size(); i++)
		setLevels(graph[node][i]);

}

inline void setTable(int n) {

	for(int i = 0; i <= n; i++) 
		for(int j = 0; j <= n; j++)
			table[i][j] = NOT_SET;
	
	for(int i = 1; i <= n; i++)
		table[i][0] = parent[i];

	for(int j = 1; 1 << j <= n; j++) {
		for(int i = 1; i <= n; i++)
			if(table[i][j-1] != NOT_SET)
				table[i][j] = table[table[i][j-1]][j-1];
	}
}


int query(int n, int u, int v) {

	int log, i;

	// u has to have the higher level always
	if(level[u] < level[v])
		swap(&u, &v);

	for(log = 1; 1 << log <= level[u]; log++);
		log--;
	
	for(i = log; i >= 0; i--) {
		if(level[u] - (1 << i) >= level[v])
			u = table[u][i];
	}

	if(u == v)
		return u;
	
	for(i = log; i >= 0; i--) {
		if(table[u][i] != NOT_SET 
			&& table[u][i] != table[v][i]) {
	
			u = table[u][i]; v = table[v][i];
		}

	}// for
	
	return parent[u];
}// query

inline void printArr(int arr[], int n) {
	for(int i = 0; i <= n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

inline void printTable(int table[N][LOGN+1], int n) {

	for(int i = 1; i <= n; i++)
		printArr(table[i], LOGN);
}

int main() {

	int t;
	
	scanf("%d", &t);

	int n, m, aux, u, v;
	const int CASE_NUMBER = t;
	while(t--) {

		scanf(" %d", &n);

		for(int i = 0; i <= n; i++)
			parent[i] = i;

		for(int i = 1; i <= n; i++) {
			scanf(" %d", &m);
			for(int j = 0; j < m; j++) {
				scanf(" %d", &aux);
				graph[i].push_back(aux);
				parent[aux] = i;
			}

		}// for


		level[ROOT] = -1;
		setLevels(ROOT);
		setTable(n);
//		printArr(level, n);
//		printTable(table, n);

		scanf("%d", &m);
		printf("Case %d:\n", CASE_NUMBER - t);
		while(m--) {
			scanf(" %d %d", &u, &v);

			printf("%d\n", query(n, u, v));
		}

	}// while

	return 0;
}// main
