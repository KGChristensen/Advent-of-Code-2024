// Day23LANParty1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adj; // Dynamic adjacency list

public:
    // Add an edge (undirected) - dynamically handles new string-based vertices
    void addEdge(const std::string& u, const std::string& v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Count cycles of length 3 that start and end with the same edge
    int findEdgeBasedTriangleCount() {

        std::set<std::tuple<std::string, std::string, std::string>> uniqueTriangles;

        // Iterate over all edges (u, v)
        for (const auto& [u, neighbors] : adj) {
            for (const std::string& v : neighbors) {
                if (u < v) { // Ensure consistent ordering
                    for (const std::string& w : adj[v]) {
                        if (w > v && adj[w].end() != std::find(adj[w].begin(), adj[w].end(), u)) {
                            // Found a triangle cycle: (u, v, w, u)
                            if (u[0] == 't' || v[0] == 't' || w[0] == 't')
                                uniqueTriangles.insert({ u, v, w });
                        }
                    }
                }
            }
        }

        return uniqueTriangles.size(); // Return the count of valid triangles
    }
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	long results = 0;

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


    int triangleCount = g.findEdgeBasedTriangleCount();
    std::cout << "Total Matching Triangles: " << triangleCount << "\n";


	inputfile.close();

	std::cout << "Results: " << results << "\n";

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
