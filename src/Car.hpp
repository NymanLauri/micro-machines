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
        int getLap(){return this->lap;};
        void addLap(){this->lap += 1;};
        void addCheckpoint(unsigned int checkpoint, unsigned int numLevelCheckpoints);
  //std::vector<unsigned int> getCheckpoints() {return this->checkpoints;}
        b2Vec2 getPosition(){return this->bodyObject->getPosition();}
    private:
        std::vector<unsigned int> checkpoints;
        int lap = 1;
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
