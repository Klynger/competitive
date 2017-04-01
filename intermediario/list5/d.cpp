#include<bits/stdc++.h>

using namespace std;

typedef int ll;

#define MAX_NODES 110
#define INF 100005
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

// -------------------------------------------------------------

void recieveNodeCapacities(const int M) {
	
	int machine, capacity;
	for(int i = 0; i < M-2; i++) {
		
		scanf("%d%d", &machine, &capacity);

		graph[machine].push_back(machine+M);
		graph[machine+M].push_back(machine);

		capacities[machine][machine+M] = capacity;
	}

	graph[1].push_back(M+1);
	graph[M+1].push_back(1);
	
	capacities[1][M+1] = INF;

	graph[M].push_back(M<<1);
	graph[M<<1].push_back(M);

	capacities[M][M<<1] = INF;
	capacities[M<<1][M] = INF;

}

void recieveNormalConnections(const int M, const int W) {
	
	int from, to, capacity;

	for(int i = 0; i < W; i++) {
		
		scanf("%d%d%d", &from, &to, &capacity);

		from += M;
		if(capacities[from][to] == 0 && capacities[to][from] == 0) {
			graph[from].push_back(to);
			graph[to].push_back(from);			
		}

		capacities[from][to] += capacity;
		capacities[to][from] += capacity;

	}// for

}// recieveNormalConnections


int main () {
	int m, w;
	while(true) {
		scanf("%d%d", &m, &w);

		if(m == 0 && w == 0) 
			break;

		memset(capacities, 0, sizeof(capacities));
		for(int i = 0; i < MAX_NODES; i++)
			graph[i].clear();

		recieveNodeCapacities(m);
		recieveNormalConnections(m, w);
		printf("%d\n", edmondsKarp(1, m));

	}// while

	return 0;
}
