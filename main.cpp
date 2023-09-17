#include "Network.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

double identifyFucntion(double x, double y) {
    return (0.05 * x + 45 < y) ? 1 : 0;
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

int gmain()
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
        for (size_t i = 0; i < 200; i++) {
            int x = (double) rand() / RAND_MAX * 100;
            int y = (double) rand() / RAND_MAX * 100;
            double expected_output = identifyFucntion(x, y);

            std::vector<double> input = { (double)x, (double)y };
            std::vector<double> expected_outputs = { 1 - expected_output, expected_output };
            //network->learn(input, expected_outputs);
        }
        
        window.clear(sf::Color::Black);
        for (double i = 1; i < 101; i++) {
            for (double j = 1; j < 101; j++) {
                std::vector<double> inputs = { i, j };
                std::vector<double> outputs = network->activate(inputs);
                int decision = outputs.at(0) > outputs.at(1) ? 0 : 1;
                std::cout << outputs.at(0) << " , " << outputs.at(1) << std::endl;
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

std::vector<double> test(double num) {
    if (num < 33) {
        return { 1, 0, 0 };
    }
    else if (num < 66) {
        return { 0, 1, 0 };
    }
    return { 0, 0, 1 };
}

int main() {
    Network* network = new Network({1, 2, 3});
    std::vector<std::vector<std::vector<double>>> training_data = {};
    for (size_t i = 0; i < 50; i++) {
        int y = (double)rand() / RAND_MAX * 100;
        training_data.push_back({ {(double)y}, {test(y)} });
    }
    network->learn(training_data);
    
    for (size_t i = 0; i < 100; i++) {
        std::vector<double> outputs = network->activate({ (double) i });
        std::cout << outputs.at(0) << " , " << outputs.at(1) << " , " << outputs.at(2) << std::endl;
    }

    return 0;
}