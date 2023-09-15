#pragma once
#include "Network.h"
#include "Node.h"
#include <vector>

class Layer
{
public:
	Layer(int size, int rank);

private:
	std::vector<Node*> nodes;
	int size;
	int rank;
};

