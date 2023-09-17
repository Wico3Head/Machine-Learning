#pragma once
#include <vector>

class Node
{
public:
	Node();
	void setWeights(std::vector<double> weights);
	void alterWeights(std::vector<double> alterations);
	std::vector<double> getWeights();
	void setBias(double bias);
	void alterBias(double alteration);
	double getBias();

private:
	double bias;
	std::vector<double> weights;
};

