// This is also a solution for the question http://www.spoj.com/problems/MTOTALF/

/*
	* Line 1: A single integer: N

	* Lines 2..N + 1: Line i+1 describes pipe i with two letters and an
	 integer, all space-separated: a_i, b_i, and F_i

	SAMPLE INPUT 

	5
	A B 3
	B C 3
	C D 5
	D Z 4
	B Z 6


	* Line 1: A single integer that the maximum flow from the well ('A')
	 to the barn ('Z')

	SAMPLE OUTPUT 

	3

*/

#include<bits/stdc++.h>

using namespace std;

typedef int ll;

#define MAX_NODES 100
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
inline int index(char chr) {
	return chr - 'A';
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