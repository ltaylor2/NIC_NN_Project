#include "Node.h"

#include <math.h>

// Node constructor
Node::Node()
	:output(0);
{}

double Node::evaluateNode(std::vector<double> &input) {

	double inputSum = 0.0;
	//sum all the inputs
	for (int i = 0; i < input.size(); i++) {
		inputSum += input[i];
	}

	// activate the node with the sigmoid function
	output  = sigmoidEvaluation(inputSum);
	return output;
}

double Node::evaluateNode(double input) {
	// activate the node with the sigmoid function
	output = sigmoidEvaluation(input);
	return output;
}

double Node::sigmoidEvaluation(double inputSum) {
	return 1/(1+ exp(-input));
}

