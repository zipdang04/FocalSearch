#pragma once

#include "testlib.h"
#include <bits/stdc++.h>

#include "Geometry.h"
namespace Data {
	
	const int MAX_N = 100'000'000;
	const int MAX_COORDINATE = 1'000'000'000;
	struct pair_hash {
		inline std::size_t operator()(const std::pair<int,int> & v) const {
			return v.first*MAX_COORDINATE+v.second;
		}
	};
	
	void init() {
		long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		rnd.setSeed(seed);
	}
	
	std::vector<std::vector<int>> graph;
	Point points[MAX_N];
	static int n, m;
	std::vector<std::pair<int, int>> edges;
	void createGraph() {
		graph.resize(n); edges.resize(m);

		int ptr = 0;
		for (int i = 1; i < n; i++) {
			edges[ptr++] = {rnd.next(i), i};
		}
		std::cerr << "build tree done\n";
		
		while (ptr < m) { 
			int u = rnd.next(n);
			int v; do {v = rnd.next(n);} while (u == v);
			if (u > v) std::swap(u, v);
			edges[ptr++] = {u, v};
		}
		std::cerr << "build edge done\n";
		
		for (std::pair<int, int> edge: edges) {
			auto [u, v] = edge;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		std::cerr << "build graph done\n";
		// how to create a *large* single graph
	}
	void createData(int _n, int _m) {
		init();
		n = _n; m = _m;
		assert((1ll * n * (n-1) / 2 >= m));
		for (int i = 0; i < n; i++) {
			points[i] = { rnd.next(0, MAX_COORDINATE), rnd.next(0, MAX_COORDINATE) };
		}

		createGraph();
	}
	void exportData(std::string filename) {
		std::ofstream ofs(filename);
		ofs << n << ' ' << m << '\n';
		for (int i = 0; i < n; i++) ofs << points[i].x << ' ' << points[i].y << '\n';
		for (int u = 0; u < n; u++) {
			ofs << graph[u].size() << ' ';
			for (int v: graph[u]) ofs << v << ' ';
			ofs << '\n';
		}
		ofs.flush(); ofs.close();
	}
}

main(int argc, char** argv) {
	registerGen(argc, argv, 1);
	int SZ_N = opt<int>("n"), SZ_M = opt<int>("m");
	Data::createData(SZ_N, SZ_M);
	
	auto current_time = time(nullptr);
	auto local_time = localtime(&current_time);
	std::string year = std::to_string(local_time -> tm_year + 1900);
	std::string month = std::to_string(local_time -> tm_mon + 1);
	std::string day = std::to_string(local_time -> tm_mday);
	std::string hour = std::to_string(local_time -> tm_hour);
	std::string minute = std::to_string(local_time -> tm_min);
	std::string second = std::to_string(local_time -> tm_sec);
	while (month.length() < 2) month = "0" + month;
	while (day.length() < 2) day = "0" + day;
	while (hour.length() < 2) hour = "0" + hour;
	while (minute.length() < 2) minute = "0" + minute;
	while (second.length() < 2) second = "0" + second;

	std::string filename = std::format("n{}_m{}_{}{}{}-{}{}{}.inp", SZ_N, SZ_M, year, month, day, hour, minute, second);
	Data::exportData(filename);

	std::cout << filename << '\n';

}