#include "dijkstras.h"

int main(){
	Graph G;
	file_to_graph("graph.txt", G);

	int source = 0;
	int destination = 4;

	vector<int> previous;
	vector<int> distances = dijkstra_shortest_path(G, source, previous);

	vector<int> path = extract_shortest_path(distances, previous, destination);

	int total_cost = distances[destination];
	print_path(path, total_cost);

	return 0;
}