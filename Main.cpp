#include "Node.h"
#include "Perceptron.h"
#include "readFile.h"

#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "USAGE dataFile epoch learningRate" << std::endl;
		return 1;
	}

	std::vector<std::pair<std::vector<double>, std::vector<double>>> data; 
    readData32(argv[1], data);

	Perceptron perceptron(atoi(argv[2]), atof(argv[3]), data);
    for (unsigned int i = 0; i < data.size(); i++) {
        std::vector<double> output(data[i].second.size(), 0);
        perceptron.evaluate(data[i].first, output);

        for (unsigned int j = 0; j < output.size(); j++) {
            std::cout << data[i].second[j] << ", " << output[j] << std::endl;
        }
    }

	return 0;
}
