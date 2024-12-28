// Day07BridgeRepair2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void getExprUtil(size_t pos, unsigned long long int sum, unsigned long long int target, std::vector<unsigned long long int>& input, bool& ok) {

	if (pos == input.size()) {
		if (sum == target) {
			ok = true;
		}
		return;
	}
	getExprUtil(pos + 1, sum + input[pos], target, input, ok);
	getExprUtil(pos + 1, sum * input[pos], target, input, ok);
	getExprUtil(pos + 1, std::stoull(std::to_string(sum) + std::to_string(input[pos])), target, input, ok);

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::pair<unsigned long long int, std::vector<unsigned long long int>>> equations;
	unsigned long long int TotalCalibrationResult = 0;
	
	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		size_t colonPos = line.find_first_of(':');

		unsigned long long int testVal = std::stoull(line.substr(0, colonPos));

		std::vector<unsigned long long int> numberSets;

		std::string number;

		std::stringstream numbers(line.substr(colonPos + 2, line.length() - colonPos - 2));

		while (std::getline(numbers, number, ' ')) {

			unsigned long long int num = std::stoull(number);

			numberSets.push_back(num);

		}

		equations.push_back(std::make_pair(testVal, numberSets));

	}

	for (auto equation : equations) {


		bool ok = false;
		getExprUtil(1, equation.second[0], equation.first, equation.second,ok);
		if (ok)
			TotalCalibrationResult += equation.first;

	}

	std::cout << "\n";

	inputfile.close();

	std::cout << "Results: " << TotalCalibrationResult << "\n";

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
