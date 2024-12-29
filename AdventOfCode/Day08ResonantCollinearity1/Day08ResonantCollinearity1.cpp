// Day08ResonantCollinearity1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct point {
	int x; // cols >>>
	int y; // rows vvv
};

struct cmp
{
	bool operator() (point a, point b) const
	{
		return std::make_pair(a.x, a.y) < std::make_pair(b.x, b.y);
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char ch;
	long results = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::map<point, char, cmp> map;
	std::map<point, char, cmp> mapAntiNodes;

	int cols = 0; // x >>>
	int rows = 0; // y vvv

	size_t width = 0;	// >>>, cols, x
	size_t height = 0;	// vvv, rows, y

	while (inputfile.get(ch)) {
		
		if (ch != '\n' && ch != '.') {
			point p = { cols, rows };
			map[p] = ch;
		}

		//std::cout << ch << "";
		cols++;
		if (ch == '\n') {
			rows++;
			width = cols - 1;
			cols = 0;
		} 

		
		height = rows + 1;
	}

	for (auto mappoint : map) {

		//std::cout << "Value: " << mappoint.second << " (x:" << mappoint.first.x << "," << mappoint.first.y << ")\n";

		char ch = mappoint.second;
		point p = mappoint.first;
		int x = p.x;
		int y = p.y;

		
		if (ch != '#') {

			auto itFindCh = std::find_if(map.begin(), map.end(),
				[&ch,x,y](const auto& pair) { return ((pair.second == ch) && (pair.first.x != x) && (pair.first.y != y)); });

			while (itFindCh != map.end()) {

				int foundX = itFindCh->first.x;
				int foundY = itFindCh->first.y;


				int diffX = foundX - x;
				int diffY = foundY - y;

				//std::cout << "new x: " << (foundX - x) << ", new y: " << (foundY - y) << "\n";
					
				int newX = (diffX) > 0 ? x - diffX : x + std::abs(diffX);
				int newY = (diffY) > 0 ? y - diffY : y + std::abs(diffY);


				if (mapAntiNodes.find({newX, newY}) == mapAntiNodes.end() && (newX >= 0 && newX < width) && (newY >= 0 && newY < height))
					mapAntiNodes[{newX, newY}] = '#';

				itFindCh = std::find_if(std::next(itFindCh), map.end(),
					[&ch, x, y](const auto& pair) { return ((pair.second == ch) && (pair.first.x != x) && (pair.first.y != y)); });

			}
		}

	}

	std::cout << "Width: " << width << ", height: " << height << "\n";

	for (int ih = 0; ih < height; ih++) {
		for (int iw = 0; iw < width; iw++) {

			auto it = map.find({ iw,ih });
			auto itAntiNodes = mapAntiNodes.find({ iw,ih });
			if (it != map.end())
				std::cout << it->second;
			else if (itAntiNodes != mapAntiNodes.end())
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << "\n";
	}

	// Get last key (11,11)
	//point p = { .x = width-1, .y = height-1 };
	//point p = { .x = 9, .y = 9 };
	//auto it = map.find({9,9});
	//auto it = map.find({9,9});
	//std::cout << "p(11,11): " << it->second << "\n";

	// Set last key at (11,11)
	//it->second = 'C';

	// Get all A's
	//char chA = 'A';
	//auto itA = std::find_if(map.begin(), map.end(),
	//	[&chA](const auto& pair) { return pair.second == chA; });

	//while (itA != map.end()) {

	//	std::cout << "A: (" << itA->first.x << "," << itA->first.y << ")\n";

	//	itA = std::find_if(std::next(itA), map.end(),
	//		[&chA](const auto& pair) { return pair.second == chA; });
	//}

	inputfile.close();




	std::cout << "Results: " << mapAntiNodes.size() << "\n";

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
