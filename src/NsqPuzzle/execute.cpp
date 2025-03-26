#include "testlib.h"
#include <bits/stdc++.h>
#include "../../problems/NsqPuzzle/Puzzle.h"
#include "../../algorithms/NsqPuzzle/PuzzleAlgorithm.h"
#include "../../algorithms/NsqPuzzle/FS.h"
#include "../../algorithms/NsqPuzzle/PFS.h"
#include "../../algorithms/NsqPuzzle/BFS.h"
#include "../../algorithms/NsqPuzzle/AStar.h"
#include "../../algorithms/NsqPuzzle/Heuristics.h"
#include "../../algorithms/NsqPuzzle/PE.h"

int n;
std::vector<int> state;

void input() {
	std::ios_base::sync_with_stdio(false);
	std::cin >> n; 
	state.resize(n * n); BoardState::changeSize(n);
	
	for (int& i: state) std::cin >> i;
}

int h1(BoardState state) {
	int answer = 0;
	for (int i = 0; i < state.board.size(); i++)
		answer += state.board[i] == i;
	return answer;
}
int hManhattan(BoardState state) {
	return Heuristics::manhattanDistance(state) / 2;
}

std::vector<Algorithm*> algorithms;

int main(int argc, char **argv)
{
	registerGen(argc, argv, 1);
	rnd.setSeed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	input();
	const BoardState board = BoardState(state);

	// algorithms.push_back(new BreadthFirstSearch(board));
	// algorithms.push_back(new AStar(board, Heuristics::mismatchDistance));
	// algorithms.push_back(new AStar(board));
	// algorithms.push_back(new AStar(board, Heuristics::manhattanDistance));
	algorithms.push_back(new FocalSearch(board, Heuristics::manhattanDistance, Heuristics::manhattanDistance));
	algorithms.push_back(new ProbabilisticFocalSearch(board, Heuristics::manhattanDistance, Heuristics::manhattanDistance, 0.6));
	algorithms.push_back(new PartialExpansion(board, Heuristics::manhattanDistance, 3));
	algorithms.push_back(new ProbabilisticFocalSearch(board, Heuristics::manhattanDistance, Heuristics::manhattanDistance, 0.95));
	// algorithms.push_back(new AStar(board, Heuristics::cartesianDistance));
	// algorithms.push_back(new AStar(board, hManhattan));
	// algorithms.push_back(new Dijkstra(n, m, &graph, points));
	// algorithms.push_back(new AStar(n, m, &graph, points));
	for (Algorithm *algorithm: algorithms) {
		std::cerr << algorithm->getName() << std::endl;
		std::cout << "start " << algorithm -> getName() << '\n';
		double timeUsed = algorithm -> measure();
		std::cout << "count of expanded nodes: " << ((PuzzleAlgorithm*) algorithm) -> getExpandedCount() << '\n';
		std::cout << "steps: " << ((PuzzleAlgorithm*) algorithm) -> makeStep() << '\n';
		std::cout << "execution time: " << timeUsed << '\n';
		algorithm -> ~Algorithm();
	}
	return 0;
}
