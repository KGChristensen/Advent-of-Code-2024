// Day16ReindeerMaze2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <chrono>
#include <iostream>
#include <cassert>

#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <set>

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

static int getDistance(const std::pair<int, int>& begin, const std::pair<int, int>& end, const Direction& d)
{
    if (begin == end) { return 0; }
    int diffX = end.first - begin.first;
    int diffY = end.second - begin.second;
    // case go straight
    if ((diffX == 0 && diffY > 0 && d == DOWN) ||
        (diffX == 0 && diffY < 0 && d == UP) ||
        (diffX < 0 && diffY == 0 && d == LEFT) ||
        (diffX > 0 && diffY == 0 && d == RIGHT))
    {
        return (std::abs(diffX) + std::abs(diffY));
    }
    // case at least one turn
    if ((diffY > 0 && diffX != 0 && d == DOWN) ||
        (diffY < 0 && diffX != 0 && d == UP) ||
        (diffX < 0 && diffY != 0 && d == LEFT) ||
        (diffX > 0 && diffY != 0 && d == RIGHT))
    {
        return (std::abs(diffX) + std::abs(diffY) + 1000);
    }
    // case at least two turns
    return (std::abs(diffX) + std::abs(diffY) + 2000);
}

static int getTurnScore(int amount90DegTurns)
{
    if (amount90DegTurns == 2)
    {
        return 2000;
    }
    if (amount90DegTurns == 1 || amount90DegTurns == 3)
    {
        return 1000;
    }
    return 0;
}

static std::pair<int, int> getPosition(const std::vector<std::string>& map, const char& c)
{
    for (size_t y = 0; y < map.size(); y++)
    {
        for (size_t x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == c)
            {
                return std::make_pair(static_cast<int>(x), static_cast<int>(y));
            }
        }
    }
    return std::make_pair(-1, -1);
}

static int path(const std::vector<std::string>& input, const int& bestScore)
{
    int result = 0;

    std::map<Direction, std::pair<int, int>> directions = { { UP, { 0, -1 } },
                                                            { RIGHT, { 1, 0 } },
                                                            { DOWN, { 0, 1 } },
                                                            { LEFT, { -1, 0 } } };
    std::pair<int, int> end = getPosition(input, 'E');
    std::pair<int, int> current = getPosition(input, 'S');
    Direction currentDirection = RIGHT;
    int score = 0;

    std::set<std::tuple<int, Direction, std::vector<std::pair<int, int>>>> nextCoordinates = { { score + getDistance(current, end, currentDirection), currentDirection, { current } } }; // tuple consists of: score + min distance to end, current direction, route
    std::tuple<int, Direction, std::vector<std::pair<int, int>>> currentRoute;

    std::set<std::pair<int, int>> allPositionsOfBestRoutes;
    std::map<std::pair<int, int>, std::pair<int, Direction>> positionWithFastestWayToGetThere;
    positionWithFastestWayToGetThere[current] = std::make_pair(0, currentDirection);

    do
    {
        currentRoute = *nextCoordinates.begin();
        nextCoordinates.erase(nextCoordinates.begin());

        std::vector<std::pair<int, int>> route = std::get<2>(currentRoute);
        current = *route.rbegin();
        currentDirection = std::get<1>(currentRoute);
        score = std::get<0>(currentRoute) - getDistance(current, end, currentDirection);

        for (int direction = 0; direction <= 3; direction++)
        {
            int newDirection = static_cast<int>(currentDirection + direction);
            if (newDirection >= 4) { newDirection -= 4; }
            Direction d = static_cast<Direction>(newDirection);
            std::pair<int, int> next = std::make_pair(current.first + directions[d].first, current.second + directions[d].second);
            if (input[static_cast<size_t>(next.second)][static_cast<size_t>(next.first)] != '#' && std::find(route.begin(), route.end(), next) == route.end())
            {
                int newScore = score;
                newScore += getTurnScore(direction);
                newScore += 1;

                auto newEntry = std::make_tuple(newScore + getDistance(next, end, d), d, route);
                std::get<2>(newEntry).push_back(next);
                if (newScore <= bestScore && (positionWithFastestWayToGetThere.find(next) == positionWithFastestWayToGetThere.end() || newScore <= positionWithFastestWayToGetThere[next].first + getTurnScore(std::abs(d - positionWithFastestWayToGetThere[next].second))))
                {
                    positionWithFastestWayToGetThere[next] = std::make_pair(newScore, d);
                    nextCoordinates.insert(newEntry);
                }
            }
        }

        if (current == end)
        {
            allPositionsOfBestRoutes.insert(std::get<2>(currentRoute).begin(), std::get<2>(currentRoute).end());
        }
    } while (!nextCoordinates.empty());

    result = static_cast<int>(allPositionsOfBestRoutes.size());
    return result;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

    std::string line;

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

    std::vector<std::string> lines;

    while (std::getline(inputfile, line)) {
        
        lines.push_back(line);

    }

    std::cout << "\n" << path(lines, 107468) << "\n";

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
