#include<bits/stdc++.h>
 
using namespace std;
 
#define MAX_NODES 100
#define INF 1005
#define UNITIALIZED -1 // value for node with no parent
#define NEUTRAL 0
 
int capacities[MAX_NODES][MAX_NODES];
int flowPassed[MAX_NODES][MAX_NODES];
int parentsList[MAX_NODES];
int currentPathCapacity[MAX_NODES];
vector<int> graph[MAX_NODES];
 
inline int index(char chr) {
	return chr - 'A';
}
 
 
int bfs(int begin, int end) {
 
	memset(parentsList, UNITIALIZED, sizeof(parentsList));
	memset(currentPathCapacity, NEUTRAL, sizeof(currentPathCapacity));
 
	queue<int> fifo;
	fifo.push(begin);
 
	parentsList[begin] = -2;
	currentPathCapacity[begin] = INF;
 
	while(!fifo.empty()) {
		int current = fifo.front(); fifo.pop();
 
		for(int i = 0; i < (int)graph[current].size(); i++) {
			
			int to = graph[current][i];
			
			if(parentsList[to] == UNITIALIZED) {
 
				if(capacities[current][to] - flowPassed[current][to] > 0) {
					
					parentsList[to] = current;
 
					currentPathCapacity[to] = min(currentPathCapacity[current], 
						capacities[current][to] - flowPassed[current][to]);
					
					if(to == end) return currentPathCapacity[end];
 
					fifo.push(to);
				}
			}
		}
	}
 
	return 0;
}// bfs
 
int edmondsKarp(int begin, int end) {
	
	int maxFlow = 0;
	memset(flowPassed, NEUTRAL, sizeof(flowPassed));
	
	while(true) {
 
		int flow = bfs(begin, end);
 
		if(flow == 0)
			break;
 
		maxFlow += flow;
		int current = end;
 
		while(current != begin) {
			
			int previous = parentsList[current];
			
			flowPassed[previous][current] += flow;
			flowPassed[current][previous] -= flow;
 
			current = previous;
		}
	}
 
	return maxFlow;
}
 
int main() {
 
	int n;
	scanf("%d", &n);
 
	char  a, b;
	int flow, from, to;
	for(int e = 0; e < n; e++) {
		
		scanf("\n%c %c %d", &a, &b, &flow);
		from = index(a);
		to = index(b);
 
		if(capacities[from][to] == 0) {
			graph[to].push_back(from);
			graph[from].push_back(to);
		}
		capacities[from][to] += flow;
		capacities[to][from] += flow;
 
	}
	printf("%d\n", edmondsKarp(index('A'), index('Z')));
	return 0;
} 