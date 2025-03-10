// Day24CrossedWires2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Big thanks to https://www.youtube.com/watch?v=A5AJb_34RXc&ab_channel=RobHabraken// 
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

struct Wire {
	std::string name;
	explicit Wire(const std::string& n) : name(n) {}
};

struct Gate {
	Wire* input1;
	Wire* input2;
	Wire* output;
	std::string op;
	Gate(Wire* in1, Wire* in2, Wire* out, const std::string& operation)
		: input1(in1), input2(in2), output(out), op(operation) {
	}
};

static void addWire(const std::string& wireName, std::map<std::string, Wire*>& wires) {
	if (wires.find(wireName) == wires.end()) {
		wires[wireName] = new Wire(wireName);
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::string binaryNumber;
	std::map<std::string, Wire*> wires;
	std::vector<Gate> gateWireConnections;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }


	while (std::getline(inputfile, line)) {

		if (line.find("->") != std::string::npos) {
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

			addWire(wireLeft, wires);
			addWire(wireRight, wires);
			addWire(output, wires);
			gateWireConnections.emplace_back(wires[wireLeft], wires[wireRight], wires[output], gate);

		}

	}

    std::vector<Gate*> suspiciousGates;
    std::vector<Wire*> outputWires;
    for (const auto& pair : wires) {
        if (pair.first[0] == 'z') {
            outputWires.push_back(pair.second);
        }
    }

    for (auto& gate : gateWireConnections) {
        if ((gate.input1->name[0] == 'x' || gate.input2->name[0] == 'x') &&
            (gate.input1->name[0] == 'y' || gate.input2->name[0] == 'y') &&
            (gate.input1->name.find("00") == std::string::npos && gate.input2->name.find("00") == std::string::npos)) {
            for (auto& secondGate : gateWireConnections) {
                if (gate.output == secondGate.input1 || gate.output == secondGate.input2) {
                    if ((gate.op == "AND" && secondGate.op == "AND") ||
                        (gate.op == "XOR" && secondGate.op == "OR")) {
                        suspiciousGates.push_back(&gate);
                    }
                }
            }
        }

        if (gate.input1->name[0] != 'x' && gate.input2->name[0] != 'x' &&
            gate.input1->name[0] != 'y' && gate.input2->name[0] != 'y' &&
            gate.output->name[0] != 'z' && gate.op == "XOR") {
            suspiciousGates.push_back(&gate);
        }

        if (std::find(outputWires.begin(), outputWires.end(), gate.output) != outputWires.end() &&
            gate.output->name != "z" + std::to_string(outputWires.size() - 1) &&
            gate.op != "XOR") {
            suspiciousGates.push_back(&gate);
        }
    }

    std::vector<std::string> results;
    for (const auto& sGate : suspiciousGates) {
        results.push_back(sGate->output->name);
    }
    std::sort(results.begin(), results.end());

    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << results[i] << (i == results.size() - 1 ? "" : ",");
    }
    std::cout << std::endl;

    for (auto& pair : wires) {
        delete pair.second;
    }

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
