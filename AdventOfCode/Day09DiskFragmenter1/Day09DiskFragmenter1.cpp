// Day09DiskFragmenter1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct disksegment {
	unsigned long long int id;
	std::vector<unsigned long long int> vLayout;
	int fileSize;
	int freeSpace;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char chInput;
	unsigned long long int filesystemChecksum = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::map<unsigned long long int, disksegment> diskmap;
	

	unsigned long long int segmentIdx = 0;

	while (inputfile.get(chInput)) {

		disksegment ds;
		int fileSize = chInput - '0';
		
		int freeSpace = 0;
		if (inputfile.get(chInput))
			freeSpace = chInput - '0';

		ds.id = segmentIdx;
		ds.vLayout = std::vector<unsigned long long int>(static_cast<size_t>(fileSize), segmentIdx);
		ds.fileSize = fileSize;
		ds.freeSpace = freeSpace;

		diskmap[segmentIdx] = ds;

		segmentIdx++;

	}

	auto findAvailable = diskmap.begin();

	for (auto itReserve = diskmap.rbegin(); itReserve != diskmap.rend(); ++itReserve) {

		auto currentSegment = itReserve;

		const unsigned long long int currentID = currentSegment->first;
		int currentFileSize = currentSegment->second.fileSize;
		std::vector<unsigned long long int> currentVLayout = currentSegment->second.vLayout;

		while (currentFileSize > 0 && findAvailable != diskmap.end() && (itReserve->first > findAvailable->first)) {

			// While filesize is not 0

			findAvailable = std::find_if(diskmap.begin(), diskmap.end(),
				[](const auto& pair) { return pair.second.freeSpace > 0; });

			if (findAvailable != diskmap.end()) {
				int availableFreeSpace = findAvailable->second.freeSpace;

				if (currentFileSize <= availableFreeSpace) {
					findAvailable->second.vLayout.insert(findAvailable->second.vLayout.end(), currentVLayout.end() - 1, currentVLayout.end()); // mod

					findAvailable->second.freeSpace -= 1; // currentFileSize; // mod
					findAvailable->second.fileSize += 1; // currentFileSize; // mod
					currentSegment->second.vLayout.clear();
					currentSegment->second.fileSize -= 1; // = 0; // mod
					currentSegment->second.freeSpace -= 1; // = 0; // mod

					currentFileSize -= 1; // = 0;

				} else if (currentFileSize > availableFreeSpace) {

					findAvailable->second.vLayout.insert(findAvailable->second.vLayout.end(), 1, currentID); // mod
					findAvailable->second.fileSize += 1; // += availableFreeSpace; // mod
					findAvailable->second.freeSpace -= 1; // = 0; // mod

					currentSegment->second.vLayout.erase(currentSegment->second.vLayout.end() - 1); // mod

					currentSegment->second.fileSize -= 1; // -= availableFreeSpace;
					currentSegment->second.freeSpace += 1; // += availableFreeSpace;

					currentFileSize -= 1; // -= availableFreeSpace;
					currentVLayout = currentSegment->second.vLayout;

					findAvailable = std::find_if(std::next(findAvailable), diskmap.end(),
						[](const auto& pair) { return pair.second.freeSpace > 0; });



				}

			}

		}

	}

	auto itResult = diskmap.begin();

	unsigned long long int filesystemIdx = 0;

	while (itResult->second.fileSize > 0) {
		
		for (auto ch : itResult->second.vLayout) {

			filesystemChecksum += (ch * filesystemIdx);

			filesystemIdx++;
		}
		itResult = std::next(itResult);
	}

	inputfile.close();

	std::cout << "Results: " << filesystemChecksum << "\n";

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
