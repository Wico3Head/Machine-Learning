#pragma once
#include "Node.h"
#include <vector>

class Layer
{
public:
	Layer(int size, int rank);
	int getSize();
	int getRank();
	std::vector<Node*> getNodes();

private:
	std::vector<Node*> nodes;
	int size;
	int rank;
};

