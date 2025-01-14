// Day13ClawContraption2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	long long results = 0;
	const long long additional = 10000000000000;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		long long tokens = 0;

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
		long long xPrize = additional + stoll(line.substr(9, commaPos - 9));
		long long yPrize = additional + stoll(line.substr(commaPos + 4, len - commaPos - 4));
		std::getline(inputfile, line);

		
		long long lY = ((xPrize * aY) - (yPrize * aX));
		long long rY = ((aY * bX) - (bY * aX));

		long long y = lY / rY;

		long long lX = (xPrize - (bX * y));

		long long x = lX / aX;
			
		if ((lY % rY) == 0 && (lX % aX) == 0)
			tokens = (x * 3LL) + y;

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
