// Day15WarehouseWoes1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <stack>
#include <set>
#include <vector>
#include <algorithm>

struct tile {
	int x;
	int y;
	char t;

	bool operator<(const tile& rhs) const {
		return rhs.x < this->x || (rhs.x == this->x && rhs.y < this->y);
	}
};



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char chTile;
	long sumOfAllBoxesGPSCoordinates = 0;
	std::vector<tile> warehouse;
	std::queue<char> moves;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	int x = 0;
	int y = 0;
	int startX = 0;
	int startY = 0;
	int width = 0;  // X >>>>>
	int height = 0; // Y vvvvv

	while (inputfile.get(chTile)) {

		if (chTile == '\n') {
			y++;
			x = 0;
			continue;
		}
		else if (chTile == '@') {
			startX = x;
			startY = y;
		}
		else if (chTile == '#' || chTile == 'O') {
			width = x;
			height = y;
			warehouse.emplace_back(tile{ x,y,chTile });
		}
		else if (chTile == '<' || chTile == '^' || chTile == 'v' || chTile == '>') {
			moves.emplace(chTile);
		}


		x++;

		//std::cout << tile << "\n";
	}



	for (int idxY = 0; idxY <= height; idxY++) {
		for (int idxX = 0; idxX <= width; idxX++) {

			auto foundTile = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& t) {
				return (t.x == idxX && t.y == idxY);
				});

			if (foundTile != warehouse.end()) {
				std::cout << foundTile->t;
			}
			else {
				if (startX == idxX && startY == idxY) {
					std::cout << "@";
				}
				else {
					std::cout << ".";
				}
			}

		}
		std::cout << "\n";

	}




	while (!moves.empty()) {
		char move = moves.front();

		//std::cout << "Move: " << move << "\n";
		
		if (move == '<') {

			auto nearestWall = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const tile& f) {
				return (f.x < startX && f.y == startY && f.t == '#');
				});

			int distanceFromX = std::abs(startX - nearestWall->x);

			std::stack<int> boxes;

			for (int idx = startX - 1; idx > (startX - distanceFromX); --idx) {
				auto isBox = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const tile& f) {
					return (f.x == idx && f.y == startY && f.t == 'O');
					});

				if (isBox != warehouse.rend())
				{
					boxes.emplace(idx);
				}
				else {
					idx = 0;
				}

			}

			startX = std::max((nearestWall->x + 1 + static_cast<int>(boxes.size())), startX - 1);

			int counter = 1;

			while (!boxes.empty()) {
				auto idx = boxes.top();

				auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == idx && f.y == startY && f.t == 'O');
					});

				theBox->x = std::max(theBox->x - 1, nearestWall->x + counter);

				boxes.pop();
				counter++;
			}

		} 
		else if (move == '^') {

			auto nearestWall = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const tile& f) {
				return (f.x == startX && f.y < startY && f.t == '#');
				});

			int distanceFromY = std::abs(startY - nearestWall->y);

			std::stack<int> boxes;

			for (int idy = startY - 1; idy > (startY - distanceFromY); --idy) {
				auto isBox = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const tile& f) {
					return (f.x == startX && f.y == idy && f.t == 'O');
					});

				if (isBox != warehouse.rend())
				{
					boxes.emplace(idy);
				}
				else {
					idy = 0;
				}

			}

			startY = std::max((nearestWall->y + 1 + static_cast<int>(boxes.size())), startY - 1);


			int counter = 1;

			while (!boxes.empty()) {
				auto idy = boxes.top();

				auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == startX && f.y == idy && f.t == 'O');
					});

				theBox->y = std::max(theBox->y - 1, nearestWall->y + counter);

				boxes.pop();
				counter++;
			}

		}
		else if (move == '>') {

			auto nearestWall = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
				return (f.x > startX && f.y == startY && f.t == '#');
				});

			int distanceFromX = std::abs(startX - nearestWall->x);

			std::stack<int> boxes;

			for (int idx = startX + 1; idx < (startX + distanceFromX); ++idx) {
				auto isBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == idx && f.y == startY && f.t == 'O');
					});

				if (isBox != warehouse.end())
				{
					boxes.emplace(idx);
				}
				else {
					idx = nearestWall->x;
				}

			}

			startX = std::min((nearestWall->x - 1 - static_cast<int>(boxes.size())), startX + 1);

			int counter = 1;

			while (!boxes.empty()) {
				auto idx = boxes.top();

				auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == idx && f.y == startY && f.t == 'O');
					});

				theBox->x = std::min(theBox->x + 1, nearestWall->x - counter);
				
				boxes.pop();
				counter++;
			}

			

			

		}
		else if (move == 'v') {

			auto nearestWall = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
				return (f.x == startX && f.y > startY && f.t == '#');
				});

			int distanceFromY = std::abs(startY - nearestWall->y);

			std::stack<int> boxes;

			for (int idy = startY + 1; idy < (startY + distanceFromY); ++idy) {
				auto isBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == startX && f.y == idy && f.t == 'O');
					});

				if (isBox != warehouse.end())
				{
					boxes.emplace(idy);
				}
				else {
					idy = nearestWall->y;
				}

			}

			startY = std::min((nearestWall->y - 1 - static_cast<int>(boxes.size())), startY + 1);
			

			int counter = 1;



			while (!boxes.empty()) {
				auto idy = boxes.top();

				auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& f) {
					return (f.x == startX && f.y == idy && f.t == 'O');
					});

				theBox->y = std::min(theBox->y + 1, nearestWall->y - counter);
				//startY = nearestWall->y - counter - 1;
				boxes.pop();
				counter++;

			}

		}

		//for (int idxY = 0; idxY <= height; idxY++) {
		//	for (int idxX = 0; idxX <= width; idxX++) {

		//		auto foundTile = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& t) {
		//			return (t.x == idxX && t.y == idxY);
		//			});



		//		if (foundTile != warehouse.end()) {
		//			std::cout << foundTile->t;

		//		}
		//		else {
		//			if (startX == idxX && startY == idxY) {
		//				std::cout << "@";
		//			}
		//			else {
		//				std::cout << ".";
		//			}
		//		}

		//	}
		//	std::cout << "\n";

		//}

		moves.pop();
	}

	for (int idxY = 0; idxY <= height; idxY++) {
		for (int idxX = 0; idxX <= width; idxX++) {

			auto foundTile = std::find_if(warehouse.begin(), warehouse.end(), [&](const tile& t) {
				return (t.x == idxX && t.y == idxY);
				});



			if (foundTile != warehouse.end()) {
				std::cout << foundTile->t;

				if (foundTile->t == 'O')
					sumOfAllBoxesGPSCoordinates += (100 * foundTile->y) + foundTile->x;

			}
			else {
				if (startX == idxX && startY == idxY) {
					std::cout << "@";
				}
				else {
					std::cout << ".";
				}
			}

		}
		std::cout << "\n";

	}

	inputfile.close();

	std::cout << "Sum of all boxes' GPS coordinates: " << sumOfAllBoxesGPSCoordinates << "\n";

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
