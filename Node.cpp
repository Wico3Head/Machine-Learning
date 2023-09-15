#include "Node.h"
#include "Global.h"
#include <vector>
#include <iostream>

Node::Node() {
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