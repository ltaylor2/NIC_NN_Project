#include "Perceptron.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Perceptron::Perceptron(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
    : outputLayer(labeled[0].second.size(), Node())
{
    srand(time(NULL));
    
    int inputNum = labeled[0].first.size();

    weights = new double*[inputNum];
    for (int i = 0; i < inputNum; i++) {
        weights[i] = new double[outputLayer.size()];
    }

    std::cout << "inputNum: " << inputNum << std::endl;

    for (int i = 0; i < inputNum; i++) {
        for (unsigned int j = 0; j < outputLayer.size(); j++) {
            weights[i][j] = 2*(static_cast<double>(rand()) / RAND_MAX) - 1;
            std::cout << weights[i][j] << std::endl;
        }
    }

    train(epochs, learningRate, labeled);

}

// NOTE assumes output is correct size
void Perceptron::evaluate(const std::vector<double>& input, std::vector<double>& output)
{
    for (unsigned int i = 0; i < outputLayer.size(); i++) {
        std::vector<double> weightedInputs(input.size(), 0);

        for (unsigned int j = 0; j < input.size(); j++) {
            weightedInputs[j] = weights[j][i]*input[j];
        }

        //output[i] = outputLayer[i].evaluateNode(weightedInputs);
        output[i] = floor(10 * outputLayer[i].evaluateNode(weightedInputs));
    }
}

void Perceptron::train(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
{
        std::cout << learningRate << std::endl;

    for (int i = 0; i < epochs; i++) {
        std::cout << "epoch, " << i << std::endl;
        double totalError = 0;
        for (unsigned int j = 0; j < labeled.size(); j++) {
            std::vector<double> output(labeled[j].second.size(), 0);
            evaluate(labeled[j].first, output);

            double error = 0;
            for (unsigned int k = 0; k < output.size(); k++) {
                error += labeled[j].second[k] - output[k];
            }
            totalError += error;

            if (error != 0) {
                for (unsigned int m = 0; m < labeled[j].first.size(); m++) {
                    for (unsigned int n = 0; n < outputLayer.size(); n++) {
                        weights[m][n] += learningRate * error * sigmoidPrime(labeled[j].first[m]);
                    }
                }
            }
        }
        std::cout << totalError << std::endl;
    }
    // for (unsigned int m = 0; m < labeled[0].first.size(); m++) {
    //     for (unsigned int n = 0; n < outputLayer.size(); n++) {
    //         std::cout << weights[m][n] << std::endl;
    //     }
    // }
}

double Perceptron::sigmoidPrime(double x) {
    return exp(x) / pow(exp(x) + 1, 2);
}
