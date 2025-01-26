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

struct Tile {
    int x;
    int y;
    char t;

    bool operator<(const Tile& rhs) const {
        return rhs.x < this->x || (rhs.x == this->x && rhs.y < this->y);
    }
};

struct dir {
    int dx;
    int dy;
};

static dir directions[] = {
    {-1, 0}, // Up
    {0, 1}, // Right
    {1, 0}, // Down
    {0, -1} // Left

};

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    char chTile;
    long sumOfAllBoxesGPSCoordinates = 0;
    std::vector<Tile> warehouse;
    std::queue<char> moves;
    std::map<int, std::vector<int>> wallsX, wallsY;

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) {
        std::cerr << "Cannot open file!\n";
        return 0;
    }

    int x = 0, y = 0, startX = 0, startY = 0, width = 0, height = 0;

    while (inputfile.get(chTile)) {
        if (chTile == '\n') {
            y++;
            x = 0;
            continue;
        }

        switch (chTile) {
        case '@':
            startX = x;
            startY = y;
            break;
        case '#':
        case 'O':
            width = x;
            height = y;
            warehouse.emplace_back(Tile{ x, y, chTile });
            if (chTile == '#') {
                wallsX[y].push_back(x);
                wallsY[x].push_back(y);
            }
            break;
        case '<':
        case '^':
        case 'v':
        case '>':
            moves.emplace(chTile);
            break;
        }
        x++;
    }

    auto findNearestWallX = [&wallsX](int y, int startX, bool left) {
        auto& walls = wallsX[y];
        if (left) {
            auto it = std::lower_bound(walls.rbegin(), walls.rend(), startX, std::greater<int>());
            return (it == walls.rend()) ? -1 : *it;
        }
        else {
            auto it = std::lower_bound(walls.begin(), walls.end(), startX);
            return (it == walls.end()) ? -1 : *it;
        }
        };

    auto findNearestWallY = [&wallsY](int x, int startY, bool up) {
        auto& walls = wallsY[x];
        if (up) {
            auto it = std::lower_bound(walls.rbegin(), walls.rend(), startY, std::greater<int>());
            return (it == walls.rend()) ? -1 : *it;
        }
        else {
            auto it = std::lower_bound(walls.begin(), walls.end(), startY);
            return (it == walls.end()) ? -1 : *it;
        }
        };

    while (!moves.empty()) {
        char move = moves.front();
        std::stack<int> boxes;

        if (move == '<') {
            int nearestWallX = findNearestWallX(startY, startX, true);
            if (nearestWallX == -1) nearestWallX = 0;
            int distanceFromX = std::abs(startX - nearestWallX);

            for (int idx = startX - 1; idx > (startX - distanceFromX); --idx) {
                auto isBox = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const Tile& f) {
                    return (f.x == idx && f.y == startY && f.t == 'O');
                    });

                if (isBox != warehouse.rend()) {
                    boxes.emplace(idx);
                }
                else {
                    break;
                }
            }

            startX = std::max((nearestWallX + 1 + static_cast<int>(boxes.size())), startX - 1);

            int counter = 1;
            while (!boxes.empty()) {
                auto idx = boxes.top();

                auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == idx && f.y == startY && f.t == 'O');
                    });

                theBox->x = std::max(theBox->x - 1, nearestWallX + counter);

                boxes.pop();
                counter++;
            }
        }
        else if (move == '^') {
            int nearestWallY = findNearestWallY(startX, startY, true);
            if (nearestWallY == -1) nearestWallY = 0;
            int distanceFromY = std::abs(startY - nearestWallY);

            for (int idy = startY - 1; idy > (startY - distanceFromY); --idy) {
                auto isBox = std::find_if(warehouse.rbegin(), warehouse.rend(), [&](const Tile& f) {
                    return (f.x == startX && f.y == idy && f.t == 'O');
                    });

                if (isBox != warehouse.rend()) {
                    boxes.emplace(idy);
                }
                else {
                    break;
                }
            }

            startY = std::max((nearestWallY + 1 + static_cast<int>(boxes.size())), startY - 1);

            int counter = 1;
            while (!boxes.empty()) {
                auto idy = boxes.top();

                auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == startX && f.y == idy && f.t == 'O');
                    });

                theBox->y = std::max(theBox->y - 1, nearestWallY + counter);

                boxes.pop();
                counter++;
            }
        }
        else if (move == '>') {
            int nearestWallX = findNearestWallX(startY, startX, false);
            if (nearestWallX == -1) nearestWallX = warehouse.size();
            int distanceFromX = std::abs(startX - nearestWallX);

            for (int idx = startX + 1; idx < (startX + distanceFromX); ++idx) {
                auto isBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == idx && f.y == startY && f.t == 'O');
                    });

                if (isBox != warehouse.end()) {
                    boxes.emplace(idx);
                }
                else {
                    break;
                }
            }

            startX = std::min((nearestWallX - 1 - static_cast<int>(boxes.size())), startX + 1);

            int counter = 1;
            while (!boxes.empty()) {
                auto idx = boxes.top();

                auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == idx && f.y == startY && f.t == 'O');
                    });

                theBox->x = std::min(theBox->x + 1, nearestWallX - counter);

                boxes.pop();
                counter++;
            }
        }
        else if (move == 'v') {
            int nearestWallY = findNearestWallY(startX, startY, false);
            if (nearestWallY == -1) nearestWallY = warehouse.size();
            int distanceFromY = std::abs(startY - nearestWallY);

            for (int idy = startY + 1; idy < (startY + distanceFromY); ++idy) {
                auto isBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == startX && f.y == idy && f.t == 'O');
                    });

                if (isBox != warehouse.end()) {
                    boxes.emplace(idy);
                }
                else {
                    break;
                }
            }

            startY = std::min((nearestWallY - 1 - static_cast<int>(boxes.size())), startY + 1);

            int counter = 1;
            while (!boxes.empty()) {
                auto idy = boxes.top();

                auto theBox = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& f) {
                    return (f.x == startX && f.y == idy && f.t == 'O');
                    });

                theBox->y = std::min(theBox->y + 1, nearestWallY - counter);

                boxes.pop();
                counter++;
            }
        }
        moves.pop();
    }

    for (int idxY = 0; idxY <= height; idxY++) {
        for (int idxX = 0; idxX <= width; idxX++) {

            auto foundTile = std::find_if(warehouse.begin(), warehouse.end(), [&](const Tile& t) {
                return (t.x == idxX && t.y == idxY);
                });



            if (foundTile != warehouse.end()) {
                //std::cout << foundTile->t;

                if (foundTile->t == 'O')
                    sumOfAllBoxesGPSCoordinates += (100 * foundTile->y) + foundTile->x;

            }
            //else {
            //	if (startX == idxX && startY == idxY) {
            //		std::cout << "@";
            //	}
            //	else {
            //		std::cout << ".";
            //	}
            //}

        }
        //std::cout << "\n";

    }

    inputfile.close();

    std::cout << "Sum of all boxes' GPS coordinates: " << sumOfAllBoxesGPSCoordinates << "\n";

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
