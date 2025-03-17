#pragma once

#include "../../base/Algorithm.h"
#include "../../problems/NsqPuzzle/Puzzle.h"

class PuzzleAlgorithm: public Algorithm {
	protected:
		BoardState initialState;
		std::unordered_map<BoardState, BoardMove> action;
		std::unordered_map<BoardState, int> result;
		// std::map<BoardState, BoardMove> action;
	public:
		PuzzleAlgorithm(BoardState initialState) {
			assert(initialState.isSolvable());
			this -> initialState = initialState;
		}
		std::string makeStep() {
			std::string answer = "";
			BoardState state;
			// std::cerr << state << '\n';

			while (true) {
				BoardMove move = action[state];
				if (move == STOP) break;
				// std:: cerr << state << ' ' << move << ' ';

				switch (move)
				{
					case L:
						answer += "L";
						state = BoardState::move(state, BoardMove::R);
						break;
					case R:
						answer += "R";
						state = BoardState::move(state, BoardMove::L);
						break;
					case U:
						answer += "U";
						state = BoardState::move(state, BoardMove::D);
						break;
					case D:
						answer += "D";
						state = BoardState::move(state, BoardMove::U);
						break;
					default:
						throw std::exception();
				}
			}

			reverse(answer.begin(), answer.end());
			return answer;
		}
		long long getExpandedCount() {
			return result.size();
		}
};