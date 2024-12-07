// Day01HistorianHysteria1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	std::list<long> leftLocationIds;
	std::list<long> rightLocationIds;
	long totalDistance = 0L;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		std::stringstream ids(line);
		std::string id;
		ids >> id;

		leftLocationIds.push_back(atol(id.c_str()));
		ids >> id;

		rightLocationIds.push_back(atol(id.c_str()));

	}

	leftLocationIds.sort();
	rightLocationIds.sort();

	std::list<long>::const_iterator lIt = leftLocationIds.begin();
	std::list<long>::const_iterator rIt = rightLocationIds.begin();

	for (; lIt != leftLocationIds.end() && rIt != rightLocationIds.end(); ++lIt, ++rIt)
	{
		totalDistance += std::abs(*rIt - *lIt);
	}

	inputfile.close();

	std::cout << "Total distance: " << totalDistance << "\n";

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
