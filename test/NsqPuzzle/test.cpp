#include "testlib.h"
#include <bits/stdc++.h>
#include "../../problems/NsqPuzzle/Puzzle.h"
#include "../../algorithms/NsqPuzzle/Heuristics.h"

int n;
void TestInit() {
	std::vector<int> state(BoardState::MAX_VALUE);
	iota(state.begin(), state.end(), 0);
	BoardState board(state);
	ensure(board.blankX == 0);
	ensure(board.blankY == 0);
	ensure(board.isFinished());
	// std::cerr << "finished init";
}
void TestMove() {
	std::vector<int> state(BoardState::MAX_VALUE);
	iota(state.begin(), state.end(), 0);
	BoardState board(state);

	try {
		board = BoardState::move(board, U);
		quitf(_wa, "Cannot move up");
	} catch (std::exception e) {
		return;
	}
}

void TestHeuristics() {
	if (n == 3) {
		std::vector<int> state = {2, 1, 5, 8, 3, 4, 6, 0, 7};
		BoardState board(state);
		std::cerr << Heuristics::manhattanDistance(board) << '\n';
		ensure(Heuristics::manhattanDistance(board) == 12);
	}
	if (n == 4) {
		std::vector<int> state = {5,7,6,14,2,1,11,0,9,13,4,10,15,8,3,12};
		BoardState board(state);
		std::cerr << Heuristics::manhattanDistance(board) << '\n';
	}
}

int main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	n = opt<int>("n");
	// registerTestlibCmd(argc, argv);
	// registerValidation();
	BoardState::changeSize(n);

	TestInit();
	TestMove();
	TestHeuristics();
}