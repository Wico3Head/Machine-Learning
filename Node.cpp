#include "Node.h"
#include "Global.h"
#include <time.h>
#include <vector>

Node::Node(int connections, bool is_first_layer) {
	srand((unsigned)time(NULL));

	first_layer = is_first_layer;
	this->connections = connections;
	for (size_t i = 0; i < connections; i++) {
		weights.push_back(rand() / RAND_MAX * 2 * WEIGHT_INITIALISATION_SIZE - WEIGHT_INITIALISATION_SIZE);
	}
	
	if (!first_layer) {
		bias = rand() / RAND_MAX * 2 * BIAS_INITIALISATION_SIZE - BIAS_INITIALISATION_SIZE;
	}
	else {
		bias = 0;
	}
}

void Node::setWeights(std::vector<double> weights) {
	this->weights = weights;
}

std::vector<double> Node::getWeights() {
	return weights;
}

void Node::setBias(double bias) {
	this->bias = bias;
}

double Node::getBias() {
	return bias;
}