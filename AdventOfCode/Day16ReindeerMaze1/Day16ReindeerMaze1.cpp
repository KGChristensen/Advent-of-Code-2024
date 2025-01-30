// Day16ReindeerMaze1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <unordered_map>

struct tile {
	char c;
	int x;
	int y;
};

struct Node {
	int x, y;
	float f, g, h;
	int direction; // 0: Up, 1: Right, 2: Down, 3: Left
	int score;
	std::shared_ptr<Node> parent;

	Node(int _x, int _y, float _g, float _h, int _direction, int _score, std::shared_ptr<Node> _parent = nullptr)
		: x(_x), y(_y), f(_g + _h), g(_g), h(_h), direction(_direction), score(_score), parent(_parent) {
	}
};

struct CompareF {
	bool operator()(std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
		return a->f > b->f;
	}
};

struct CompareScore {
	bool operator()(std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
		return a->score > b->score;  // Prioritize nodes with smaller scores
	}
};

static float heuristic(int x1, int y1, int x2, int y2) {
	return static_cast<float>(std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static std::vector<std::shared_ptr<Node>> get_neighbors(std::shared_ptr<Node> node, const std::vector<std::vector<int>>& grid) {
	std::vector<std::shared_ptr<Node>> neighbors;
	const int dx[4] = { 0, 1, 0, -1 };
	const int dy[4] = { 1, 0, -1, 0 };
	int new_direction;

	for (int i = 0; i < 4; ++i) {
		int nx = node->x + dx[i];
		int ny = node->y + dy[i];
		if (nx >= 0 && static_cast<size_t>(nx) < grid.size() && ny >= 0 && static_cast<size_t>(ny) < grid[0].size() && grid[static_cast<size_t>(nx)][static_cast<size_t>(ny)] == 0) {
			int rotation_cost = (node->direction == i) ? 0 : 1000;
			new_direction = i;
			neighbors.push_back(std::make_unique<Node>(nx, ny, 0, 0, new_direction, node->score + 1 + rotation_cost));
		}
	}
	return neighbors;
}

static std::vector<std::shared_ptr<Node>> reconstruct_path(std::shared_ptr<Node> node) {
	std::vector<std::shared_ptr<Node>> path;
	while (node) {
		path.push_back(node);
		node = node->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

static std::vector<std::shared_ptr<Node>> astar(int start_x, int start_y, int goal_x, int goal_y, const std::vector<std::vector<int>>& grid) {
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareScore> open_list;
	std::unordered_map<int, std::shared_ptr<Node>> all_nodes;
	open_list.push(std::make_unique<Node>(start_x, start_y, 0, heuristic(start_x, start_y, goal_x, goal_y), 0, 0));

	while (!open_list.empty()) {
		std::shared_ptr<Node> current = open_list.top();
		open_list.pop();

		if (current->x == goal_x && current->y == goal_y) {
			return reconstruct_path(current);
		}

		for (std::shared_ptr<Node> neighbor : get_neighbors(current, grid)) {
			float g = current->g + 1;
			float h = heuristic(neighbor->x, neighbor->y, goal_x, goal_y);
			if (!all_nodes[static_cast<size_t>(neighbor->x) * grid[0].size() + static_cast<size_t>(neighbor->y)] || g + h < neighbor->f) {
				neighbor->g = g;
				neighbor->h = h;
				neighbor->f = g + h;
				neighbor->parent = current;
				open_list.push(neighbor);
				all_nodes[static_cast<size_t>(neighbor->x) * grid[0].size() + static_cast<size_t>(neighbor->y)] = neighbor;
			}
		}
	}
	return {};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char chTile;

	int x = 0;
	int y = 0;
	int start_x = 0, start_y = 0;
	int goal_x = 4, goal_y = 4;
	size_t rows = 0;
	std::vector<std::vector<tile>> maze;
	std::vector<std::vector<int>> grid;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }
	// Read map
	while (inputfile.get(chTile)) {

		if (maze.empty() || rows > (maze.size() - 1)) {
			maze.push_back(std::vector<tile>());
		}

		if (grid.empty() || rows > (grid.size() - 1)) {
			grid.push_back(std::vector<int>());
		}

		if (chTile == '#') {
			maze[maze.size() - 1].push_back(tile{ chTile, x, y });
			grid[grid.size() - 1].push_back(1);
		}
		else if (chTile == '.') {
			maze[maze.size() - 1].push_back(tile{ chTile, x, y });
			grid[grid.size() - 1].push_back(0);
		}
		else if (chTile == 'S') {
			maze[maze.size() - 1].push_back(tile{ '.', x, y });
			grid[grid.size() - 1].push_back(0);
			start_x = x;
			start_y = y;
		}
		else if (chTile == 'E') {
			maze[maze.size() - 1].push_back(tile{ '.', x, y });
			grid[grid.size() - 1].push_back(0);
			goal_x = x;
			goal_y = y;
		}
		
		x++;

		if (chTile == '\n') {
			grid.push_back(std::vector<int>());
			rows++;
			y++;
			x = 0;
		}
	}

	std::vector<std::shared_ptr<Node>> path = astar(start_x, start_y, goal_x, goal_y, grid);

	std::map<int, int> finalepath;



	//for (auto node : path) {
	//	//std::cout << "(" << node->x << ", " << node->y << ", score" << node->score << ")\n";
	//	
	//	finalepath.emplace(std::make_pair(node->x, node->y));
	//}

	//std::cout << "\n";

	//for (int idyRow = 0; idyRow < static_cast<int>(maze.size()); idyRow++) {
	//	for (int idxCol = 0; idxCol < static_cast<int>(maze[0].size()); idxCol++) {
	//		
	//		auto f = std::find_if(path.begin(), path.end(), [&](const std::shared_ptr<Node>& p) {
	//			return (p->x == idxCol && p->y == idyRow);
	//			});

	//		if (f != path.end()) {
	//			std::cout << 'X';
	//		}
	//		else
	//			std::cout << maze[idyRow][idxCol].c;
	//	}
	//	std::cout << "\n";
	//}

	inputfile.close();

	std::cout << "Results: " << path[path.size()-1]->score << "\n";

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
