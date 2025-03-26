#pragma once
#include "PuzzleAlgorithm.h"

#pragma once

#include "PuzzleAlgorithm.h"
#include "../../problems/NsqPuzzle/Puzzle.h"
class PartialExpansion: public PuzzleAlgorithm {
	private:
		struct Data{
			BoardState state;
			int f, g;
			Data(BoardState state, int f, int g): state(state), f(f), g(g) {}
			bool operator < (Data a) const { return f != a.f ? f < a.f : (g != a.g ? g < a.g : state < a.state); }
			bool operator > (Data a) const { return f != a.f ? f > a.f : (g != a.g ? g > a.g : state > a.state); }
		};
		std::set<Data> opening, closed;
		std::unordered_map<BoardState, int> f;
		std::function<int(BoardState)> heuristic;
		int cBound;

		static int default_heuristic(BoardState state) {
			return state.countInversions() / 2;
		}
	protected:
		void execute() override {
			// std::cerr << initialState << '\n';
			result[initialState] = 0;
			f[initialState] = heuristic(initialState);
			opening.emplace(initialState, f[initialState], 0);
			action[initialState] = STOP;

			int tmp = 0;
			while (not opening.empty()) {
				if (++tmp == 10000) std::cerr << opening.size() << closed.size() << '\n';
				// std::cerr << "opening: " << '\n';
				// for (auto [board, _, _2]: opening) std::cerr << board << '\n';

				auto _it = opening.begin();  Data cur = *_it;
				opening.erase(_it);
				if (cur.state.isFinished()) return;
				// std::cerr << cur.state << "=>" << ' ' << cur.g << ' ' << cur.f << '\n';

				BoardMove avoid = action[cur.state];
				switch (avoid){
					case U: avoid = D; break;
					case D: avoid = U; break;
					case L: avoid = R; break;
					case R: avoid = L; break;
					default: break;
				}

				int minClosed = INT_MAX;
				for (const BoardMove move: {BoardMove::U, BoardMove::D, BoardMove::L, BoardMove::R}) {
					if (move == avoid) continue;
					BoardState newBoard;
					try { newBoard = BoardState::move(cur.state, move); } 
					catch (InvalidBoardException e) {  continue; }
					
					
					int newG = cur.g + 1, newF = newG + heuristic(newBoard);
					if (result.find(newBoard) != result.end() and result[newBoard] <= newG) continue;
					
					f[newBoard] = newF, result[newBoard] = newG; 
					action[newBoard] = move;
					// std::cerr << move << ": " << cur.state << "=>" << newBoard  << ' ' << newG << ' ' << newF << '\n';
					assert(newG > cur.g);
					
					Data newState(newBoard, newF, newG);

					if (newState.f <= cur.f + cBound) {
						// std::cerr << "opened" << '\n';
						auto itO = opening.lower_bound(Data(newState.state, 0, 0));
						auto itC = closed.lower_bound(Data(newState.state, 0, 0));
						// // if (itO != opening.end()) std::cerr << itO -> state << '\n'; else std::cerr << "nonsense\n";
						// // if (itC != closed.end()) std::cerr << itC -> state << '\n'; else std::cerr << "nonsense\n";
						if (itO != opening.end() and itO -> state == newState.state){
							opening.erase(itO);
							// std::cerr << "erase itO\n";
						} else if (itC != closed.end() and itC -> state == newState.state) {
							closed.erase(itC);
							// std::cerr << "erase itC\n";
						}
						
						auto shit = opening.insert(newState);
						// std::cerr << shit.second << '\n';
					} else 
						minClosed = std::min(minClosed, newState.f);
				}
				
				if (minClosed != INT_MAX)
					closed.insert(cur);
				else if (minClosed < f[cur.state]){
					result[cur.state] = minClosed;
					opening.insert(Data(cur.state, minClosed, cur.g));
				}
				// std::cerr << "doneState\n";
			}
		}
	public:
		PartialExpansion(BoardState initialState, std::function<int(BoardState)> heuristic, int cBound): PuzzleAlgorithm(initialState) {
			// std::cerr << initialState << '\n';
			this -> cBound = cBound;
			this -> heuristic = heuristic;
			algoName = "A* with Partial Expansion, cBound = " + toString(cBound);
		}
};