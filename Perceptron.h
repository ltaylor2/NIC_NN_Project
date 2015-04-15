#pragma once

#include "Node.h"

#include <vector>
#include <utility>

class Perceptron {
public:
    Perceptron(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled);
    void evaluate(const std::vector<double>& input, std::vector<double>& output);

private:
    void train(int epochs, double learningRate, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled);
    double sigmoidPrime(const std::vector<double>& x);
    
    // TODO not necessary
    std::vector<Node> outputLayer;
    double** weights;
};
