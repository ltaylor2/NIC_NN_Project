#pragma once

#include <vector>
#include <utility>

class Perceptron {
public:
    Perceptron(int epochs, double learningRate, std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled, bool multipleOutputs);
    void evaluate(const std::vector<double>& input, std::vector<double>& output);
    void train(int epochs, double learningRate, std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled, bool multipleOutputs);

private:
    double sigmoid(double sum);
    double sigmoidPrime(double sum);
    
    double** weights;
};
