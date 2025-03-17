#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
	int n = G.size();
	vector<int> distances(n, INF);
	vector<bool> visited(n, false);
	previous.resize(n, -1);

	distances[source] = 0;
	previous[source] = -1;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({0, source});

	while(!pq.empty()){
		int current_distance = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		if(visited[u]){
			continue;
		}

		visited[u] = true;

		for(const Edge& e: G[u]){
			int v = e.dst;
			int weight = e.weight;

			if(!visited[v] && current_distance + weight < distances[v]){
				distances[v] = current_distance + weight;
				previous[v] = u;
				pq.push({distances[v], v});
			}
		}
	}
	return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
	vector<int> path;

	for(int i = destination; i != -1; i = previous[i]){
		path.push_back(i);
		
	}

	reverse(path.begin(), path.end());
	return path;
}

void print_path(const vector<int>& v, int total){
	for(size_t i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "Total cost is " << total << endl;
}
