#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

typedef sf::Vector2f Vec2;

struct VerletObject {
    sf::CircleShape obj;
    std::vector<sf::CircleShape> trace;
    sf::Clock timer;
    Vec2 position_last;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    VerletObject() {
        timer.restart();
        acceleration = Vec2(0, 0);

        obj.setFillColor(sf::Color::White);
        obj.setRadius(30);
        obj.setOrigin(obj.getRadius(), obj.getRadius());
        obj.setOutlineThickness(2);
        obj.setOutlineColor(sf::Color::Black);
        obj.setPointCount(30);

        Vec2 initPosition(500, 500);
        obj.setPosition(initPosition);

        position =  initPosition;
        position_last = initPosition;
    }

    VerletObject(Vec2 velocity) {
        timer.restart();
        acceleration = Vec2(0, 0);

        obj.setFillColor(sf::Color::White);
        obj.setRadius(30);
        obj.setOrigin(obj.getRadius(), obj.getRadius());
        obj.setOutlineThickness(2);
        obj.setOutlineColor(sf::Color::Black);
        obj.setPointCount(50);

        Vec2 initPosition(500, 500);
        obj.setPosition(initPosition);

        position =  initPosition + velocity;
        position_last = initPosition;
    }

    void update(float dt) {
        velocity = position - position_last;
        position_last = position;
        position = position + velocity + acceleration * dt * dt;

        acceleration = Vec2();
        obj.setPosition(position);
    }

    void updateTrace(Vec2 pos, int trace_max) {
        sf::CircleShape c;
        c.setRadius(obj.getRadius());
        c.setOrigin(c.getRadius(), c.getRadius());
        c.setPosition(pos);
        c.setFillColor(sf::Color::White);
        c.setPointCount(obj.getPointCount());
        c.setOutlineThickness(2);
        c.setOutlineColor(sf::Color::Black);

        trace.push_back(c);
        while (trace.size() > trace_max) {
            trace.erase(trace.begin());
        }
    }

    void accelerate(Vec2 a) {
        acceleration += a;
    }
};