#pragma once
#include "Network.h"
#include "Node.h"
#include <vector>

class Layer
{
public:
	Layer(int size, int rank, int next_layer_size, bool is_first_layer);
	int getSize();
	int getRank();
	std::vector<Node*> getNodes();

private:
	std::vector<Node*> nodes;
	int size;
	int rank;
};

