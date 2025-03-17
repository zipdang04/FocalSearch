#pragma once

#include "PuzzleAlgorithm.h"
#include "../../problems/NsqPuzzle/Puzzle.h"
class BreadthFirstSearch: public PuzzleAlgorithm {
	private:
		std::queue<BoardState> q;
	protected:
		void execute() override {
			action[initialState] = STOP; q.push(initialState);
			result[initialState] = 0;
			int ptr = 0;
			while (!q.empty()) {
				if (++ptr == 1'000'000) {
					std::cerr << q.size() << ' ' << result[q.front()] << '\n';
					ptr = 0;
				}
				BoardState board = q.front(); q.pop();
				int boardDist = result[board];
				BoardMove avoid = action[board];
				switch (avoid){
					case U: avoid = D; break;
					case D: avoid = U; break;
					case L: avoid = R; break;
					case R: avoid = L; break;
					default: break;
				}

				for (BoardMove move: {BoardMove::U, BoardMove::D, BoardMove::L, BoardMove::R}) {
					if (move == avoid) continue;

					try {
						BoardState newState = BoardState::move(board, move);
						if (action.find(newState) != action.end()) continue;
	
						action[newState] = move;
						result[newState] = boardDist + 1;

						q.push(newState);
						if (newState.isFinished()) break;
					} catch (InvalidBoardException e) { 
					}
				}
			}
		}
	public:
		BreadthFirstSearch(BoardState initialState): PuzzleAlgorithm(initialState) {
			algoName = "BreadthFirstSearch";
		}
};