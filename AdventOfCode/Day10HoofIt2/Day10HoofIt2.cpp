// Day10HoofIt2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

namespace global {
	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };
	const int N = 41; // Set this to the actual number of rows in the new map
	const int M = 41; // Set this to the actual number of columns in the new map
}

struct Position {
	int x, y, height;
};

static int bfs(const std::vector<std::vector<int>>& map, int startX, int startY) {
	std::queue<Position> q;
	std::vector<std::vector<bool>> visited(global::N, std::vector<bool>(global::M, false));
	q.push({ startX, startY, map[startX][startY] });
	visited[startX][startY] = true;

	int score = 0;

	while (!q.empty()) {
		Position pos = q.front();
		q.pop();

		if (pos.height == 9) {
			score++;
			continue;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = pos.x + global::dx[i];
			int ny = pos.y + global::dy[i];

			if (nx >= 0 && nx < global::N && ny >= 0 && ny < global::N && !visited[nx][ny] && map[nx][ny] == pos.height + 1) {
				q.push({ nx, ny, map[nx][ny] });
				visited[nx][ny] = true;
			}
		}
	}

	return score;
}

static void dfs(const std::vector<std::vector<int>>& map, std::vector<std::vector<bool>>& visited, int x, int y, int& score) {
	if (map[x][y] == 9) {
		score++;
		return;
	}

	visited[x][y] = true;

	for (int i = 0; i < 4; ++i) {
		int nx = x + global::dx[i];
		int ny = y + global::dy[i];

		if (nx >= 0 && nx < global::N && ny >= 0 && ny < global::M && !visited[nx][ny] && map[nx][ny] == map[x][y] + 1) {
			dfs(map, visited, nx, ny, score);
		}
	}

	visited[x][y] = false;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char height;

	std::vector<std::vector<int>> topographicMap;
	long sumScoresOfAllTrailheads = 0;
	std::vector<std::vector<bool>> visited(global::N, std::vector<bool>(global::N, false));
	//int width = 0;
	//int height = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	topographicMap.push_back(std::vector<int>());

	while (inputfile.get(height)) {

		if (height != '\n') {
			topographicMap[topographicMap.size() - 1].push_back(height - '0');
		}
		else {
			topographicMap.push_back(std::vector<int>());
		}
	}

	for (int x = 0; x < global::N; ++x) {
		for (int y = 0; y < global::M; ++y) {
			if (topographicMap[x][y] == 0) {
				int score = 0;
				dfs(topographicMap, visited, x, y, score);
				sumScoresOfAllTrailheads += score;
			}
		}
	}



	std::cout << "Sum of the scores of all trailheads: " << sumScoresOfAllTrailheads << "\n";

	inputfile.close();

	//std::cout << "Results: " << results << "\n";

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
