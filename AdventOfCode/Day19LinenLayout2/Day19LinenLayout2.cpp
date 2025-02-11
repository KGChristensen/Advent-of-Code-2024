// Day19LinenLayout2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <set>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

static long long combinePatternsFromDesign(const std::string& design, const std::vector<std::string>& patterns, std::unordered_map<std::string, long long>& memo) {
	if (design.empty()) {
		return 1; // Found a valid combination
	}

	if (memo.find(design) != memo.end()) {
		return memo[design];
	}

	long long count = 0;
	for (const auto& pattern : patterns) {
		if (design.find(pattern) == 0) { // Pattern matches the start of the design
			count += combinePatternsFromDesign(design.substr(pattern.size()), patterns, memo);
		}
	}

	memo[design] = count;
	return count;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	//long results = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::getline(inputfile, line);

	std::stringstream patternsLine(line);
	std::string pattern;
	std::vector<std::string> patterns;
	std::vector<std::string> designs;

	while (std::getline(patternsLine, pattern, ',')) {
		if (pattern.front() == ' ') {
			pattern.erase(0, 1);
		}
		patterns.push_back(pattern);
	}

	std::getline(inputfile, line);

	while (std::getline(inputfile, line)) {
		designs.push_back(line);
	}
	long long totalValidCombinations = 0;
	for (const std::string& design : designs) {
		std::unordered_map<std::string, long long> memo;
		long long designCombinations = combinePatternsFromDesign(design, patterns, memo);
		std::cout << "Design: " << design << " - Valid Combinations: " << designCombinations << "\n";
		totalValidCombinations += designCombinations;
	}


	inputfile.close();

	std::cout << "Total valid combinations: " << totalValidCombinations << "\n";

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
