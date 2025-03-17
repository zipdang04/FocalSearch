#pragma once

#include <bits/stdc++.h>
#include "../../base/Algorithm.h"
#include "../../problems/SSSP_2DPlane/Geometry.h"

class GraphAlgorithm: public Algorithm {
	protected:
		int n, m;
		std::vector<std::vector<int>> *graph;
		Point *points;
		int START, DEST;
	public:
		GraphAlgorithm(int n, int m, std::vector<std::vector<int>> *graph, Point *points) {
			this -> n = n;
			this -> m = m;
			this -> graph = graph;
			this -> points = points;
			START = 0; DEST = n-1;
		}
};

template <class T> struct State{
	int node; T value;
	State() { value = node = 0;}
	State(int node, T value): node(node), value(value) {}	
};
template <class T> 
bool operator < (State<T> a, State<T> b) { return a.value < b.value; }
template <class T> 
bool operator > (State<T> a, State<T> b) { return a.value > b.value; }