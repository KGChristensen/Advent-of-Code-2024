// Day22MonkeyMarket2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <numeric>


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

	std::vector<std::vector<int>> allChanges;
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> mapSequences;

	size_t lineId = 0;
	while (std::getline(inputfile, line)) {
		long long secretNumber = std::stoll(line);
		allChanges.emplace_back();
		allChanges[lineId].reserve(generateCount); // Preallocate memory

		for (size_t generateId = 0; generateId < generateCount; generateId++) {
			allChanges[lineId].emplace_back(secretNumber % 10);
			secretNumber = generateSecretNumber(secretNumber);
		}
		lineId++;
	}
	
	for (size_t changeId = 0; changeId < allChanges.size();changeId++) {
		for (size_t secretNumberId = 4; secretNumberId < generateCount; secretNumberId++) {
			int secretNumber = allChanges[changeId][secretNumberId];
			int last = allChanges[changeId][secretNumberId - 1];
			int secondLast = allChanges[changeId][secretNumberId - 2];
			int thirdLast = allChanges[changeId][secretNumberId - 3];
			int fourthLast = allChanges[changeId][secretNumberId - 4];
			
			std::string consecutiveChanges = std::to_string(thirdLast - fourthLast) + std::to_string(secondLast - thirdLast) + std::to_string(last - secondLast) + std::to_string(secretNumber - last);

			auto consecutiveChange = mapSequences[consecutiveChanges];

			auto found = std::find_if(consecutiveChange.begin(), consecutiveChange.end(), [&changeId](std::pair<int, int>& chg) {return (chg.first == static_cast<int>(changeId)); });
			if (found == consecutiveChange.end()) {	// Not found
				mapSequences[consecutiveChanges].emplace_back(std::make_pair(changeId, secretNumber));
			}
			else {	// Found
				found->second = std::max(found->second, secretNumber);
			}

		}
	}
	
	// Compute results using accumulate
	for (const auto& [key, value] : mapSequences) {
		long long subtotal = std::accumulate(value.begin(), value.end(), 0LL,
			[](long long total, const std::pair<int, int>& p) {
				return total + p.second;
			});

		results = std::max(results, subtotal);
	}


	std::cout << "\n";

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
