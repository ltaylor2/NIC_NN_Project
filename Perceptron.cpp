#include "Perceptron.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Perceptron::Perceptron(int epochs, double learningRate, std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled, bool multipleOutputs)
{
    // Seed random number generator
    srand(time(NULL));
    
    // Add bias node
    for (unsigned int i = 0; i < labeled.size(); i++) {
        labeled[i].first.push_back(1.0);
    }
    
    std::cout << "Biased" << std::endl;

    int inputSize = labeled[0].first.size();
    int outputSize = 10;

    // Create weight matrix
    weights = new double*[inputSize];
    for (int i = 0; i < inputSize; i++) {
        weights[i] = new double[outputSize];
    }

    std::cout << "Weights" << std::endl;

    // Initialize weights randomly between interval
    for (int i = 0; i < inputSize; i++) {
        for (int j = 0; j < outputSize; j++) {
            // NOTE between -0.25 and 0.25
            weights[i][j] = (2*(static_cast<double>(rand()) / RAND_MAX) - 1) / 8;
        }
    }

    std::cout << "Weights initialized" << std::endl;

    std::cout << "Perceptron Constructed";
    if (multipleOutputs) 
        std::cout << " with 10 output nodes." << std::endl;
    else
        std::cout << " with 1 output node." << std::endl;

    // Train network
    train(epochs, learningRate, labeled, multipleOutputs);
}

// NOTE assumes output is correct size
void Perceptron::evaluate(const std::vector<double>& input, std::vector<double>& output)
{
    for (unsigned int i = 0; i < output.size(); i++) {
        double sum = 0;
        for (unsigned int j = 0; j < input.size(); j++) {
            sum += weights[j][i]*input[j];
        }

        output[i] = sigmoid(sum);
    }
}

void Perceptron::train(int epochs, double learningRate, std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled, bool multipleOutputs)
{
    for (int i = 0; i < epochs; i++) {
        double totalError = 0;
        for (unsigned int j = 0; j < labeled.size(); j++) {
            const std::vector<double>& exampleInput = labeled[j].first;
            const std::vector<double>& exampleOutput = labeled[j].second;
            std::vector<double> computedOutput(exampleOutput.size(), 0);
            
            evaluate(exampleInput, computedOutput);

            for (unsigned int k = 0; k < computedOutput.size(); k++) {
                double error;
                if (multipleOutputs) {
                    error = exampleOutput[k] - computedOutput[k];
                }
                else {
                    error = exampleOutput[k] / 10 - computedOutput[k];
                }
                double sum = computedOutput[k];
                
                totalError += fabs(error);
                
                if (error != 0) {
                    double gIn = sigmoidPrime(sum);
                    for (unsigned int m = 0; m < exampleInput.size(); m++) {
                        weights[m][k] += learningRate * error * exampleInput[m] * gIn;
                    }
                }
            }
        }
        std::cout << "epoch: " << i << ", error: " << totalError << std::endl;
    }
}

double Perceptron::sigmoid(double sum) {
    return 1/(1+ exp(-sum+0.5));
}

double Perceptron::sigmoidPrime(double sum) {
    return exp(sum) / pow(exp(sum) + 1, 2);
}
