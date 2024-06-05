#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

typedef sf::Vector2f Vec2;

struct VerletObject {
    sf::CircleShape obj;
    std::vector<Vec2> trace;
    sf::Clock time_alive;
    Vec2 position_last;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    VerletObject() {
        time_alive.restart();
        acceleration = Vec2(0, 0);

        obj.setFillColor(sf::Color::White);
        obj.setRadius(30);
        obj.setOrigin(obj.getRadius(), obj.getRadius());
        obj.setOutlineThickness(2);
        obj.setOutlineColor(sf::Color::Black);
        obj.setPointCount(50);

        Vec2 initPosition(500, 500);
        obj.setPosition(initPosition);

        position =  initPosition;
        position_last = initPosition;
    }

    void update(float dt) {
        velocity = position - position_last;
        position_last = position;
        position = position + velocity + acceleration * dt * dt;

        acceleration = Vec2();
        obj.setPosition(position);
    }

    void accelerate(Vec2 a) {
        acceleration += a;
    }
};