// Day06GuardGallivant1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <vector>
#include <algorithm>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::string> map;
	long resultDistinctPositionsVisited = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	size_t startRow = 0;
	size_t startCol = 0;
	size_t lineIdx = 0;
	// 0 = up, 1 = left, 2 = down, 3 = right
	int direction = 0;

	while (std::getline(inputfile, line)) {

		map.push_back(line);
		auto pos = line.find('^');
		if (pos != std::string::npos) {
			startRow = lineIdx;
			startCol = pos;
		}

		lineIdx++;
	}

	size_t width = map[0].length() - 1ULL;
	size_t height = lineIdx - 1ULL;

	while (startRow >= 0 && startRow <= height && startCol >= 0 && startCol <= width) {

		switch (direction) {
			//up
			case 0: {

				// is at the edge
				if (startRow <= 0) {
					map[startRow][startCol] = 'X';
					startRow--;
					break;
				}

				// can't move
				if (map[startRow - 1][startCol] == '#') {
					map[startRow][startCol] = 'X';
					direction = 3; //right
					break;
				}

				// move in direction
				map[startRow][startCol] = 'X';
				startRow--;

				break;
			}
			//left
			case 1: {

				// is at the edge
				if (startCol <= 0) {
					map[startRow][startCol] = 'X';
					startCol--;
					break;
				}

				// can't move
				if (map[startRow][startCol - 1] == '#') {
					map[startRow][startCol] = 'X';
					direction = 0; //down

					break;
				}

				// move in direction
				map[startRow][startCol] = 'X';
				startCol--;

				break;
			}
			//down
			case 2: {

				// is at the edge
				if (startRow >= height) {
					map[startRow][startCol] = 'X';
					startRow++;
					break;
				}

				// can't move
				if (map[startRow + 1][startCol] == '#') {
					map[startRow][startCol] = 'X';
					direction = 1; //left

					break;
				}

				// move in direction
				map[startRow][startCol] = 'X';
				startRow++;

				break;
			}
			//right
			case 3: {

				// is at the edge
				if (startCol >= width) {
					map[startRow][startCol] = 'X';
					startCol++;
					break;
				}

				// can't move
				if (map[startRow][startCol + 1] == '#') {
					map[startRow][startCol] = 'X';
					direction = 2; //down

					break;
				}

				// move in direction
				map[startRow][startCol] = 'X';
				startCol++;

				break;
			}
			default: {
				break;
			}
		}
	}

	for (auto s : map) {
		resultDistinctPositionsVisited += std::count(s.begin(), s.end(), 'X');
	}

	inputfile.close();

	std::cout << "Results: " << resultDistinctPositionsVisited << "\n";

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
