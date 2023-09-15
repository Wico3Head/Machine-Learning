#include "Layer.h"
#include "Node.h"

Layer::Layer(int size, int rank) {
	this->size = size;
	this->rank = rank;
	for (size_t i = 0; i < size; i++) {
		Node* node = new Node(rank);
		nodes.push_back(node);
	}
}