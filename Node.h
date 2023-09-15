#pragma once
#include <vector>

class Node
{
public:
	Node(int connections, bool is_first_layer);
	void setWeights(std::vector<double> weights);
	std::vector<double> getWeights();
	void setBias(double bias);
	double getBias();

private:
	int connections;
	double bias;
	bool first_layer;
	std::vector<double> weights;
};

