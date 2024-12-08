// Day02RedNosedReports2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static bool checkReports(const std::vector<long> reports) {

	const bool isIncreasing = (reports[1] > reports[0]);
	const bool isDecreasing = (reports[1] < reports[0]);

	for (size_t reportIdx = 1; reportIdx < reports.size(); reportIdx++) {

		const long diff = (reports[reportIdx] - reports[reportIdx - 1]);

		if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;

		if (isIncreasing && (diff <= 0)) return false;
		if (isDecreasing && (diff >= 0)) return false;

	}

	return true;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long safeReports = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		std::stringstream levels(line);
		std::string level;
		std::vector<long> reports;
		while (levels >> level) {
			reports.push_back(atol(level.c_str()));
		}

		if (checkReports(reports)) 
		{ 
			safeReports++; 
		} else {

			size_t reportLength = reports.size();
			
			for (size_t reportIdx = 0; reportIdx < reportLength; reportIdx++) {

				std::vector<long> newReports(reports.begin(), reports.end());

				newReports.erase(newReports.begin() + reportIdx);

				if (checkReports(newReports))
				{
					safeReports++;
					reportIdx = reportLength;
				}

			}

		}

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
