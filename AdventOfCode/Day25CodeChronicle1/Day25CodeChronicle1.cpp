// Day25CodeChronicle1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <numeric>
#include <algorithm>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;
	std::vector<std::vector<int>> schematicLocks;
	std::vector<std::vector<int>> schematicKeys;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	int id = 0;
	bool isLock = false;

	while (std::getline(inputfile, line)) {

		if (id == 0) {

			if (line.find('#') != std::string::npos) {
				isLock = true;
				schematicLocks.push_back(std::vector<int>({ -1,-1,-1,-1,-1 }));
			}
			else {
				schematicKeys.push_back(std::vector<int>({ -1,-1,-1,-1,-1 }));
			}
		}

		for (size_t idCh = 0; idCh < line.size();idCh++) {
			if (line[idCh] == '#') {
				if (isLock) {
					schematicLocks[schematicLocks.size() - 1][idCh]++;
				}
				else {
					schematicKeys[schematicKeys.size() - 1][idCh]++;
				}
			}

		}

		id++;

		if (line.size() == 0) {
			id = 0;
			isLock = false;
		}
		
	}


	for (auto schematicLock : schematicLocks) {
		for (auto schematicKey : schematicKeys) {
			bool overlap = false;
			for (size_t pinPosition = 0; pinPosition < 5; pinPosition++) {
				if (schematicLock[pinPosition] + schematicKey[pinPosition] > 5)
					overlap = true;
			}
			if (!overlap)
				results++;
		}
	}

	inputfile.close();

	std::cout << "Results: " << results << "\n";

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

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
