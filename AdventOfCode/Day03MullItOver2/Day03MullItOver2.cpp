// Day03MullItOver2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static std::size_t rfind_in_substr(
	const std::string& str
	, const std::size_t from
	, const std::size_t len
	, const std::string& sub
) {

	std::size_t res = from + str.substr(from, len).rfind(sub);

	return res != std::string::npos && res >= from ? res : std::string::npos;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char ch;
	std::string corruptedMemory;
	long resultsOfTheMultiplications = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (inputfile.get(ch)) {

		corruptedMemory += ch;

	}

	for (size_t idx = 4; idx <= corruptedMemory.length(); idx++) {

		while (corruptedMemory.substr(idx - 4, 4) == "mul(") {

			size_t numberIdx = idx;

			while (corruptedMemory.substr(numberIdx, 1) >= "0" && corruptedMemory.substr(numberIdx, 1) <= "9") {
				numberIdx++;
			}

			if (numberIdx == idx)
				break;

			long numberLeft = stoi(corruptedMemory.substr(idx, (numberIdx - idx)));

			size_t commaPos = numberIdx;

			if (corruptedMemory.substr(numberIdx, 1) != ",")
				break;

			numberIdx++;

			while (corruptedMemory.substr(numberIdx, 1) >= "0" && corruptedMemory.substr(numberIdx, 1) <= "9") {
				numberIdx++;
			}

			if (numberIdx == commaPos + 1)
				break;

			long numberRight = stoi(corruptedMemory.substr(commaPos + 1, (numberIdx - commaPos - 1)));

			if (corruptedMemory.substr(numberIdx, 1) != ")") {
				break;
			}

			size_t nextDont = rfind_in_substr(corruptedMemory, 0, idx, "don't()");
			size_t nextDo = rfind_in_substr(corruptedMemory, 0, idx, "do()");

			if (nextDo == std::string::npos && nextDont == std::string::npos) {
				resultsOfTheMultiplications += (numberLeft * numberRight);
			}
			else if (nextDont != std::string::npos && nextDo == std::string::npos) {}
			else if (nextDo > nextDont && nextDont != std::string::npos) {
				resultsOfTheMultiplications += (numberLeft * numberRight);
			}

			idx = numberIdx;

		}


	}


	inputfile.close();

	std::cout << "Results of the multiplications: " << resultsOfTheMultiplications << "\n";

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
