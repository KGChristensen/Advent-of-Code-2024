// Day04CeresSearch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::string> wordSearch;
	long resultsTimesXMASAppear = 0;
	const std::string x_mas = "MAS";
	size_t lineIdx = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {
		wordSearch.push_back(line);
	}

	const size_t lineSize = wordSearch[0].size();
	const size_t lineCount = wordSearch.size();

	for (auto ln : wordSearch) {

		if (lineIdx <= (lineCount - 3)) {

			for (size_t charIdx = 0; charIdx < lineSize; charIdx++) {

				if (charIdx <= (lineSize - 3)) {


					//M.M
					//.A.
					//S.S
					if (wordSearch[lineIdx][charIdx] == x_mas[0] &&
						wordSearch[lineIdx][charIdx+2] == x_mas[0] &&
						wordSearch[lineIdx + 1][charIdx + 1] == x_mas[1] &&
						wordSearch[lineIdx + 2][charIdx] == x_mas[2] &&
						wordSearch[lineIdx + 2][charIdx + 2] == x_mas[2]) {
						++resultsTimesXMASAppear;
					}

					//S.S
					//.A.
					//M.M
					if (wordSearch[lineIdx][charIdx] == x_mas[2] &&
						wordSearch[lineIdx][charIdx + 2] == x_mas[2] &&
						wordSearch[lineIdx + 1][charIdx + 1] == x_mas[1] &&
						wordSearch[lineIdx + 2][charIdx] == x_mas[0] &&
						wordSearch[lineIdx + 2][charIdx + 2] == x_mas[0]) {
						++resultsTimesXMASAppear;
					}

					//S.M
					//.A.
					//S.M
					if (wordSearch[lineIdx][charIdx] == x_mas[2] &&
						wordSearch[lineIdx][charIdx + 2] == x_mas[0] &&
						wordSearch[lineIdx + 1][charIdx + 1] == x_mas[1] &&
						wordSearch[lineIdx + 2][charIdx] == x_mas[2] &&
						wordSearch[lineIdx + 2][charIdx + 2] == x_mas[0]) {
						++resultsTimesXMASAppear;
					}

					//M.S
					//.A.
					//M.S
					if (wordSearch[lineIdx][charIdx] == x_mas[0] &&
						wordSearch[lineIdx][charIdx + 2] == x_mas[2] &&
						wordSearch[lineIdx + 1][charIdx + 1] == x_mas[1] &&
						wordSearch[lineIdx + 2][charIdx] == x_mas[0] &&
						wordSearch[lineIdx + 2][charIdx + 2] == x_mas[2]) {
						++resultsTimesXMASAppear;
					}

				}

			}

		}


		lineIdx++;
	}

	inputfile.close();

	std::cout << "Results: " << resultsTimesXMASAppear << "\n";

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
