#pragma once

#include <bits/stdc++.h>
#include "Exception.h"

class Algorithm{
	protected:
		// static
		std::string algoName;
		bool hasRun = false;
		
		virtual void execute() {
			throw NotImplementedException();
		};
	public:
		std::string getName() {return algoName;}
		void changeName(std::string name) {algoName = name;}

		double measure() {
			auto beginTime = std::chrono::high_resolution_clock::now().time_since_epoch();
			execute(); hasRun = true; std::cerr << "done!\n";
			auto endTime = std::chrono::high_resolution_clock::now().time_since_epoch();
			auto duration = endTime - beginTime;
			long long count = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
			return count / 1'000'000.0;
		};
		virtual ~Algorithm() {};
};