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

namespace global
{

    static std::map<char, std::pair<int, int>> numeric_keys = {
        {'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}},
        {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}},
        {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}},
        {'0', {3, 1}}, {'A', {3, 2}}
    };

    static std::map<char, std::pair<int, int>> direction_keys = {
        {'^', {0, 1}}, {'A', {0, 2}},
        {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}}
    };

    static std::map<char, std::pair<int, int>> dd = {
        {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}, {'^', {-1, 0}}
    };
}

static void generate_permutations(const std::string& moves, std::string current, std::set<std::string>& raw_combos, std::vector<bool>& used) {
    if (current.size() == moves.size()) {
        raw_combos.insert(current + "A");
        return;
    }
    for (size_t i = 0; i < moves.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            generate_permutations(moves, current + moves[i], raw_combos, used);
            used[i] = false;
        }
    }
}

static std::vector<std::string> ways(const std::string& code, std::map<char, std::pair<int, int>>& keypad) {
    std::vector<std::vector<std::string>> parts;
    auto cur_loc = keypad['A'];

    for (char c : code) {
        auto next_loc = keypad[c];
        int di = next_loc.first - cur_loc.first;
        int dj = next_loc.second - cur_loc.second;
        std::string moves;

        if (di > 0) moves.append(static_cast<std::string::size_type>(di), 'v');
        else if (di < 0) moves.append(static_cast<std::string::size_type>(-di), '^');
        if (dj > 0) moves.append(static_cast<std::string::size_type>(dj), '>');
        else if (dj < 0) moves.append(static_cast<std::string::size_type>(-dj), '<');

        std::set<std::string> raw_combos;
        std::vector<bool> used(moves.size(), false);
        generate_permutations(moves, "", raw_combos, used);

        std::vector<std::string> combos;
        for (const auto& combo : raw_combos) {
            auto [ci, cj] = cur_loc;
            bool good = true;
            for (size_t i = 0; i < combo.size() - 1; ++i) {
                auto [dy, dx] = global::dd[combo[i]];
                ci += dy;
                cj += dx;
                if (std::find_if(keypad.begin(), keypad.end(), [ci, cj](const auto& kv) {
                    return kv.second == std::make_pair(ci, cj);
                    }) == keypad.end()) {
                    good = false;
                    break;
                }
            }
            if (good) combos.push_back(combo);
        }
        parts.push_back(combos);
        cur_loc = next_loc;
    }

    std::vector<std::string> results = { "" };
    for (const auto& part : parts) {
        std::vector<std::string> new_results;
        for (const auto& prefix : results) {
            for (const auto& suffix : part) {
                new_results.push_back(prefix + suffix);
            }
        }
        results = std::move(new_results);
    }
    return results;
}

static int shortest3(const std::string& code) {
    auto ways1 = ways(code, global::numeric_keys);
    std::vector<std::string> ways2;
    for (const auto& way : ways1) {
        auto new_ways = ways(way, global::direction_keys);
        ways2.insert(ways2.end(), new_ways.begin(), new_ways.end());
    }
    std::vector<std::string> ways3;
    for (const auto& way : ways2) {
        auto new_ways = ways(way, global::direction_keys);
        ways3.insert(ways3.end(), new_ways.begin(), new_ways.end());
    }
    int min_len = INT_MAX;
    for (const auto& w : ways3) {
        min_len = std::min(min_len, static_cast<int>(w.length()));
    }
    return min_len;
}


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    long results = 0;

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

    //auto startPosition = std::make_shared<Node>(3, 2, ' ');


    //std::string sequence;


    while (std::getline(inputfile, line)) {
        
        int value = std::stoi(line.substr(0, line.size() - 1));
        int shortest = shortest3(line);

        results += shortest * value;

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
