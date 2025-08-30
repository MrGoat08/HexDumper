#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "No arguments passed..." << std::endl;
		std::cin.get();
		return 1;
	}

	const char* fileName = argv[1];
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Cannot open the .exe file..." << std::endl;
		std::cin.get();
		return 1;
	}

	file.seekg(0, std::ios::end);
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::cout << "File size: " << fileSize << std::endl;

	char* buffer = new char[fileSize];
	std::streamsize lastBlockStartIndex = 0;

	file.read(buffer, fileSize);

	for (std::streamsize i = 0; i < fileSize; ++i) {
		char currentByte = static_cast<unsigned char>(buffer[i]);
		printf("%02X ", currentByte);

		if ((i + 1) % 16 == 0) {
			std::cout << "         ";
			for (size_t currentCharIndex = lastBlockStartIndex; currentCharIndex < i; currentCharIndex++) {
				char currentChar = static_cast<unsigned char>(buffer[currentCharIndex]);

				if (currentChar >= 32 && currentChar <= 127) {
					std::cout << currentChar;
				}
				else {
					std::cout << ".";
				}
			}
			std::cout << std::endl;
			lastBlockStartIndex = i;
		};
	}

	delete buffer;
	return 0;
}
