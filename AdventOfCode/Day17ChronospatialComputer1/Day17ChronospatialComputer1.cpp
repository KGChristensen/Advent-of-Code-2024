// Day17ChronospatialComputer1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <functional>
#include <type_traits>

class Computer {
public:
	// opcode 0
	void Adv(long long const operand) noexcept;
	// opcode 1
	void Bxl(long long const operand) noexcept;
	// opcode 2
	void Bst(long long const operand) noexcept;
	// opcode 3
	void Jnz(long long const operand) noexcept;
	// opcode 4
	void Bxc(long long const operand) noexcept;
	// opcode 5
	void Out(long long const operand) noexcept;
	// opcode 6
	void Bdv(long long const operand) noexcept;
	// opcode 7
	void Cdv(long long const operand) noexcept;

	void loadRegister(const char registerNo, const long long registerVal) noexcept { registers[registerNo] = registerVal; }
	void loadProgram(const long long instruction) noexcept { program.emplace_back(instruction); }
	void run() noexcept;
	void display() noexcept;

private:
	bool halt = true;
	std::map<char, long long> registers = { {'A',0}, {'B',0}, {'C',0} };
	size_t instructionPointer = 0;
	std::vector<long long> output;

	std::vector<long long> program;

	template <typename T> T GetComboOperand(T t);

};

template<typename T>
T Computer::GetComboOperand(T t)
{

	T tmp = static_cast<T>(t);

	if (t == 4) {
		tmp = static_cast<T>(registers['A']);
	}
	else if (t == 5){
		tmp = static_cast<T>(registers['B']);
	}
	else if (t == 6){
		tmp = static_cast<T>(registers['C']);
	}
	return tmp;
}

void Computer::Adv(long long const operand) noexcept{

	double registerA = static_cast<double>(registers['A']);
	
	double registerB = GetComboOperand<double>(static_cast<double>(operand));

	double division = registerA / std::pow(2.0, registerB);

	registers['A'] = static_cast<long long>(std::trunc(division));
}

void Computer::Bxl(long long const operand) noexcept {

	long long registerB = static_cast<long long>(registers['B']);
	long long secondHandside = GetComboOperand<long long>(operand);

	registers['B'] = static_cast<long long>(registerB ^ secondHandside);
}

void Computer::Bst(long long const operand) noexcept {

	long long secondHandside = GetComboOperand<long long>(operand);

	registers['B'] = static_cast<long long>(secondHandside % 8);
}

void Computer::Jnz(long long const operand) noexcept {

	long long registerA = registers['A'];

	if (registerA != 0) {
		instructionPointer = static_cast<size_t>(operand);
	}

}

void Computer::Bxc(long long const operand) noexcept {

	long long registerB = static_cast<long long>(registers['B']);
	long long registerC = static_cast<long long>(registers['C']);

	registers['B'] = static_cast<long long>(registerB ^ registerC);
}

void Computer::Out(long long const operand) noexcept {

	long long secondHandside = GetComboOperand<long long>(operand);

	output.push_back(static_cast<long long>(secondHandside % 8));
}

void Computer::Bdv(long long const operand) noexcept {

	double registerA = static_cast<double>(registers['A']);
	double registerB = GetComboOperand<double>(static_cast<double>(operand));

	double division = registerA / std::pow(2.0, registerB);

	registers['B'] = static_cast<long long>(std::trunc(division));
}

void Computer::Cdv(long long const operand) noexcept {

	double registerA = static_cast<double>(registers['A']);
	double registerB = GetComboOperand<double>(static_cast<double>(operand));

	double division = registerA / std::pow(2.0, registerB);

	registers['C'] = static_cast<long long>(std::trunc(division));
}

void Computer::run() noexcept {

	halt = false;

	while ((instructionPointer < program.size()) && !halt) {

		long long opcode = program[instructionPointer++];

		long long operand = 0;

		if (opcode != 3LL) {
			if (instructionPointer > program.size() - 1) {
				halt = true;
				std::cout << "Computer halted!\n";

				for (auto iter = output.begin(); iter != output.end(); iter++) {
					if (iter != output.begin()) std::cout << ",";
					std::cout << *iter;
				}

				std::cout << "\n";

			}
			else {
				operand = program[instructionPointer++];
			}
		}


		switch (opcode) {
			case 0:
				Adv(operand);
				break;
			case 1:
				Bxl(operand);
				break;
			case 2:
				Bst(operand);
				break;
			case 3:
				Jnz(operand);
				break;
			case 4:
				Bxc(operand);
				break;
			case 5:
				Out(operand);
				break;
			case 6:
				Bdv(operand);
				break;
			case 7:
				Cdv(operand);
				break;
			default:
				break;
		}

	}
};

void Computer::display() noexcept {
	for (auto regstr : registers) {
		std::cout << "Register " << regstr.first << ": " << regstr.second << "\n";
	}
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

	char registerNo;
	int registerVal;
	char program[255];

	while (std::getline(inputfile, line)) {
		
		if (line[0] == 'R') {
			sscanf_s(line.c_str(), "Register %c: %i\n", &registerNo, rsize_t{ 1 }, &registerVal);
			ThreeBitComputer->loadRegister(registerNo, static_cast<long long>(registerVal));
		}
		else if (line[0] == 'P') {
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


