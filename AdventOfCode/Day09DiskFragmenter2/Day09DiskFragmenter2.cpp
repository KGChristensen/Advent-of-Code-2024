// Day09DiskFragmenter2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	long long int id;
	std::vector<long long int> vLayout;
	int fileSize;
	int freeSpace;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	char chInput;
	long long int filesystemChecksum = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::map<long long int, disksegment> diskmap;


	long long int segmentIdx = 0;

	while (inputfile.get(chInput)) {

		disksegment ds;
		int fileSize = chInput - '0';

		int freeSpace = 0;
		if (inputfile.get(chInput))
			freeSpace = chInput - '0';

		ds.id = segmentIdx;
		ds.fileSize = fileSize;
		ds.freeSpace = freeSpace;
		ds.vLayout = std::vector(static_cast<size_t>(fileSize + freeSpace), LLONG_MIN);

		std::fill(ds.vLayout.begin(), ds.vLayout.begin() + static_cast<long long int>(fileSize), segmentIdx);

		diskmap[segmentIdx] = ds;

		segmentIdx++;

	}

	
	for (auto itReserve = diskmap.rbegin(); itReserve != diskmap.rend(); ++itReserve) {

		auto currentSegment = itReserve;

		const long long int currentID = currentSegment->first;

		auto currentFileSize = std::count(currentSegment->second.vLayout.begin(), currentSegment->second.vLayout.end(), currentID);

		std::vector<long long int> currentVLayout = currentSegment->second.vLayout;

		auto findAvailable = diskmap.begin();

		while (currentFileSize > 0  && findAvailable != diskmap.end() && (itReserve->first > findAvailable->first)) {

			// While filesize is not 0

			findAvailable = std::find_if(diskmap.begin(), diskmap.end(),
				[&currentFileSize, &currentID](const auto& pair) { return ((pair.second.freeSpace >= currentFileSize) && (pair.first < currentID)); });

			if (findAvailable != diskmap.end()) {
				int availableFreeSpace = findAvailable->second.freeSpace;
				int availableFileSize = findAvailable->second.fileSize;

				if (currentFileSize <= availableFreeSpace) {

					std::fill(findAvailable->second.vLayout.begin() + static_cast<long long int>(availableFileSize), findAvailable->second.vLayout.begin() + static_cast<long long int>(availableFileSize) + currentFileSize, currentID);

					findAvailable->second.freeSpace -= currentFileSize;
					findAvailable->second.fileSize += currentFileSize; 

					std::fill(currentSegment->second.vLayout.begin(), currentSegment->second.vLayout.begin() + static_cast<long long int>(currentFileSize), LLONG_MIN);

					currentSegment->second.fileSize -= currentFileSize;
					currentSegment->second.freeSpace += currentFileSize;

					currentFileSize = 0;

				}

			}

		}

	}

	auto itResult = diskmap.begin();

	long long int filesystemIdx = 0;

	while (itResult != diskmap.end()) {

		for (auto ch : itResult->second.vLayout) {

			if (ch != LLONG_MIN)
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
