// Day22MonkeyMarket1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <cmath>


static long long generateSecretNumber(long long secretNumber) {
    constexpr long long MODULO = 16777216;

    // Step 1
    secretNumber ^= (secretNumber * 64);
    secretNumber %= MODULO;

    // Step 2
    secretNumber ^= (secretNumber >> 5); // Equivalent to division by 32
    secretNumber %= MODULO;

    // Step 3
    secretNumber ^= (secretNumber * 2048);
    secretNumber %= MODULO;

    return secretNumber;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long long results = 0;
	const size_t generateCount = 2000;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {
		long long secretNumber = std::stoll(line);

		for (size_t generateId = 0; generateId < generateCount; generateId++) {
			secretNumber = generateSecretNumber(secretNumber);
		}
		//std::cout << secretNumber << "\n";
		results += secretNumber;

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
