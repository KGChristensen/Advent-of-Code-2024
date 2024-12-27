// Day07BridgeRepair1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void getExprUtil(std::vector<std::string>& res, std::string curExp,
//static void getExprUtil(bool& res, std::string curExp,
	std::vector<unsigned long long int> input, unsigned long long int target, size_t pos,
	unsigned long long int curVal, unsigned long long int last) {

	if (pos == input.size())
	{
		// if current value is equal to target
		//then only add to final solution
		// if question is : all possible o/p then just
		//push_back without condition
		if (curVal == target)
			//res = true;

			res.push_back(curExp);
		return;
	}

	// loop to put operator at all positions
	for (size_t idx = pos; idx < input.size(); idx++) {

		unsigned long long int cur = input[pos];
		std::string part = std::to_string(cur);

		if (pos == 0) {
			getExprUtil(res, curExp + part, input,
				target, idx + 1, cur, cur);
		}
		else {

			getExprUtil(res, curExp + "+" + part, input,
				target, idx + 1, curVal + cur, cur);
/*			getExprUtil(res, curExp + "-" + part, input,
				target, idx + 1, curVal - cur, -cur);*/

			unsigned long long int newCurVal = curVal - last;
			newCurVal += last;
			newCurVal *= cur;

			getExprUtil(res, curExp + "*" + part, input,
				target, idx + 1, newCurVal,
				(last * cur));
			/*getExprUtil(res, curExp + "*" + part, input,
				target, idx + 1, curVal - last + last * cur,
				(last * cur));*/
		}

	}

	//res.push_back("test");


}

static std::vector<std::string> getExprs(unsigned long long int testVal, std::vector<unsigned long long int> input) {
	std::vector<std::string> res;
	getExprUtil(res,"",input, testVal,0,0,0);
	return res;
};

/*static bool getExprs(unsigned long long int testVal, std::vector<unsigned long long int> input) {
	bool res = false;
	getExprUtil(res, "", input, testVal, 0, 0, 0);
	return res;
};*/

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::pair<unsigned long long int, std::vector<unsigned long long int>>> equations;
	unsigned long long int TotalCalibrationResult = 0;
	const char operators[2] = { '+','*' };

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line)) {

		size_t colonPos = line.find_first_of(':');

		unsigned long long int testVal = std::stoull(line.substr(0, colonPos));

		std::vector<unsigned long long int> numberSets;

		std::string number;

		//std::cout <<">" << line.substr(colonPos + 2, line.length()-colonPos - 2) << "<\n";

		std::stringstream numbers(line.substr(colonPos + 2, line.length() - colonPos - 2));

		while (std::getline(numbers,number,' ')) {

			unsigned long long int num = std::stoull(number);

			numberSets.push_back(num);

		}

		equations.push_back(std::make_pair(testVal, numberSets));
		
	}

	for (auto equation : equations) {

		std::vector<std::string> res = getExprs(equation.first, equation.second);
		//bool res = getExprs(equation.first, equation.second);

		if (res.size() > 0)
		//if (res)
			TotalCalibrationResult += equation.first;

		/*for (size_t i = 0; i < res.size(); i++)
			std::cout << res[i] << " ";
		std::cout << std::endl;*/

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
