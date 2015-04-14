#pragma once

#include "Node.h"

#include <vector>
#include <utility>

class Perceptron {
public:
    Perceptron(int epochs, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled);
    void evaluate(const std::vector<double>& input, std::vector<double>& output);

private:
    void train(int epochs, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled);

    std::vector<Node> inputLayer;
    std::vector<Node> outputLayer;
    double** weights;

    static constexpr double learningRate = 0.5;
};
