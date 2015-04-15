#include "Perceptron.h"
#include "readFile.h"

#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
	if (argc != 6) {
		std::cout << "USAGE dataFile inputType [0 = 32x32 | 1 = 8x8] epoch learningRate outputType[0 = single node | 1 = multiple nodes]" << std::endl;
		return 1;
	}

    // Read in data
	std::vector<std::pair<std::vector<double>, std::vector<double>>> data; 
    bool inputType = static_cast<bool>(atoi(argv[2]));
    if (inputType)
        readData8(argv[1], data);
    else
        readData32(argv[1], data);
    
    bool multipleOutputs = static_cast<bool>(atoi(argv[5]));
    
    // Convert to multi-output format
    if (multipleOutputs) {
        for (unsigned int i = 0; i < data.size(); i++) {
            int recorded = static_cast<int>(data[i].second[0]);
            data[i].second = std::vector<double>(10, 0);
            data[i].second[recorded] = 1;
        }
    }

    // Construct the network
    int epochs = atoi(argv[3]);
    double learningRate = atof(argv[4]);
	Perceptron perceptron(epochs, learningRate, data, multipleOutputs);

    // train it for epochs, reporting % at each epoch
    for (int e = 0; e < epochs; e++) {
        perceptron.train(1, learningRate, data, multipleOutputs);

        // now evaluate current solution
    
        int numCorrect = 0;
        // evaluate the trained network 
        for (unsigned int i = 0; i < data.size(); i++) {
            std::vector<double> output(data[i].second.size(), 0);
            perceptron.evaluate(data[i].first, output);

            // calculate the correct output node
            if (multipleOutputs) {
                double outMax = 0.0;
                int outNode = 0;

                double labeledMax = 0.0;
                int labeledNode = 0;
                for (unsigned int j = 0; j < output.size(); j++) {
                    if (output[j] > outMax) {
                        outMax = output[j];
                        outNode = j;
                    }
                    if (data[i].second[j] > labeledMax) {
                        labeledMax = data[i].second[j];
                        labeledNode = j;
                    }
                }
                if (outNode == labeledNode)
                    numCorrect++;
            }

            else {
                if (floor(10*output[0]) == data[i].second[0])
                    numCorrect++;
            }
        }
        // calculate % correct
        double percentCorrect = static_cast<double>(numCorrect) / data.size();
        std::cout << "Epoch: " << e << std::endl;
        std::cout << "Percent Correct Solutions: " << percentCorrect * 100 << "\%" << std::endl;
    }

	return 0;
}
