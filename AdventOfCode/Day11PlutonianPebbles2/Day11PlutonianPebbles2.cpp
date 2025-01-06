// Day11PlutonianPebbles2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <math.h>

//static bool even(long long number) {
//
//	int digit = 0;
//
//	while (number) {
//		number /= 10;
//		digit++;
//	}
//
//	if (digit % 2 == 0) {
//		return true;
//	}
//
//	return false;
//}

static int countDigits(long long number) {
	int digit = 0;


		while (number) {
			number /= 10;
			digit++;
		}

	return digit;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long long result = 0;
	std::map<long long, long long> stoneArrangement;
	
	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		std::stringstream stones(line);

		std::string stone;

		while (std::getline(stones, stone, ' ')) {
			stoneArrangement[std::stoll(stone)]++;
		}

	}

	size_t blinks = 0;
	while (blinks < 75) {

		std::map<long long, long long> newStoneArrangement;

		for (auto stone : stoneArrangement)
		{
			const long long stoneVal = stone.first; // stoneArrangement[idx];
			const long long stoneCount = stone.second; 
			const int digitsCount = countDigits(stoneVal);

			//Rule 1: If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
			if (stoneVal == 0) {
				newStoneArrangement[1] += stoneCount;
			}
			//Rule2: If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
			else if (digitsCount % 2 == 0) {
				long long divider = std::pow(10, (digitsCount / 2));
				newStoneArrangement[(stoneVal / divider)] += stoneCount;
				newStoneArrangement[(stoneVal % divider)] += stoneCount;

			}
			//Rule 3: If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
			else {
				newStoneArrangement[(stoneVal * 2024)] += stoneCount;
			}

		}
		stoneArrangement = newStoneArrangement;
		blinks++;
	}

	auto it = stoneArrangement.begin();

	while (it != stoneArrangement.end()) {
		result += it->second;
		it = std::next(it);
	}

	inputfile.close();

	std::cout << "Results: " << result << "\n";

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
