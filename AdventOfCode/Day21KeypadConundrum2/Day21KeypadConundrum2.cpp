// Day21KeypadConundrum2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif
// 
// Thanks to https ://www.youtube.com/watch?v=q5I6ZvJmHEo&ab_channel=WilliamY.Feng
//

#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <tuple>
#include <fstream>

//#define long long long long


static int getInt(char c) {
	if (isdigit(c)) return c - '0';
	if (c == 'A') return 10;
	//assert(false);
	return -1;
}
/*
static char getChar(long long value) {
	if (0 <= value && value < 10) {
		return '0' + value;
	}
	if (value == 10) {
		return 'A';
	}
	return false;
}*/
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, HIT = 4;
const size_t numRobots = 25; // number of robots using keypads
const char MOVEMENT = '$';
const char ERROR = '@';


namespace global {
	static std::pair<int, int> dirs[4] = { std::make_pair(-1,0), std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(0,1) };
	static long long dp[numRobots + 2][11][11];
}


static char makeMove(size_t mv, size_t& x, std::vector<std::vector<int>> pad) {
	//assert(0 <= mv && mv < 4);
	size_t H = pad.size();
	size_t W = pad[0].size();
	for (size_t r = 0; r < H; r++) {
		for (size_t c = 0; c < W; c++) {
			if (pad[r][c] == static_cast<int>(x)) {
				r += static_cast<size_t>(global::dirs[mv].first);
				c += static_cast<size_t>(global::dirs[mv].second);
				if (0 <= static_cast<int>(r) && r < H && 0 <= static_cast<int>(c) && c < W && pad[r][c] != -1) {
					x = static_cast<size_t>(pad[r][c]);
					return MOVEMENT;
				}
				else {
					return ERROR;
				}
			}
		}
	}
	return ERROR;
	//assert(false);
}



static void preprocess(std::vector<std::vector<int>>& numpad, std::vector<std::vector<int>>& keypad) {
	for (size_t id = 1; id <= numRobots + 1; id++) {
		const size_t X = (id == numRobots + 1 ? 11 : 5);
		for (size_t from = 0; from < X; from++) {
			std::vector<std::vector<long long>> small(5, std::vector<long long>(11, LLONG_MAX));
			small[HIT][from] = 0;
			std::set<std::pair<long long, std::pair<size_t, size_t>>> pq;
			pq.insert({ 0LL, {HIT,from} });

			auto consider = [&](size_t prv, size_t me, long long maybe) {
				if (maybe < small[prv][me]) {
					pq.erase({ small[prv][me], {prv,me} });
					small[prv][me] = maybe;
					pq.insert({ maybe, {prv,me} });
				}
				};

			while (!pq.empty()) {
				long long my_dist = pq.begin()->first;
				size_t prv = pq.begin()->second.first;
				size_t me = pq.begin()->second.second;
				pq.erase(pq.begin());
				for (size_t prv2 = 0; prv2 < 5; prv2++) {
					long long maybe = my_dist + global::dp[id - 1][prv][prv2];
					consider(prv2, me, maybe);
				}
				if (prv != HIT) {
					if (MOVEMENT == makeMove(prv, me, (id == numRobots + 1 ? numpad : keypad))) {
						consider(prv, me, my_dist + 1);
					}
				}
			}
			for (size_t to = 0; to < (id == numRobots + 1 ? 11 : 5); to++) {
				global::dp[id][from][to] = small[HIT][to];
			}
		}
	}
}

static long long solve(std::string s) {
	char prv = 'A';
	long long total = 0;
	for (char c : s) {
		total += global::dp[numRobots + 1][getInt(prv)][getInt(c)] + 1;
		prv = c;
	}
	return total;
}


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto start = std::chrono::high_resolution_clock::now();

    std::string code;
    long long results = 0;

	std::vector<std::vector<int>> numpad = {
		{7,8,9},
		{4,5,6},
		{1,2,3},
		{-1,0,10} // 10=A
	};

	std::vector<std::vector<int>> keypad = {
		{-1, UP, HIT},
		{LEFT, DOWN, RIGHT}
	};

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

    //auto startPosition = std::make_shared<Node>(3, 2, ' ');


    //std::string sequence;
	preprocess(numpad, keypad);

    while (std::getline(inputfile, code)) {

		long long x = solve(code);
		std::cout << x << "\n";
		code.pop_back();
		results += x * std::stoi(code);



    }

    inputfile.close();

    std::cout << "Sum of the complexities of the five codes: " << results << "\n";

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

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
