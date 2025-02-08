// Day18RAMRun2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <cmath>
#include <unordered_map>
#include <algorithm>


struct Node {
	int x, y;
	double f, g, h;
	std::shared_ptr<Node> parent;

	Node(int _x, int _y, double _g, double _h, std::shared_ptr<Node> _parent = nullptr)
		: x(_x), y(_y), f(_g + _h), g(_g), h(_h), parent(_parent) {
	}

	bool operator<(const Node& other) const {
		return f > other.f;
	}
};

static double heuristic(int x1, int y1, int x2, int y2) {
	return std::abs(x2 - x1) + std::abs(y2 - y1); // Manhattan distance
}

static std::vector<std::pair<int, int>> get_neighbors(int x, int y) {
	return { {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1} };
}

static bool is_valid(int x, int y, const std::vector<std::vector<bool>>& grid) {
	return x >= 0 && x < static_cast<int>(grid.size()) && y >= 0 && y < static_cast<int>(grid[0].size()) && grid[static_cast<size_t>(x)][static_cast<size_t>(y)] == false;
}

static std::vector<std::pair<int, int>> reconstruct_path(std::shared_ptr<Node> node) {
	std::vector<std::pair<int, int>> path;
	while (node) {
		path.push_back(std::make_pair(node->x, node->y));
		node = node->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

static std::vector<std::pair<int, int>> a_star(const std::vector<std::vector<bool>>& grid, std::pair<int, int> start, std::pair<int, int> goal) {
	std::priority_queue<Node> open_list;
	std::unordered_map<int, std::unordered_map<int, bool>> closed_list;
	open_list.emplace(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));

	while (!open_list.empty()) {
		Node current = open_list.top();
		open_list.pop();

		if (current.x == goal.first && current.y == goal.second) {
			return reconstruct_path(std::make_shared<Node>(current));
		}

		closed_list[current.x][current.y] = true;

		for (const auto& neighbor : get_neighbors(current.x, current.y)) {
			int nx = neighbor.first, ny = neighbor.second;
			if (is_valid(nx, ny, grid) && !closed_list[nx][ny]) {
				double tentative_g = current.g + 1; // move cost is 1 for each step
				double h = heuristic(nx, ny, goal.first, goal.second);
				open_list.emplace(nx, ny, tentative_g, h, std::make_shared<Node>(current));
			}
		}
	}

	return {};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	size_t width = 70;
	size_t height = 70;

	std::vector<std::vector<bool>> memorySpace;

	for (size_t idh = 0; idh <= height; idh++) {
		memorySpace.push_back(std::vector<bool>());
		for (size_t idw = 0; idw <= width; idw++) {
			memorySpace[memorySpace.size() - 1].push_back(false);
		}
	}


	std::pair<int, int> startPosition = std::make_pair(0, 0);
	std::pair<int, int> exitPosition = std::make_pair(static_cast<int>(width), static_cast<int>(height));

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	int px;
	int py;
	bool pathPossible = true;

	while (std::getline(inputfile, line) && pathPossible) {

		sscanf_s(line.c_str(), "%i,%i\n", &px, &py);

		memorySpace[static_cast<size_t>(px)][static_cast<size_t>(py)] = true;
		std::vector<std::pair<int, int>> path = a_star(memorySpace, startPosition, exitPosition);
		
		if (path.empty()) {
			pathPossible = !path.empty();
			std::cout << "Result: " << px << "," << py << "\n";
		}

	}

	inputfile.close();

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
