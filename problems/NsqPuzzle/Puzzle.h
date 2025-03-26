#pragma once

#include <bits/stdc++.h>

enum BoardMove{
	L,U,R,D, STOP
};
class InvalidBoardException: public std::exception {
	int row, col; BoardMove move;
	public:
		InvalidBoardException(int row, int col, BoardMove move): std::exception() {
			this -> row = row; this -> col = col; this -> move = move;
		}

		virtual const char* what() const throw() {
			std::stringstream ss;
			ss << "InvalidBoardException: tried to move " << move << " in position " << row << "." << col;

			std::string s; getline(ss, s);
			return s.c_str();
		}
};

class BoardState {
	// private:
	public:
		static int SIZE, MAX_VALUE;
		// some static functions
		static const int NaN = -1;
		static inline void changeSize(int sz) {
			assert((SIZE == 0));					// only first time;
			SIZE = sz; MAX_VALUE = sz * sz;
		}
		static inline int getIndex(int row, int col) {
			return row * SIZE + col;
		}
		static inline BoardState move(BoardState state, BoardMove move) {
			assert(SIZE != 0);
			int row = state.blankX, col = state.blankY;
			
			switch (move) {
				case L: {
					if (col <= 0) throw InvalidBoardException(row, col, move);
					int newCol = col - 1;
					std::swap(state.get(row, col), state.get(row, newCol));
					col = newCol;	
				} break;
				case R: {
					if (col >= SIZE - 1) throw InvalidBoardException(row, col, move);
					int newCol = col + 1;
					std::swap(state.get(row, col), state.get(row, newCol));
					col = newCol;	
				} break;
				case U: {
					if (row <= 0) throw InvalidBoardException(row, col, move);
					int newRow = row - 1;
					std::swap(state.get(row, col), state.get(newRow, col));
					row = newRow;	
				} break;
				case D: {
					if (row >= SIZE - 1) throw InvalidBoardException(row, col, move);
					int newRow = row + 1;
					std::swap(state.get(row, col), state.get(newRow, col));
					row = newRow;	
				} break;
				
				default:
					break;
			}
			state.blankX = row, state.blankY = col;

			return state;
		}

		// declaration
		std::vector<int> board;
		int blankX, blankY;
		BoardState() {
			assert (SIZE != 0);
			board = std::vector<int>(SIZE * SIZE);
			blankX = blankY = 0;
			iota(board.begin(), board.end(), 0);
		}
		BoardState(std::vector<int> board, int blankX = NaN, int blankY = NaN) {
			assert (SIZE != 0 and (int)board.size() == SIZE * SIZE);
			this -> board = board;
			
			if (blankX == NaN or blankY == NaN 			// not exists, or
			or board[getIndex(blankX, blankY)] != 0) { 	// wrong
				int blankIndex = find(0);
				// std::cerr << blankIndex << '\n';
				blankX = blankIndex / SIZE; 
				blankY = blankIndex % SIZE;
			}

			this -> blankX = blankX;
			this -> blankY = blankY;         
		}

		// get & find
		inline int& get(int row, int col) {
			return board[getIndex(row, col)];
		}
		inline int find(int number) {
			if (number < 0 or number > SIZE * SIZE) return NaN;
			for (int i = 0; i < board.size(); i++)
				if (number == board[i]) return i;
			return NaN;
		}

		// operator
		bool operator == (const BoardState &state) const {
			for (int i = 0; i < MAX_VALUE; i++)
				if (board[i] != state.board[i])
					return false;
			return true;
		}
		bool operator < (const BoardState &state) const {
			for (int i = 0; i < MAX_VALUE; i++)
				if (board[i] != state.board[i])
					return board[i] < state.board[i];
			return false;
		}
		bool operator > (const BoardState &state) const {
			for (int i = 0; i < MAX_VALUE; i++)
				if (board[i] != state.board[i])
					return board[i] > state.board[i];
			return false;
		}
		
		
		bool isFinished() {
			for (int i = 0; i < MAX_VALUE; i++)
				if (board[i] != i) return false;
			return true;
		}
		int countInversions() {
			unsigned long long bit = 0, count = 0;
			for (int i: board) {
				count += int(!!i) * __builtin_popcount(bit >> i);
				bit |= 1ull << i;
			}
			return count;
		}
		bool isSolvable() {
			int inversions = countInversions();
			if (SIZE % 2 == 1)
				return inversions % 2 == 0;
			else
				return (inversions + blankX) % 2 == 0;
			// the board is reversed
		}
};
std::ostream& operator << (std::ostream& out, BoardState state) {
	out << "[";
	for (int row = 0; row < BoardState::SIZE; row++) {
		for (int col = 0; col < BoardState::SIZE; col++) {
			out << state.get(row, col);
			if (col + 1 < BoardState::SIZE) out << ' ';
			else if (row + 1 < BoardState::SIZE) out << ";";
			else out << "]";
		}
	}

	return out;
}
int BoardState::SIZE = 0;
int BoardState::MAX_VALUE = 0;

template<>
struct std::hash<BoardState> {
	std::size_t operator()(const BoardState &p) const
    {
        unsigned long long num = 0;
		for (int i: p.board)
			num = (num << 5) | i;
		return num;
    }
};