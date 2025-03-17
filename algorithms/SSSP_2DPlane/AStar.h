#pragma once

#include "GraphAlgorithm.h"

class AStar: public GraphAlgorithm{
	private:
		const int NaN = -1;
		std::priority_queue<State<double>, std::vector<State<double>>, std::greater<State<double>>> pq;
		std::vector<double> result, f;

		double predictionToGoal(Point p) {
			return (points[DEST] - p).abs();
		}
		inline void process() {
			result.resize(n, NaN);
			f.resize(n, NaN);
			std::cerr << "start!" << std::endl;
			
			result[START] = 0; f[START] = predictionToGoal(points[START]);
			pq.emplace(START, f[START]);
			while (not pq.empty()) {
				State<double> current = pq.top(); pq.pop();
				if (f[current.node] != current.value) continue;
				if (current.node == DEST) break;
					// std::cerr << current.node << ' ' << current.value << '\n';

				for (int neighbor: (*graph)[current.node]) {
					double newRes = (points[neighbor] - points[current.node]).abs();
					if (result[neighbor] < 0 or newRes < result[neighbor]) {
						result[neighbor] = newRes;
						f[neighbor] = result[neighbor] + predictionToGoal(points[neighbor]);
						pq.emplace(neighbor, f[neighbor]);
					}
				}
			}

			std::cout << result[DEST] << '\n';
		}
	public:
		AStar(int n, int m, std::vector<std::vector<int>> *graph, Point *points): GraphAlgorithm(n, m, graph, points) {
			algoName = "AStar";
		}
		void execute() override {
			process();
		}
};
