// Day13ClawContraption1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;
	const int maxClick = 100;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		int tokens = INT_MAX;

		size_t len = line.length();
		size_t commaPos = line.find(',', 0);

		//button A
		int aX = stoi(line.substr(12, commaPos - 12));
		int aY = stoi(line.substr(commaPos + 4, len - commaPos - 4));

		//button B
		std::getline(inputfile, line);
		len = line.length();
		commaPos = line.find(',', 0);
		int bX = stoi(line.substr(12, commaPos - 12));
		int bY = stoi(line.substr(commaPos + 4, len - commaPos - 4));

		//Prize
		std::getline(inputfile, line);
		len = line.length();
		commaPos = line.find(',', 0);
		int xPrize = stoi(line.substr(9, commaPos - 9));
		int yPrize = stoi(line.substr(commaPos + 4, len - commaPos - 4));
		std::getline(inputfile, line);


		for (int idxX = 0; idxX <= maxClick; idxX++) {
			for (int idxY = 0; idxY <= maxClick; idxY++) {

				if ((aX * idxX) + (bX * idxY) == xPrize && (aY * idxX) + (bY * idxY) == yPrize) {
					tokens = std::min(tokens,(idxX * 3) + idxY);
				}

			}
		}

		if (tokens != INT_MAX)
			results += tokens;

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
