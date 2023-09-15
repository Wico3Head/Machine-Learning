#include "Layer.h"
#include "Node.h"

Layer::Layer(int size, int rank) {
	this->size = size;
	for (size_t i = 0; i < size; i++) {
		Node* node = new Node();
		nodes.push_back(node);
	}
}

int Layer::getSize() {
	return size;
}

int Layer::getRank() {
	return rank;
}

std::vector<Node*> Layer::getNodes() {
	return nodes;
}