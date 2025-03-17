#include <bits/stdc++.h>
#include "../../algorithms/SSSP_2DPlane/Dijkstra.h"
#include "../../algorithms/SSSP_2DPlane/AStar.h"

int n, m;
std::vector<std::vector<int>> graph;
Point points[100'000'000];

void input() {
	std::ios_base::sync_with_stdio(false);
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
		std::cin >> points[i].x >> points[i].y;

	graph.resize(n);
	for (int u = 0; u < n; u++) {
		int sz; std::cin >> sz;
		graph[u].resize(sz);
		for (int i = 0; i < sz; i++) {
			int v; std::cin >> v;
			graph[u].push_back(v);
		}
	}
}

std::vector<Algorithm*> algorithms;

int main(int argc, char const *argv[])
{
	input();
	std::cout << std::fixed;
	std::cerr << std::fixed;

	algorithms.push_back(new Dijkstra(n, m, &graph, points));
	algorithms.push_back(new AStar(n, m, &graph, points));
	for (Algorithm *algorithm: algorithms) {
		std::cerr << "start " << algorithm -> getName() << '\n';
		double timeUsed = algorithm -> measure();
		std::cerr << "execution time: " << timeUsed << '\n';

		algorithm -> ~Algorithm();
	}
	return 0;
}
