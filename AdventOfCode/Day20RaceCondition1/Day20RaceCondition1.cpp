// Day20RaceCondition1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// 
// big help from: https://www.youtube.com/live/Mu0XXZeCFqw?si=_KfmaRxEgzE7PuBq&t=3256
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
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace {
	static std::vector<std::pair<int, int>> dirs{ std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(0, -1) };
}

static bool inside(size_t row, size_t col, size_t height, size_t width) {
	return 0 <= row && row < height && 0 <= col && col < width;
}

static std::vector<std::vector<int>> bfs(std::pair<int, int> start, std::vector<std::vector<bool>>& racetrack) {
	
	
	//std::vector<std::vector<int>> d(height, std::vector<int>(width, INT_MAX));
	std::vector<std::vector<int>> d;

	for (size_t i = 0; i < racetrack.size(); i++) {
		std::vector<int> temp;
		for (size_t j = 0; j < racetrack[0].size(); j++) {
			temp.push_back(INT_MAX);
		}
		d.push_back(temp);
	}

	

	d[static_cast<size_t>(start.first)][static_cast<size_t>(start.second)] = 0;
	std::vector<std::pair<int, int>> queue;
	queue.push_back(start);
	for (size_t idq = 0; idq < queue.size(); idq++) {
		size_t r = static_cast<size_t>(queue[idq].first);
		size_t c = static_cast<size_t>(queue[idq].second);
		if (racetrack[r][c] == true) {
			continue;
		}
		for (std::pair<int, int> dir : dirs) {
			size_t r2 = r + static_cast<size_t>(dir.first);
			size_t c2 = c + static_cast<size_t>(dir.second);
			if (inside(r2, c2, racetrack.size(), racetrack[0].size()) && d[r2][c2] == INT_MAX) {
				d[r2][c2] = d[r][c] + 1;
				queue.emplace_back(r2, c2);
			}
		}
	}
	return d;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char chTile;

	int x = 0;
	int y = 0;
	int resultCheatsWithLeastXPicoseconds = 0;
	const int picoSeconds = 100;
	int start_x = 0, start_y = 0;
	int end_x = 4, end_y = 4;
	size_t rows = 0;
	std::vector<std::vector<bool>> racetrack;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }
	// Read map
	while (inputfile.get(chTile)) {

		if (racetrack.empty() || rows > (racetrack.size() - 1)) {
			racetrack.push_back(std::vector<bool>());
		}

		if (chTile == '#') {
			racetrack[racetrack.size() - 1].push_back(true);
		}

		else if (chTile == '.') {
			racetrack[racetrack.size() - 1].push_back(false);
		}

		else if (chTile == 'S') {
			racetrack[racetrack.size() - 1].push_back(false);
			start_x = x;
			start_y = y;
		}
		else if (chTile == 'E') {
			racetrack[racetrack.size() - 1].push_back(false);
			end_x = x;
			end_y = y;
		}

		x++;

		if (chTile == '\n') {
			racetrack.push_back(std::vector<bool>());
			rows++;
			y++;
			x = 0;
		}

	}

	std::pair<int, int> startPosition{ start_y, start_x };
	std::pair<int, int> endPosition{ end_y, end_x };

	std::vector<std::vector<int>> forwardPath = bfs(startPosition,racetrack);
	std::vector<std::vector<int>> backwardPath = bfs(endPosition, racetrack);
	int normal = forwardPath[static_cast<size_t>(endPosition.first)][static_cast<size_t>(endPosition.second)];

	for (size_t idyHeight = 0; idyHeight < racetrack.size(); idyHeight++) {
		for (size_t idxWidth = 0; idxWidth < racetrack[0].size(); idxWidth++) {
			if (racetrack[idyHeight][idxWidth] == true) {
				for (std::pair<int, int> dir : dirs) {
					size_t idyHeight2 = idyHeight + static_cast<size_t>(dir.first);
					size_t idxWidth2 = idxWidth + static_cast<size_t>(dir.second);
					if (inside(idyHeight2, idxWidth2, racetrack.size(), racetrack[0].size()) && racetrack[idyHeight2][idxWidth2] != true) {
						int here = forwardPath[idyHeight][idxWidth] + backwardPath[idyHeight2][idxWidth2] + 1;
						//std::cout << "Here: " << here << " Normal: " << normal << "\n";
						if (here <= (normal - picoSeconds)) {
							resultCheatsWithLeastXPicoseconds++;
						}
					}
				}
			}
		}
	}

	inputfile.close();


	std::cout << "Cheats with at least " << picoSeconds << " picoseconds " << resultCheatsWithLeastXPicoseconds << "\n";

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
