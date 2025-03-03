// Day23LANParty2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <unordered_set>

class Graph {
private:
    std::unordered_map<std::string, std::set<std::string>> adj; // Adjacency list

public:
    void addEdge(const std::string& u, const std::string& v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    // Bron-Kerbosch Algorithm to find maximal cliques
    void bronKerbosch(std::set<std::string> R, std::set<std::string> P, std::set<std::string> X, std::set<std::string>& largestClique) {
        if (P.empty() && X.empty()) { // Found a maximal clique
            if (R.size() > largestClique.size()) {
                largestClique = R;
            }
            return;
        }

        std::set<std::string> P_copy = P;
        for (const std::string& v : P_copy) {
            std::set<std::string> newR = R, newP, newX;

            newR.insert(v);

            for (const std::string& neighbor : adj[v]) {
                if (P.find(neighbor) != P.end()) newP.insert(neighbor);
                if (X.find(neighbor) != X.end()) newX.insert(neighbor);
            }

            bronKerbosch(newR, newP, newX, largestClique);

            P.erase(v);
            X.insert(v);
        }
    }

    // Find the largest clique in the graph and return just the nodes (single elements)
    std::set<std::string> findLargestCliqueNodes() {
        std::set<std::string> largestClique, P, X;

        for (const auto& [node, _] : adj) {
            P.insert(node);
        }

        bronKerbosch({}, P, X, largestClique);

        return largestClique; // Return the largest clique as a set of single elements
    }
};

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    std::string password = "";

    std::ifstream inputfile("input.txt");

    if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

    Graph g;

    while (std::getline(inputfile, line)) {

        size_t dashPos = line.find('-'); // Find the separator
        if (dashPos != std::string::npos) {
            std::string comp1 = line.substr(0, dashPos);
            std::string comp2 = line.substr(dashPos + 1);
            g.addEdge(comp1, comp2);
        }
    }


    // Get the largest clique as interconnected nodes (single elements)
    std::set<std::string> largestCliqueNodes = g.findLargestCliqueNodes();

    // Output result
    for (const auto& node : largestCliqueNodes) {
		if (password.length() > 0) password += ",";
        password += node;
    }

    inputfile.close();

    std::cout << "Password: " << password << "\n";

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
