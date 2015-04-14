#pragma once

#include <vector>

class Node {
public:
	Node();
	
	double evaluateNode(const std::vector<double> &input);
	double evaluateNode(double input);

	double getOutput() const { return output; }

private:
	double sigmoidActivation(double x);

	double output;
};
