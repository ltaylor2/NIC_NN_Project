#pragma once

#include <vector>

class Node {
	
public:
	Node();
	
	double evaluateNode(std::vector<double> &input);
	double evaluateNode(double input);

	double getOutput() { return output; }

private:
	double sigmoidActivation(double inputSum);
	double output;
};