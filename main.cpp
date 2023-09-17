#include "Network.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>

double identifyFucntion(double x, double y) {
    return (x < y) ? 1 : 0;
}

double getAccuracy(Network* network) {
    int accurate = 0;
    for (double i = 1; i < 101; i++) {
        for (double j = 1; j < 101; j++) {
            std::vector<double> input = { i, j };
            std::vector<double> output = network->activate(input);
            if (output.at(0) > output.at(1) == (identifyFucntion(i, j) == 0)) {
                accurate += 1;
            }
        }
    }
    return (double)accurate / 10000 * 100;
}

int main()
{
    srand(time(0));
    std::vector<int> structure = { 2, 3, 3, 2 };
    Network* network = new Network(structure);

    sf::RenderWindow window(sf::VideoMode(300, 300), "Machine Learning");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::cout << getAccuracy(network) << std::endl;
        std::vector<std::vector<std::vector<double>>> training_data;
        for (size_t i = 0; i < 200; i++) {
            double x = (double) rand() / RAND_MAX;
            double y = (double) rand() / RAND_MAX;
            double expected_output = identifyFucntion(x*100, y*100);

            std::vector<double> input = { x, y };
            std::vector<double> expected_outputs = { 1 - expected_output, expected_output };
            std::vector<std::vector<double>> training_pair = { input, expected_outputs };
            training_data.push_back(training_pair);
        }
        network->learn(training_data);
        network->printWeights();
        
        window.clear(sf::Color::Black);
        for (double i = 1; i < 101; i++) {
            for (double j = 1; j < 101; j++) {
                std::vector<double> inputs = { i/100, j/100 };
                std::vector<double> outputs = network->activate(inputs);
                int decision = outputs.at(0) > outputs.at(1) ? 0 : 1;
                sf::RectangleShape rectangle(sf::Vector2f(3.0f, 3.0f));
                rectangle.setFillColor( decision == 1 ? sf::Color::Red : sf::Color::Blue);
                rectangle.setPosition(3 * (i - 1), 3 * (100-j));
                window.draw(rectangle);
            }
        }
        window.display();
    }
    return 0;
}