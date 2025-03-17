#pragma once

#include <bits/stdc++.h>
#include "GraphAlgorithm.h"

class Dijkstra: public GraphAlgorithm{
	private:
		const int NaN = -1;
		std::priority_queue<State<double>, std::vector<State<double>>, std::greater<State<double>>> pq;
		std::vector<double> result;
		inline void process() {
			result.resize(n, NaN);
			std::cerr << "start!" << std::endl;
			
			result[START] = 0; pq.emplace(START, 0);
			while (not pq.empty()) {
				State<double> current = pq.top(); pq.pop();
				if (result[current.node] != current.value) continue;
				if (current.node == DEST) break;

				for (int neighbor: (*graph)[current.node]) {
					double newRes = (points[neighbor] - points[current.node]).abs();
					if (result[neighbor] < 0 or newRes < result[neighbor]) {
						result[neighbor] = newRes;
						pq.emplace(neighbor, newRes);
					}
				}
			}

			std::cout << result[DEST] << '\n';
		}
	public:
		Dijkstra(int n, int m, std::vector<std::vector<int>> *graph, Point *points): GraphAlgorithm(n, m, graph, points) {
			algoName = "Dijkstra";
		}
		void execute() override {
			process();
		}
};
