#include "Network.h"
#include "Layer.h"
#include "Node.h"

Network::Network(std::vector<int> structure) {
	this->structure = structure;
	int current_layer = 1;
	for (int size : structure) {
		Layer* layer = new Layer(size, current_layer);
		layers.push_back(layer);
	}
}