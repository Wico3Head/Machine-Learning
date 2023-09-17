#pragma once
#include "Layer.h"
#include "Node.h"
#include <vector>

class Network
{
public:
	Network(std::vector<int> structure);
	std::vector<double> activate(std::vector<double> inputs);
	void learn(std::vector<std::vector<std::vector<double>>> traning_data);
	std::vector<Layer*> getLayers();

private:
	std::vector<int> structure;
	int size;
	std::vector<Layer*> layers;
	std::vector<std::vector<double>> previous_activation;
	std::vector<std::vector<double>> previous_inputs;
};