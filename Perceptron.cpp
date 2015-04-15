#include "Perceptron.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// TODO add bias node
Perceptron::Perceptron(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
    : outputLayer(labeled[0].second.size(), Node())
{
    srand(time(NULL));
    
    int inputNum = labeled[0].first.size();

    weights = new double*[inputNum];
    for (int i = 0; i < inputNum; i++) {
        weights[i] = new double[outputLayer.size()];
    }

    for (int i = 0; i < inputNum; i++) {
        for (unsigned int j = 0; j < outputLayer.size(); j++) {
            // NOTE between -0.25 and 0.25
            weights[i][j] = (2*(static_cast<double>(rand()) / RAND_MAX) - 1);
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

        output[i] = outputLayer[i].evaluateNode(weightedInputs);
    }
}

void Perceptron::train(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
{
    for (int i = 0; i < epochs; i++) {
        double totalError = 0;
        for (unsigned int j = 0; j < labeled.size(); j++) {
            std::vector<double> output(labeled[j].second.size(), 0);
            evaluate(labeled[j].first, output);

            double error = 0;
            for (unsigned int k = 0; k < output.size(); k++) {
                error += labeled[j].second[k] / 10 - output[k];
            }
            totalError += fabs(error);

            if (error != 0) {
                double gIn = sigmoidPrime(output);
                for (unsigned int m = 0; m < labeled[j].first.size(); m++) {
                    for (unsigned int n = 0; n < outputLayer.size(); n++) {
                        weights[m][n] += learningRate * error * labeled[j].first[m] * gIn;
                    }
                }
            }
        }
        std::cout << "epoch: " << i << ", error: " << totalError << std::endl;
    }
}

double Perceptron::sigmoidPrime(const std::vector<double>& x) {
    double sum = 0;
    for (unsigned int i = 0; i < x.size(); i++)
        sum += x[i];

    return exp(sum) / pow(exp(sum) + 1, 2);
}
