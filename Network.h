#pragma once
#include "Layer.h"
#include "Node.h"
#include <vector>

class Network
{
public:
	Network(std::vector<int> structure);

private:
	std::vector<int> structure;
	std::vector<Layer*> layers;
};

