#include "../../problems/NsqPuzzle/Puzzle.h"
#include <bits/stdc++.h>
namespace Heuristics {
	inline int manhattanDistance(BoardState state) {
		int SIZE = BoardState::SIZE;
		int answer = 0;
		for (int i = 0; i < BoardState::MAX_VALUE; i++) {
			int value = state.board[i];
			int destRow = value / SIZE, destCol = value % SIZE;
			int row = i / SIZE, col = i % SIZE;
			answer += std::abs(row - destRow) + std::abs(col - destCol);
		}
		return answer;
	}
	inline int mismatchDistance(BoardState state) {
		int SIZE = BoardState::SIZE;
		int answer = 0;
		for (int i = 0; i < BoardState::MAX_VALUE; i++)
			answer += int(!!i) * (i != state.board[i]);
		return answer;
	}
	inline int cartesianDistance(BoardState state) {
		int SIZE = BoardState::SIZE;
		int answer = 0;
		for (int i = 0; i < BoardState::MAX_VALUE; i++) {
			int value = state.board[i];
			int destRow = value / SIZE, destCol = value % SIZE;
			int row = i / SIZE, col = i % SIZE;
			row = std::abs(row - destRow);
			col = std::abs(col - destCol);
			answer += sqrt(row * row + col * col);
		}
		return answer;
	}
}