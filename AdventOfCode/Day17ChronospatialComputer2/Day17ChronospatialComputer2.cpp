// Day17ChronospatialComputer2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Inspiration: https://www.youtube.com/watch?v=y-UPxMAh2N8&t=2158s

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
#include <functional>
#include <type_traits>

class Computer {
public:

	void loadProgram(const long long instruction) noexcept { program.emplace_back(instruction); }
	void run() noexcept;
	void display() noexcept;

private:
	long long output;

	std::vector<long long> program;

	long long duplicateProgram(std::vector<long long> target, long long ans) noexcept;

};

void Computer::run() noexcept {
	output = duplicateProgram(program, 0);
};

void Computer::display() noexcept {
	std::cout << "" << output << "\n";
}

long long Computer::duplicateProgram(std::vector<long long> target, long long value) noexcept
{
	if (target.empty()) return value;

	for (long long t = 0; t < 8; ++t) {
		long long a = (value << 3) | t;
		long long b = 0;
		long long c = 0;
		long long tmpOutput = -1;

		auto combo = [&](long long operand) -> long long {
			if (operand >= 0 && operand <= 3) return operand;
			if (operand == 4) return a;
			if (operand == 5) return b;
			if (operand == 6) return c;
			throw std::runtime_error("Unrecognized combo operand");
			};

		for (size_t pointer = 0; pointer < program.size() - 2; pointer += 2) {
			long long ins = program[pointer];
			long long operand = program[pointer + 1];

			if (ins == 1) {
				b = b ^ operand;
			}
			else if (ins == 2) {
				b = combo(operand) % 8;
			}
			else if (ins == 4) {
				b = b ^ c;
			}
			else if (ins == 5) {
				tmpOutput = combo(operand) % 8;
			}
			else if (ins == 6) {
				b = a >> combo(operand);
			}
			else if (ins == 7) {
				c = a >> combo(operand);
			}
			if (tmpOutput != -1 && tmpOutput == target.back()) {
				long long sub = duplicateProgram(std::vector<long long>(target.begin(), target.end() - 1), a);
				if (sub == -1) continue;
				return sub;
			}
		}
	}
	return -1;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	//long results = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::unique_ptr<Computer> ThreeBitComputer = std::make_unique<Computer>();

	char program[255];

	while (std::getline(inputfile, line)) {

		if (line[0] == 'P') {
			sscanf_s(line.c_str(), "Program: %s\n", &program, rsize_t{ 255 });
			std::stringstream instructions(program);
			std::string instruction;
			while (std::getline(instructions, instruction, ',')) {
				ThreeBitComputer->loadProgram(std::stoll(instruction));
			}
		}

	}

	ThreeBitComputer->run();

	ThreeBitComputer->display();

	inputfile.close();

	//std::cout << "Results: " << results << "\n";

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

