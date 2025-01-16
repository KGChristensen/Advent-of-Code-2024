// Day14RestroomRedoubt1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct position {
	int px;
	int py;
};

struct velocity {
	int vx;
	int vy;
};

struct robot {
	position pos;
	velocity vel;
};

struct cmp
{
	bool operator() (position a, position b) const
	{
		return std::make_pair(a.px, a.py) > std::make_pair(b.px, b.py);
	}
};
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	const int wide = 101;
	const int tall = 103;
	std::vector<robot> robots;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		int px, py, vx, vy;

		sscanf_s(line.c_str(), "p=%u,%u v=%u,%u\n", &px, &py, &vx, &vy);

		robots.push_back({ {px,py},{vx,vy} });

	}

	const int seconds = 100;

	for (size_t idxSecond = 0; idxSecond < seconds; idxSecond++) {

		for (size_t robotIdx = 0; robotIdx < robots.size(); robotIdx++)
		{

			const int newPosX = robots[robotIdx].pos.px + robots[robotIdx].vel.vx;

			robots[robotIdx].pos.px = newPosX < 0 ? (wide + newPosX) : newPosX >= wide ? newPosX - wide : newPosX;

			const int newPosY = robots[robotIdx].pos.py + robots[robotIdx].vel.vy;

			robots[robotIdx].pos.py = newPosY < 0 ? (tall + newPosY) : newPosY >= tall ? newPosY - tall : newPosY;
		}

	}

	const int halfWide = (wide - 1) / 2;
	const int halfTall = (tall - 1) / 2;

	auto robotAmount1 = std::count_if(robots.begin(), robots.end(), [](const robot& r) {
		return (r.pos.px < halfWide && r.pos.py < halfTall);
		});

	auto robotAmount2 = std::count_if(robots.begin(), robots.end(), [](const robot& r) {
		return (r.pos.px > halfWide && r.pos.py < halfTall);
		});

	auto robotAmount3 = std::count_if(robots.begin(), robots.end(), [](const robot& r) {
		return (r.pos.px < halfWide && r.pos.py > halfTall);
		});

	auto robotAmount4 = std::count_if(robots.begin(), robots.end(), [](const robot& r) {
		return (r.pos.px > halfWide && r.pos.py > halfTall);
		});

	inputfile.close();

	std::cout << "Results: " << (robotAmount1 * robotAmount2 * robotAmount3 * robotAmount4) << "\n";

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
