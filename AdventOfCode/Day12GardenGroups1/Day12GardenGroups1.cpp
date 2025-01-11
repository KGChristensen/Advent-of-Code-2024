// Day12GardenGroups1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void dfs(const std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited, size_t height, size_t width, int x, int y, int& area, int& perimeter) {
	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };

	area++;

	visited[x][y] = true;

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= static_cast<int>(height) || ny < 0 || ny >= static_cast<int>(width) || map[nx][ny] != map[x][y]) {
			perimeter++;
		}

		if (nx >= 0 && nx < static_cast<int>(height) && ny >= 0 && ny < static_cast<int>(width) && !visited[nx][ny] && map[nx][ny] == map[x][y]) {
			dfs(map, visited, height, width, nx, ny, area, perimeter);
		}

	}

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char plant;
	long totalPriceOfFencing = 0;
	std::vector<std::vector<char>> gardenPlots;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }
	
	gardenPlots.push_back(std::vector<char>());

	while (inputfile.get(plant)) {
		if (plant != '\n') {
			gardenPlots[gardenPlots.size() - 1].push_back(plant);
		}
		else {
			gardenPlots.push_back(std::vector<char>());
		}
	}

	inputfile.close();

	size_t height = gardenPlots.size();
	size_t width = gardenPlots[0].size();

	std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

	for (size_t x = 0; x < height; ++x) {
		for (size_t y = 0; y < width; ++y) {
			if (visited[x][y] == false) {
				int area = 0;
				int perimeter = 0;
				dfs(gardenPlots, visited, height, width, x, y, area, perimeter);
				//std::cout << "Plant: " << gardenPlots[x][y] << ", area: " << area << ", perimeter: " << perimeter << "\n";
				totalPriceOfFencing += (area * perimeter);

			}
		}
	}

	std::cout << "Results: " << totalPriceOfFencing << "\n";

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
