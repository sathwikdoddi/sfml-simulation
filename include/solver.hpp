#include "object.hpp"

class Solver  {
    private:
        sf::CircleShape constraint;
        VerletObject object;
        Vec2 gravity;

        void applyConstraint() {
            Vec2 position =  constraint.getPosition();
            float radius = constraint.getRadius();

            Vec2 to_object = object.position - position;
            float distance = pow(pow(to_object.x, 2) + pow(to_object.y, 2), 0.5);

            if (distance > (radius - object.obj.getRadius())) {
                Vec2 n = to_object / distance;
                object.position = position + n * (radius - object.obj.getRadius());
            }
        }
    public:
        Solver() {            
            constraint.setPosition(Vec2(500, 500));
            constraint.setRadius(375);
            constraint.setOrigin(constraint.getRadius(), constraint.getRadius());
            constraint.setFillColor(sf::Color::Black);
            constraint.setOutlineThickness(10);
            constraint.setOutlineColor(sf::Color::White);
            constraint.setPointCount(100);

            gravity = Vec2(0, 1000);
        }

        void renderObjects(sf::RenderWindow* target, float dt) {
            target->draw(constraint);
            
            object.update(dt);
            object.accelerate(gravity);
            applyConstraint();

            target->draw(object.obj);
        }
};
