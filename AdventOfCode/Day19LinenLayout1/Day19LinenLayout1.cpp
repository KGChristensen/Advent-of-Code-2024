// Day19LinenLayout1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string_view>

static void combinePatternsFromDesign(const std::string& design, size_t startPos, const std::set<std::string>& patterns, int& sum) {

	std::stack<size_t> pos;
	std::set<size_t> visited;
	
	pos.emplace(startPos);
	
	while (!pos.empty()) {
		size_t currentPos = pos.top();
		pos.pop();
		visited.emplace(currentPos);

		for (size_t posId = (currentPos+1); posId <= design.size(); posId++) {
			const std::string designSubstr = design.substr(currentPos, posId - currentPos);

			if (std::find(patterns.begin(), patterns.end(), designSubstr) != patterns.end()) {

				if (posId >= design.size()) {
					sum++;
					return;
				}
				if (!visited.contains(posId)) pos.push(posId);

			}

		}
	}

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::getline(inputfile, line);

	std::stringstream patternsLine(line);
	std::string pattern;
	std::set<std::string> patterns;
	std::vector<std::string> designs;

	while (std::getline(patternsLine, pattern, ',')) {
		if (pattern.front() == ' ') {
			pattern.erase(0, 1);
		}
		patterns.emplace(pattern);
	}

	std::getline(inputfile, line);

	while (std::getline(inputfile, line)) {
		designs.push_back(line);
	}
	int count = 1;
	for (std::string& design : designs) {
		//std::cout << count << " - " << design.substr(0,4) << "...\n";
		int sum = 0;
		combinePatternsFromDesign(design, 0, patterns, sum);
		results += (sum > 0 ? 1 : 0);
		count++;
	}


	inputfile.close();

	std::cout << "Results: " << results << "\n";

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time taken by function: "
		<< duration.count() << " microseconds\n";
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
