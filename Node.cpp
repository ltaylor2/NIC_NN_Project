#include "Node.h"

#include <cmath>

// Node constructor
Node::Node()
	: output(0)
{}

double Node::evaluateNode(const std::vector<double> &input) {

	double inputSum = 0.0;
	//sum all the inputs
	for (unsigned int i = 0; i < input.size(); i++) {
		inputSum += input[i];
	}

	// activate the node with the sigmoid function
	output  = sigmoidActivation(inputSum);
	return output;
}

// TODO make vector and call overloaded evaluateNode
double Node::evaluateNode(double input) {
	// activate the node with the sigmoid function
	output = sigmoidActivation(input);
	return output;
}

// TODO static?
double Node::sigmoidActivation(double x) {
	return 1/(1+ exp(-x+0.5));
}
