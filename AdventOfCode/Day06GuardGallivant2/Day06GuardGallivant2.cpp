// Day06GuardGallivant2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct dir{
	int dx;
	int dy;
};

static dir directions[] = {
	{-1, 0}, // Up
	{0, 1}, // Right
	{1, 0}, // Down
	{0, -1} // Left

};

static bool detectInfiniteLoop(std::vector<std::string>& map, size_t startX, size_t startY, size_t startDirection) {
	
	const size_t cols = map[0].length();
	const size_t rows = map.size();

	size_t x = startX;
	size_t y = startY;
	
	// 0 = up, 1 = right, 2 = down, 3 = left
	size_t direction = startDirection;
	//std::set<std::string> visited;
	std::vector<bool> vis(cols * rows * 4);

	while (true) {

		//const std::string state = std::format("{0},{1},{2}", x, y,direction);

		const int hash = (x * cols + y) * 4 + direction;

		//if (visited.contains(state))
		if (vis[hash])
			return true;

		//visited.insert(state);
		vis[hash] = true;


		const size_t nextX = x + directions[direction].dx;
		const size_t nextY = y + directions[direction].dy;

		if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols) {
			return false;
		}

		if (map[nextX][nextY] == '#') {
			// Change directions
			direction = (direction + 1) % 4;
		}
		else {
			// Move forward
			x = nextX;
			y = nextY;
		}

	}

	return true;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::string> map;
	long resultDistinctPositionsVisited = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	size_t startX = 0;
	size_t startY = 0;
	size_t lineIdx = 0;
	// 0 = up, 1 = right, 2 = down, 3 = left
	size_t startDirection = 0;
	std::set<std::string> visited;

	while (std::getline(inputfile, line)) {

		map.push_back(line);
		auto pos = line.find('^');
		if (pos != std::string::npos) {
			startX = lineIdx;
			startY = pos;
		}

		lineIdx++;
	}

	//size_t cols = map[0].length();
	size_t rows = lineIdx;

	for (size_t iIdx = 0; iIdx < rows; iIdx++) {
		for (size_t jIdx = 0; jIdx < rows; jIdx++) {
		

			// Ccells that are free
			if (map[iIdx][jIdx] == '.') {
				
				// Temporarily add an obstacle
				map[iIdx][jIdx] = '#';

				// Check if adding this obstacle causes an infinite loop
				if (detectInfiniteLoop(map, startX, startY, startDirection)) {
					resultDistinctPositionsVisited++;
				}

				// Remove the obstacle
				map[iIdx][jIdx] = '.';

			}

			

		}
	}

	/*
	while (true) {

		visited.insert(std::format("{0},{1}",x,y));

		const size_t nextX = x + directions[direction].dx;
		const size_t nextY = y + directions[direction].dy;

		if (nextX<0 || nextX >= rows || nextY < 0 || nextY >= cols) {
			break;
		}

		if (map[nextX][nextY] == '#') {
			// Change directions
			direction = (direction + 1) % 4;
		}
		else {
			// Move forward
			x = nextX;
			y = nextY;
		}

	}
	*/
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
