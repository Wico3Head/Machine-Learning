#include "Node.h"
#include "Global.h"
#include <vector>
#include <iostream>

Node::Node() {
}

void Node::setWeights(std::vector<double> weights) {
	this->weights = weights;
}

void Node::alterWeights(std::vector<double> alterations) {
	for (size_t current_weight = 0; current_weight < weights.size(); current_weight++) {
		weights.at(current_weight) += alterations.at(current_weight);
	}
}

std::vector<double> Node::getWeights() {
	return weights;
}

void Node::setBias(double bias) {
	this->bias = bias;
}

void Node::alterBias(double alteration) {
	bias += alteration;
}

double Node::getBias() {
	return bias;
}