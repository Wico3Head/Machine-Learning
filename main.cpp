#include "Network.h"
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    std::vector<int> structure = { 3, 2, 3 };
    Network* network = new Network(structure);

    std::vector<double> inputs = { 1, 2, 3 };
    std::vector<double> outputs = network->activate(inputs);
    for (double num : outputs) {
        std::cout << num << std::endl;

    }
}