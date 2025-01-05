// Day11PlutonianPebbles1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static bool even(long long number) {

	int digit = 0;

	while (number) {
		number /= 10;
		digit++;
	}

	if (digit % 2 == 0) {
		return true;
	}

	return false;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;
	std::vector<long long> stoneArrangement;
	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		std::stringstream stones(line);

		std::string stone;

		while (std::getline(stones, stone, ' ')) {
			stoneArrangement.push_back(std::stoll(stone));
		}

	}
	
	size_t blinks = 0;
	while (blinks < 25) {

		std::vector<long long>::size_type size = stoneArrangement.size();
		for (std::vector<long long>::size_type idx = 0; idx < size; ++idx)
		{
			//Rule 1: If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
			if (stoneArrangement[idx] == 0) {
				stoneArrangement[idx] = 1;
			}
			//Rule2: If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
			else if (even(stoneArrangement[idx])) {
				const std::string tmpNumber = std::to_string(stoneArrangement[idx]);
				stoneArrangement[idx] = std::stoll(tmpNumber.substr(0, tmpNumber.length() / 2));
				stoneArrangement.insert(stoneArrangement.begin() + idx + 1, std::stoll(tmpNumber.substr((tmpNumber.length() / 2), tmpNumber.length() / 2)));
				++size;
				idx++;
			}
			//Rule 3: If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
			else {
				stoneArrangement[idx] *= 2024;
			}

		}
		blinks++;
	}

	//auto it = stoneArrangement.begin();

	//while (it != stoneArrangement.end()) {
	//	//std::cout << ">" << *it << "<\n";
	//	std::cout << *it << " ";

	//	it = std::next(it);
	//}

	std::cout << "\n";


	inputfile.close();

	std::cout << "Results: " << stoneArrangement.size() << "\n";

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
