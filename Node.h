#pragma once

#include <vector>

class Node {
public:
	Node();
	
	double evaluateNode(const std::vector<double> &input);
	double evaluateNode(double input);

	double getOutput() const { return output; }

private:
	// TODO static?
	double sigmoidActivation(double x);

	double output;
};
