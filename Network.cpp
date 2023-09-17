#include "Network.h"
#include "Layer.h"
#include "Node.h"
#include "Global.h"
#include <vector>
#include <time.h>
#include <algorithm>
#include "iostream"

double sigmoidActivate(double input) {
	return 1 / (1 + exp(-input));
}

double sigmoidActivateGradient(double input) {
	double sigmoidValue = sigmoidActivate(input);
	return sigmoidValue * (1 - sigmoidValue);
}


double lreluActivate(double input) {
	return std::max(0.1 * input, input);
}

double lreluActivateGradient(double input) {
	return input > 0 ? 1 : 0.1;
}

Network::Network(std::vector<int> structure) {
	srand((unsigned)time(NULL));
	this->structure = structure;
	size = structure.size();
	layers.clear();
	for (int current_layer = 0; current_layer < structure.size(); current_layer++) {
		Layer* layer = new Layer(structure.at(current_layer), current_layer);
		for (Node* node : layer->getNodes()) {
			if (current_layer != structure.size() - 1) {
				std::vector<double> weights = {};
				for (size_t output_node = 0; output_node < structure.at(current_layer + 1); output_node++) {
					weights.push_back((double)rand() / RAND_MAX * 2 * WEIGHT_INITIALISATION_SIZE - WEIGHT_INITIALISATION_SIZE);
				}
				node->setWeights(weights);
			}
			if (current_layer != 0) {
				node->setBias((double)rand() / RAND_MAX * 2 * BIAS_INITIALISATION_SIZE - BIAS_INITIALISATION_SIZE);
			}
			else{
				node->setBias(0);
			}
		}
		layers.push_back(layer);
	}
}

std::vector<double> Network::activate(std::vector<double> inputs) {
	previous_activation.clear();
	previous_inputs = { inputs };
	std::vector<double> current_layer_inputs = {};
	std::vector<double> non_activation_outputs;
	for (double input : inputs) {
		current_layer_inputs.push_back(lreluActivate(input));
	}
	std::vector<double> current_layer_outputs;
	for (size_t current_layer = 0; current_layer < structure.size() - 1; current_layer++) {
		previous_activation.push_back(current_layer_inputs);
		current_layer_outputs.clear();
		non_activation_outputs.clear();
		std::vector<Node*> input_layer = layers.at(current_layer)->getNodes();
		std::vector<Node*> output_layer = layers.at(current_layer + 1)->getNodes();
		for (size_t current_output_node = 0; current_output_node < output_layer.size(); current_output_node++){
			double output = 0;
			for (size_t current_input_node = 0; current_input_node < input_layer.size(); current_input_node++) {
				output += current_layer_inputs.at(current_input_node) * input_layer.at(current_input_node)->getWeights().at(current_output_node);
			}
			output += output_layer.at(current_output_node)->getBias();
			non_activation_outputs.push_back(output);
			current_layer_outputs.push_back(lreluActivate(output));
		}
		current_layer_inputs = current_layer_outputs;
		previous_inputs.push_back(non_activation_outputs);
	}
	previous_activation.push_back(current_layer_outputs);
	return current_layer_outputs;
}

void Network::learn(std::vector<std::vector<std::vector<double>>> training_data) {

	std::vector<std::vector<std::vector<double>>> weight_alterations;
	std::vector<std::vector<double>> bias_alterations;

	for (size_t current_layer = structure.size() - 1; current_layer > 0; current_layer--) {
		std::vector<Node*> layer = layers.at(current_layer)->getNodes();
		std::vector<double> layer_bias_alteration;
		std::vector<std::vector<double>> layer_weight_alteration;
		for (size_t current_node = 0; current_node < layer.size(); current_node++) {
			int weight_size = layer.at(current_node)->getWeights().size();
			layer_bias_alteration.push_back(0.0f);
			std::vector<double> node_weight_alteration;
			for (size_t current_weight = 0; current_weight < weight_size; current_weight++) {
				node_weight_alteration.push_back(0.0f);
			}
			layer_weight_alteration.push_back(node_weight_alteration);
		}
		weight_alterations.push_back(layer_weight_alteration);
		bias_alterations.push_back(layer_bias_alteration);
	}

	for (std::vector<std::vector<double>> training_pair : training_data) {
		std::vector<double> inputs = training_pair.at(0);
		std::vector<double> expected_outputs = training_pair.at(1);

		std::vector<double> current_layer_gradients = {};
		activate(inputs);
		std::vector<double> last_layer_activation = previous_activation.at(size - 1);
		std::vector<double> last_layer_inputs = previous_inputs.at(size - 1);
		for (size_t node = 0; node < expected_outputs.size(); node++) {
			current_layer_gradients.push_back(2 * (last_layer_activation.at(node) - expected_outputs.at(node)) * lreluActivateGradient(last_layer_inputs.at(node)));
		}

		for (size_t current_layer = structure.size() - 1; current_layer > 0; current_layer--) {
			std::vector<Node*> layer = layers.at(current_layer)->getNodes();
			for (size_t current_node = 0; current_node < layer.size(); current_node++) {
				Node* node = layer.at(current_node);
				node->alterBias(-current_layer_gradients.at(current_node) * LEARN_RATE);
			}

			std::vector<double> weight_alterations;
			std::vector<double> previous_layer_gradients = {};
			std::vector<Node*> previous_layer = layers.at(current_layer - 1)->getNodes();
			std::vector<double> previous_layer_inputs = previous_inputs.at(current_layer - 1);
			for (size_t current_node = 0; current_node < previous_layer.size(); current_node++) {
				weight_alterations.clear();
				Node* node = previous_layer.at(current_node);
				std::vector<double> node_weights = node->getWeights();
				double node_activation = previous_activation.at(current_layer - 1).at(current_node);
				double node_cost_gradient = 0;
				for (size_t current_weight = 0; current_weight < node_weights.size(); current_weight++) {
					weight_alterations.push_back(-current_layer_gradients.at(current_weight) * node_activation * LEARN_RATE);
					node_cost_gradient += current_layer_gradients.at(current_weight) * node_weights.at(current_weight) * lreluActivateGradient(previous_layer_inputs.at(current_node));
				}
				node->alterWeights(weight_alterations);
				previous_layer_gradients.push_back(node_cost_gradient);
			}
			current_layer_gradients = previous_layer_gradients;
		}
	}
}

std::vector<Layer*> Network::getLayers() {
	return layers;
}