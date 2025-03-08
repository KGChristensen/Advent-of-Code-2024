// Day24CrossedWires1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct gateWireConnection
{
	std::string wireLeft;
	std::string gate;
	std::string wireRight;
	std::string output;
};

static int wireValue(const int& wireLeft, const std::string& gate, const int& wireRight) {
	if (gate == "AND") {
		return wireLeft & wireRight;
	}
	else if (gate == "OR") {
		return wireLeft | wireRight;
	}
	else if (gate == "XOR") {
		return wireLeft ^ wireRight;
	}
	else {
		return 0;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::string binaryNumber;
	long long results = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::map<std::string, int> wires;
	std::vector<std::pair<gateWireConnection, bool>> gateWireConnections;

	while (std::getline(inputfile, line)) {

		size_t colon = line.find(':');
		if (colon != std::string::npos) {
			wires[line.substr(0, colon)] = std::stoi(line.substr(colon+1));
		}
		else if (line.size() > 1) {
			//std::cout << line << "\n";
			//std::string connection;
			std::stringstream connections(line);

			std::string wireLeft;
			std::getline(connections, wireLeft, ' ');
			std::string gate;
			std::getline(connections, gate, ' ');
			std::string wireRight;
			std::getline(connections, wireRight, ' ');
			std::string output;
			std::getline(connections, output, ' ');	// Skipped
			std::getline(connections, output, ' ');

			gateWireConnections.push_back({ { wireLeft, gate, wireRight, output }, false });

		}

	}

	int gateWireConnectionSize = static_cast<int>(gateWireConnections.size());

	while (gateWireConnectionSize > std::count_if(gateWireConnections.begin(), gateWireConnections.end(), [](const std::pair<gateWireConnection, bool>& connection) {return connection.second == true; })) {

		for (auto& connection : gateWireConnections) {

			if (wires.contains(connection.first.wireLeft) == true && wires.contains(connection.first.wireRight) == true) {
				wires[connection.first.output] = wireValue(wires[connection.first.wireLeft], connection.first.gate, wires[connection.first.wireRight]);
				connection.second = true;
			}
		}
	}

	inputfile.close();

	auto cmp = [](const std::pair<std::string, int>& wire) {return wire.first[0] == 'z'; };

	auto it = std::find_if(wires.begin(), wires.end(), cmp);
	int count = 0;
	while (it != wires.end()) {
		//std::cout << it->first << " " << it->second << " - " << (it->second*(std::pow(2.0,count))) << "\n";
		binaryNumber += std::to_string(it->second);
		results += static_cast<long long>(it->second * (std::pow(2.0, count)));
		it = std::find_if(std::next(it), wires.end(), cmp);
		count++;
	}

	std::cout << "Binary: " << binaryNumber << "\n";
	std::cout << "Decimal: " << results << "\n";

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
