#include "Layer.h"
#include "Node.h"

Layer::Layer(int size, int rank, int next_layer_size, bool is_first_layer) {
	this->size = size;
	this->rank = rank;
	for (size_t i = 0; i < size; i++) {
		Node* node = new Node(next_layer_size, is_first_layer);
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