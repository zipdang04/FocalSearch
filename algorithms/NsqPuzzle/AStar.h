#pragma once

#include "PuzzleAlgorithm.h"
#include "../../problems/NsqPuzzle/Puzzle.h"
class AStar: public PuzzleAlgorithm {
	private:
		struct Data{
			BoardState state;
			int f, g;
			Data(BoardState state, int f, int g): state(state), f(f), g(g) {}
			bool operator < (Data a) const { return f != a.f ? f < a.f : g < a.g; }
			bool operator > (Data a) const { return f != a.f ? f > a.f : g > a.g; }
		};
		std::priority_queue<Data, std::vector<Data>, std::greater<Data>> pq;
		std::unordered_map<BoardState, int> f;
		std::function<int(BoardState)> heuristic;

		static int default_heuristic(BoardState state) {
			return state.countInversions() / 2;
		}
	protected:
		void execute() override {

			result[initialState] = 0; 
			f[initialState] = heuristic(initialState);
			action[initialState] = STOP;
			pq.emplace(initialState, f[initialState], 0);

			// int ptr = 0;
			while (!pq.empty()) {
				// if (++ptr == 2) {
				// if (++ptr == 100'000) {
					// std::cerr << pq.size() << ' ' << pq.top().f << ' ' << result[pq.top().state] << '\n';
				// 	ptr = 0;
				// }
				Data cur = pq.top(); pq.pop();
				if (f[cur.state] != cur.f) continue;
				if (cur.state.isFinished()) break;
				int curResult = result[cur.state];
				
				BoardMove avoid = action[cur.state];
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
					try {
						newState = BoardState::move(cur.state, move);
					} catch (InvalidBoardException e) {
						continue;
					}
					int newResult = curResult + 1;
					
					auto it = result.find(newState);
					if (it == result.end() or newResult < it -> second) {
						result[newState] = newResult;
						action[newState] = move;
						f[newState] = newResult + heuristic(newState);
						pq.emplace(newState, f[newState], result[newState]);
					}
				}
			}
		}
	public:
		AStar(BoardState initialState, std::function<int(BoardState)> heuristic = default_heuristic): PuzzleAlgorithm(initialState) {
			this -> heuristic = heuristic;
			algoName = "AStar";
		}
};