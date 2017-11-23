#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Tire.hpp"

class Car {
    public:
        Car(b2World& world, b2Vec2 position, sf::Color color = sf::Color::White);
        void drawTo(sf::RenderWindow& window);
        void accelerate();
        void decelerate();
        void turnLeft();
        void turnRight();
        void updateMovement();
    private:
        std::shared_ptr<PhysicsObject> bodyObject;
        std::vector<Tire> tires;
        std::vector<b2RevoluteJoint*> tireJoints;
        float maxForwardSpeed = 100.0;
        float maxReverseSpeed = 10.0;
        float acceleration = 60.0;
        float deceleration = 60.0;
        float turnPerStep = 3.0;
        float maxTurnAngle = 50.0;
};

#endif
