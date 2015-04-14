#include "Node.h"
#include "Perceptron.h"
#include "readFile.h"

#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "USAGE dataFile epoch" << std::endl;
		return 1;
	}

	std::vector<std::pair<std::vector<double>, std::vector<double>>>* data = readData32(argv[1]);
	Perceptron perceptron(atoi(argv[2]), *data);
	return 0;
}