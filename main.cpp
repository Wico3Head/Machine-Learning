#include "Network.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <time.h>

double sigmoid(double input) {
    return 1 / (1 + exp(-input));
}

int main()
{
    srand(time(0));

    std::vector<int> structure = { 3, 2, 3 };
    Network* network = new Network(structure);

    std::vector<double> inputs = { 2, 1, 3 };
    std::vector<double> outputs = network->activate(inputs);
    for (double num : outputs) {
        std::cout << num << std::endl;
    }
}