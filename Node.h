#pragma once
#include <vector>

class Node
{
public:
	Node(int connections);

private:
	int connections;
	double bias;
	std::vector<double> weights;
};

