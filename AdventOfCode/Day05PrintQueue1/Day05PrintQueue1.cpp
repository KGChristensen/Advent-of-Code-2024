// Day05PrintQueue1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <vector>
#include <algorithm>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long resultCorrectlyOrderedUpdates = 0;
	std::vector<std::pair<int, int>> pageOrderingRules;
	std::vector<std::vector<int>> allUpdates;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line) && !line.empty()) {

		const int x = stoi(line.substr(0, 2));
		const int y = stoi(line.substr(3, 2));

		pageOrderingRules.push_back(std::make_pair(x,y));

	}

	while (std::getline(inputfile, line)) {

		std::stringstream ss_updates(line);
		std::string s_update;
		std::vector<int> v_update;
		while (std::getline(ss_updates, s_update, ',')) {
			v_update.push_back(stoi(s_update));
		}
		allUpdates.push_back(v_update);
	}

	// Loop all updates
	for (auto updates : allUpdates) {

		bool correctOrder = true;
		size_t idx = 0;

		// Loop each update
		for (auto update : updates) {

			auto containsX = [update](const std::pair<int, int>& pair) {
				return pair.first == update; };

			auto iter = std::find_if(pageOrderingRules.begin(),
				pageOrderingRules.end(),
				containsX);

			// Loop page ordering rules to find matching updates
			while (iter != pageOrderingRules.end()) {

				auto posInUpdates = std::find_if(updates.begin(), updates.end(), [iter](const auto& v) {return (v == iter->second); });

				if (posInUpdates != updates.end()) {

					if (idx >= std::distance(updates.begin(), posInUpdates)) {
						correctOrder = false;
					}

				}

				iter = std::find_if(std::next(iter),
					pageOrderingRules.end(),
					containsX);

			}

			idx++;

		}

		if (correctOrder) {
			resultCorrectlyOrderedUpdates += updates[(updates.size() - 1) / 2];
		}

	}

	inputfile.close();

	std::cout << "Results: " << resultCorrectlyOrderedUpdates << "\n";

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
