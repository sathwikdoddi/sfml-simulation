#include <SFML/Graphics.hpp>
#include "include/solver.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "TikTok Circle Simulation");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}