#include "object.hpp"

class Solver  {
    private:
        sf::CircleShape constraint;
        VerletObject object;
        Vec2 gravity;
        float substeps;
        bool done;

        void applyConstraint() {
            Vec2 position =  constraint.getPosition();
            float radius = constraint.getRadius();
            float speed = pow(pow(object.velocity.x, 2) + pow(object.velocity.y, 2), 0.5);

            float obj_radius = object.obj.getRadius();
            float new_radius = object.obj.getRadius() + 5;
            float conserve_speed = (pow(new_radius, 2) - pow(obj_radius, 2)) / pow(obj_radius, 2);

            Vec2 to_object = object.position - position;
            float distance = pow(pow(to_object.x, 2) + pow(to_object.y, 2), 0.5);

            if (obj_radius > radius) {
                object.obj.setRadius(radius);
                object.obj.setOrigin(radius, radius);
                object.obj.setPosition(Vec2(500, 500));

                done = true;

                return;
            }

            if (distance > (radius - obj_radius) && object.timer.getElapsedTime().asSeconds() > 0.1) {
                Vec2 n = to_object / distance;

                object.position_last = position + n * (radius - obj_radius);
                object.position = object.position_last - n*speed;
                object.obj.setRadius(new_radius);
                object.timer.restart();

                speed *= 1 + conserve_speed;
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
            object = VerletObject(Vec2(4, -7));
            
            substeps = 2;
        }

        void renderObjects(sf::RenderWindow* target, float dt) {
            target->draw(constraint);
            
            float sub_dt = dt / substeps;

            if (!done) {
                for (int i = 0; i < substeps; i++) {
                    object.update(sub_dt);
                    object.accelerate(gravity);
                    applyConstraint();
                }
                object.updateTrace(object.obj.getPosition(), 60);
                for (int i = 0; i < object.trace.size(); i++) {
                    target->draw(object.trace[i]);
                }
            } else target->draw(object.obj);
        }
};