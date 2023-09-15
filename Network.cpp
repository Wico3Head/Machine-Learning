#include "Network.h"
#include "Layer.h"
#include "Node.h"
#include <vector>

double sigmoidActivate(double input) {
	return 1 / (1 + exp(-input));
}

Network::Network(std::vector<int> structure) {
	this->structure = structure;
	for (size_t current_layer = 0; current_layer < structure.size(); current_layer++) {
		Layer* layer = new Layer(structure.at(current_layer), current_layer, (current_layer == structure.size() - 1)? structure.at(current_layer+1) : 0, current_layer == 0);
		layers.push_back(layer);
	}
}

std::vector<double> Network::activate(std::vector<double> inputs) {
	std::vector<double> current_layer_inputs = inputs;
	std::vector<double> current_layer_outputs;
	for (size_t current_layer = 0; current_layer < structure.size() - 1; current_layer++) {
		current_layer_outputs.clear();
		std::vector<Node*> input_layer = layers.at(current_layer)->getNodes();
		std::vector<Node*> output_layer = layers.at(current_layer + 1)->getNodes();
		for (size_t current_output_node = 0; current_output_node < output_layer.size(); current_output_node++){
			double output = 0;
			for (size_t current_input_node = 0; current_input_node < input_layer.size(); current_input_node++) {
				output += current_layer_inputs.at(current_input_node) * input_layer.at(current_input_node)->getWeights().at(current_output_node);
			}
			output += output_layer.at(current_output_node)->getBias();
			current_layer_outputs.push_back(sigmoidActivate(output));
		}
		current_layer_inputs = current_layer_outputs;
	}
	return current_layer_outputs;
}