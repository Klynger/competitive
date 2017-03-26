#include<bits/stdc++.h>

using namespace std;

#include<bits/stdc++.h>

using namespace std;

typedef int ll;

#define MAX_NODES 210
#define INF 1000005
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

void recieveNodeCapacities(const int N) {
	
	int capacity;
	for(int node = 1; node <= N; node++) {
		scanf("%d", &capacity);
		graph[node].push_back(node+N);
		graph[node+N].push_back(node);
		capacities[node][node+N] = capacity;
	}

}

void recieveNormalConnections(const int N,  const int M) {
	int from, to, capacity;

	for(int i = 0; i < M; i++) {

		scanf("%d%d%d", &from, &to, &capacity);

		from += N; // output node
		
		if (capacities[from][to] == 0 && capacities[to][from] == 0) {
			graph[from].push_back(to);
			graph[to].push_back(from);
		}

		capacities[from][to] += capacity;
	}// for
}// recieveNormalConnections


#define BARISAL 0
#define DHAKA 205

void recieveBarisalConnetions(const int B) {
	
	int node;
	for(int i = 0; i < B; i++) {
		
		scanf("%d", &node);
		
		graph[BARISAL].push_back(node);
		graph[node].push_back(BARISAL);
		
		capacities[BARISAL][node] = INF;
	}
}

void recieaveDhakaConnections(const int N, const int D) {
	
	int node;
	for(int i = 0; i < D; i++) {

		scanf("%d", &node);
		node += N;
		
		graph[DHAKA].push_back(node);
		graph[node].push_back(DHAKA);
		
		capacities[node][DHAKA] = INF;
	}
}

int main () {
	int n, m, b, d;

	while(scanf("%d", &n) != EOF) {

		memset(capacities, 0, sizeof(capacities));
		for(int i = 0; i < MAX_NODES; i++) 
			graph[i].clear();

		recieveNodeCapacities(n);
		scanf("%d", &m);
		recieveNormalConnections(n, m);
		scanf("%d%d", &b, &d);
		recieveBarisalConnetions(b);
		recieaveDhakaConnections(n, d);
		printf("%d\n", edmondsKarp(BARISAL, DHAKA));
	}

	return 0;
}
