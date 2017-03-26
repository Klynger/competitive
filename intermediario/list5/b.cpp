#include<bits/stdc++.h>

using namespace std;

typedef int ll;

#define MAX_NODES 101
#define INF 1005
#define UNITIALIZED -1 // value for node with no parent
#define PARENT_FOR_ROOT -2 // value for the source node's parent
#define NEUTRAL 0

ll capacities[MAX_NODES][MAX_NODES];
ll flowPassed[MAX_NODES][MAX_NODES];
int parentsList[MAX_NODES];
ll currentPathCapacity[MAX_NODES];
vector<int> graph[MAX_NODES];

ll bfs(int source, int sink) {

	memset(parentsList, UNITIALIZED, sizeof(parentsList));
	memset(currentPathCapacity, NEUTRAL, sizeof(currentPathCapacity));

	queue<int> fifo;
	fifo.push(source);

	parentsList[source] = PARENT_FOR_ROOT;
	currentPathCapacity[source] = INF;

	while(!fifo.empty()) {
		int current = fifo.front(); fifo.pop();

		for(int to : graph[current]) {
			
			if(parentsList[to] == UNITIALIZED) {
			
				if(capacities[current][to] - 
					flowPassed[current][to] > 0) {

					parentsList[to] = current;

					currentPathCapacity[to] = min(currentPathCapacity[current], 
						capacities[current][to] - flowPassed[current][to]);

					if(to == sink) 
						return currentPathCapacity[sink];
					else
						fifo.push(to);
				}
			}
		}
	}

	return 0;
}


int edmondsKarp(int source, int sink) {

	ll maxFlow = 0;
	memset(flowPassed, NEUTRAL, sizeof(flowPassed));

	while(true) {

		ll flow = bfs(source, sink);

		if(flow == 0)
			break;

		maxFlow += flow;

		// add the passed flow to the edges and 
		// remove from the opposite edges
		int current = sink;
		while(current != source) {
			int previous = parentsList[current];

			flowPassed[previous][current] += flow;
			flowPassed[current][previous] -= flow;

			current = previous;
		}// while
	}// while

	return maxFlow;
}// edmondsKarp

// ----------------------------------------------------

int main() {
 
	int network = 1;
	int n, source, sink, connections, from, to, bandwidth;
	while(true) {

		scanf("%d", &n);

		if (n == 0)
			break;
		
		memset(capacities, 0, sizeof(capacities));
		for(int i = 1; i <= n; i++)
			graph[i].clear();

		scanf("%d%d%d", &source, &sink, &connections);

		for(int i = 0; i < connections; i++) {
			
			scanf("%d%d%d", &from, &to, &bandwidth);
			
			if(capacities[from][to] == 0) {
				graph[from].push_back(to);
				graph[to].push_back(from);				
			}
			
			capacities[from][to] += bandwidth;
			capacities[to][from] += bandwidth;
		}// for

		ll ans = edmondsKarp(source, sink);

		printf("Network %d\n", network++);
		printf("The bandwidth is %d.\n\n", ans);
	}// while

	return 0;
}// main