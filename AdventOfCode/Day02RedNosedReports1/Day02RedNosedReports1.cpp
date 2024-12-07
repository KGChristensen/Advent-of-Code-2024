// Day02RedNosedReports1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <list>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long safeReports = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		bool safeReport = true;
		int direction = -1; // -1 not initialized, 0 is decreasing, 1 is increasing

		std::stringstream levels(line);
		std::string level;
		long prevLLevel = 0;
		int idx = 0;
		while (levels >> level && safeReport) {

			long lLevel = atol(level.c_str());

			direction = (idx == 1 ? (lLevel > prevLLevel) : direction);

			long amount = std::abs(lLevel - prevLLevel);

			if (idx > 0) {
				if (!((direction == (lLevel > prevLLevel)) && (amount >= 1) && (amount <= 3))) {
					safeReport = false;
				}
			}

			prevLLevel = lLevel;
			idx++;
		}

		safeReports += safeReport;

	}

	inputfile.close();

	std::cout << "Reports that are safe: " << safeReports << "\n";

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
