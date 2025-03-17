#pragma once

#include "PuzzleAlgorithm.h"
#include "../../problems/NsqPuzzle/Puzzle.h"

class FocalSearch: public PuzzleAlgorithm {
	private:
		struct SearchState{
			BoardState board;
			int f, g, h;
			SearchState(BoardState board, int f, int g, int h): board(board), f(f), g(g), h(h) {}
			bool operator == (SearchState state) const {
				return state.board == board and f == state.f and g == state.g and h == state.h;
			}
		};
		struct CompareF {
			static bool operator() (SearchState a, SearchState b) {
				if (a.f != b.f) return a.f < b.f;
				if (a.g != b.g) return a.g < b.g;
				if (a.h != b.h) return a.h < b.h;
				return a.board < b.board;
			}
		};
		struct CompareH {
			static bool operator() (SearchState a, SearchState b) {
				if (a.h != b.h) return a.h < b.h;
				if (a.g != b.g) return a.g < b.g;
				if (a.f != b.f) return a.f < b.f;
				return a.board < b.board;
			}
		};

		std::function<int(BoardState)> hFunc, focalFunc;
		std::unordered_map<BoardState, int> f;
		std::set<SearchState, CompareF> openList;
		std::set<SearchState, CompareH> focalList;
		double eps;
		
		void execute() override {
			result[initialState] = 0; action[initialState] = BoardMove::STOP;
			f[initialState] = hFunc(initialState);
			SearchState original(initialState, f[initialState], 0, f[initialState]);
			focalList.insert(original);
			openList.insert(original);
			
			while (not focalList.empty()) {
				const int fMin = openList.begin() -> f;
				SearchState node = *focalList.begin();
				// std::cerr << "sz: " << openList.size() << ' ' << focalList.size() << "||||";
				// std::cerr << "open: " << openList.begin() -> f << ' ' << openList.rbegin() -> f << "|";
				// std::cerr << "focal: " << focalList.begin() -> h << ' ' << focalList.rbegin() -> h << "|";
				// std::cerr << node.board << ' ' << node.f << ' ' << node.g << ' ' << node.h << '\n';
				focalList.erase(node); 
				openList.erase(node);
				if (node.board.isFinished()) return;
				// std::cerr << "continue\n";

				BoardMove avoid = action[node.board];
				switch (avoid){
					case U: avoid = D; break;
					case D: avoid = U; break;
					case L: avoid = R; break;
					case R: avoid = L; break;
					default: break;
				}
				for (BoardMove move: {BoardMove::U, BoardMove::D, BoardMove::L, BoardMove::R}) {
					if (move == avoid) continue;

					BoardState newState;
					try { newState = BoardState::move(node.board, move);} 
					catch (InvalidBoardException e) { continue; }
					int newG = node.g + 1, newH = hFunc(newState);
					SearchState newNode(newState, newG + newH, newG, newH);
					// std::cerr << "> " << newState << ' ' << newNode.f << ' ' << newNode.g << ' ' << newNode.h << '\n';
					
					auto it = result.find(newState);
					if (it != result.end()) {
						if (newNode.g > it -> second) {
							// std:: cerr << " >> old is better: " << result[newState] << ' ' << it -> second << '\n';
							assert(result[newState] == it -> second);
							assert(f[newState] == it -> second + hFunc(newState));
							continue;
						}
						openList.erase(SearchState(newState, f[newState], result[newState], newNode.h));
					}
					f[newState] = newNode.f;
					result[newState] = newNode.g;
					action[newState] = move;
					// std::cerr << ">> pass | h =" << newNode.h << " | f = " << f[newState] << "\n";

					openList.insert(newNode);
					if (f[newState] <= round(fMin * eps))
						focalList.insert(newNode);
				}
				
				// std::cerr << "> current fMin = " << fMin << '|' << " openList fMin: " << (openList.empty() ? -1 : openList.begin() -> f) << '\n';
				if (not openList.empty() and fMin < openList.begin() -> f) {
					// std::cerr << ">> needupdate\n"; 
					int newBound = round((openList.begin() -> f) * eps);
					auto it = openList.lower_bound({BoardState(), fMin, 0, 0});
					while (it -> f <= newBound) {
						// std::cerr << "add ";
						// std::cerr << ">>> " << it -> board << ' ' << it -> f << " " << hFunc(it -> board) << '\n';
						focalList.insert(*it);
						it++;
					}
					// std::cerr << '\n';
				}
			}
			// std::cerr << "done\n";
		}
	public:
		FocalSearch(BoardState initialState, std::function<int(BoardState)> hFunc, std::function<int(BoardState)> focalFunc, double eps = 1.1)
			: PuzzleAlgorithm(initialState), hFunc(hFunc), focalFunc(focalFunc), eps(eps) {
			algoName = "Focal Search";
		}
};
