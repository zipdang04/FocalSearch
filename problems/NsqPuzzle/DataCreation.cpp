#pragma once

#include "testlib.h"
#include <bits/stdc++.h>
#include "Puzzle.h"
std::string getTimeCode() {
	auto curTime = std::chrono::current_zone() -> to_local(std::chrono::high_resolution_clock::now());
	// int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(curTime.time_since_epoch()).count();
	return std::format("{:%Y%m%d-%H%M%S}", curTime);
	
	
	// auto current_time = time(nullptr);
	// auto local_time = localtime(&current_time);
	// std::string year = std::to_string(local_time -> tm_year + 1900);
	// std::string month = std::to_string(local_time -> tm_mon + 1);
	// std::string day = std::to_string(local_time -> tm_mday);
	// std::string hour = std::to_string(local_time -> tm_hour);
	// std::string minute = std::to_string(local_time -> tm_min);
	// std::string second = std::to_string(local_time -> tm_sec);
	// while (month.length() < 2) month = "0" + month;
	// while (day.length() < 2) day = "0" + day;
	// while (hour.length() < 2) hour = "0" + hour;
	// while (minute.length() < 2) minute = "0" + minute;
	// while (second.length() < 2) second = "0" + second;
	// return std::format("{}{}{}-{}{}{}", year, month, day, hour, minute, second);
}

main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	rnd.setSeed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	int SZ_N = opt<int>("n"); BoardState::changeSize(SZ_N);

	int shuffle_steps = opt<int>("ctrl", 0);
	
	
	std::string prefix = std::format("NSQ-n{}", SZ_N);
	if (shuffle_steps > 0) prefix += std::format("-ctrl{}", shuffle_steps);
	std::string filename = prefix + std::format("_{}.inp", getTimeCode());
	std::cerr << "filename: " << filename << std::endl;
	std::ofstream ofs(filename);
	
	ofs << SZ_N << std::endl;
	
	BoardState state;
	if (shuffle_steps == 0) {
		do {
			std::vector<int> board(SZ_N * SZ_N);
			std::iota(board.begin(), board.end(), 0);
			shuffle(board.begin(), board.end());
			state = BoardState(board);
		} while (not state.isSolvable());
	} else {
		BoardMove all[4] = {BoardMove::D, BoardMove::L, BoardMove::U, BoardMove::R};
		int prv = 0;
		for (int i = 1; i <= shuffle_steps; i++) {
			BoardMove move;
			do {move = all[rnd.next(0, 3)];}
			while (move == (prv + 2) % 4);
			prv = move;

			try {
				BoardState tmp = BoardState::move(state, move);
				state = tmp;
			} catch (std::exception e) {}
		}
	}
	for (int i = 0; i < SZ_N; i++)
	for (int j = 0; j < SZ_N; j++)
		ofs << state.board[i * SZ_N + j] << " \n"[j == SZ_N - 1];

	ofs.flush(); ofs.close();
}