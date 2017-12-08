#include "Car.hpp"
#include "Settings.hpp"
#include "Constants.hpp"
#include <iostream>
#include <algorithm>
Car::Car(b2World& world, const Settings& s, Level& l, b2Vec2 position, sf::Color color) : s(s), level(l) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.3;
    std::vector<std::pair<float,float>> bodyVertices = {
        std::make_pair(0.5, 0.0),
        std::make_pair(0.25, 1.25),
        std::make_pair(0.25, 1.75),
        std::make_pair(0.75, 3.0),
        std::make_pair(1.25, 3.0),
        std::make_pair(1.75, 1.75),
        std::make_pair(1.75, 1.25),
        std::make_pair(1.5, 0.0)
    };
    bodyObject = std::make_shared<PhysicsObject>(world, s, bodyVertices, bodyDef, fixtureDef, color);
    //Set the positions of the tires relative to the center of the mass of the car's body.
    std::vector<std::pair<float,float>> tireOffsets = {
        std::make_pair(-1.0, 1.25),
        std::make_pair(1.0, 1.25),
        std::make_pair(-1.0, -1.0),
        std::make_pair(1.0, -1.0)
    };
    b2Vec2 bodyPos = bodyObject->getBody()->GetWorldCenter();
    for (auto it : tireOffsets) {
        Tire newTire(world, s, level, b2Vec2(bodyPos.x + it.first, bodyPos.y + it.second));
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = bodyObject->getBody();
        jointDef.bodyB = newTire.getBody();
        jointDef.enableLimit = true;
        b2Vec2 tireRelativePosition(it.first, it.second);
        tireRelativePosition += bodyObject->getBody()->GetLocalCenter();
        jointDef.localAnchorA = tireRelativePosition;
        jointDef.localAnchorB = newTire.getBody()->GetLocalCenter();
        b2RevoluteJoint* newJoint = static_cast<b2RevoluteJoint*>(world.CreateJoint(&jointDef));
        tireJoints.push_back(newJoint);
        tires.push_back(newTire);
    }
}

void Car::accelerate() {
    for (size_t i = 0; i < 2; i++) {
        tires.at(i).accelerate(acceleration, maxForwardSpeed);
    }
}

void Car::decelerate() {
    for (auto it : tires) {
        it.decelerate(deceleration, maxReverseSpeed);
    }
}

void Car::turnLeft() {
    turning = true;
    for (size_t i = 0; i < 2; i++) {
        b2RevoluteJoint* joint = tireJoints.at(i);
        float currentAngle = joint->GetJointAngle();
        if (currentAngle < (maxTurnAngle * DEGTORAD)) {
            float newAngle = currentAngle + turnPerStep * DEGTORAD;
            currentAngle = newAngle;
            joint->SetLimits(newAngle, newAngle);
        }
    }
}

void Car::turnRight() {
    turning = true;
    for (size_t i = 0; i < 2; i++) {
        b2RevoluteJoint* joint = tireJoints.at(i);
        float currentAngle = joint->GetJointAngle();
        if (currentAngle > (-maxTurnAngle * DEGTORAD)) {
            float newAngle = currentAngle - turnPerStep * DEGTORAD;
            currentAngle = newAngle;
            joint->SetLimits(newAngle, newAngle);
        }
    }
}

void Car::updateMovement() {
    for (auto it : tires) {
        it.updateMovement();
    } 
    if (turning) {
        turning = false;
    } else {
        for (size_t i = 0; i < 2; i++) {
            b2RevoluteJoint* joint = tireJoints.at(i);
            joint->SetLimits(0.25 * joint->GetUpperLimit(), 0.25 * joint->GetUpperLimit());
        }
    }
}

void Car::drawTo(sf::RenderWindow& window) {
    bodyObject->drawTo(window);
    for (auto it : tires) {
        it.drawTo(window);
    }
}

void Car::addCheckpoint(unsigned int checkpoint, unsigned int numLevelCheckpoints){
  if(std::find(this->checkpoints.begin(), this->checkpoints.end(), checkpoint) != this->checkpoints.end()){
    
  }
  else {
    if(this->checkpoints.size()  == checkpoint) {
      this->checkpoints.push_back(checkpoint);
      if(this->checkpoints.size() == numLevelCheckpoints){
	this->addLap();
	this->checkpoints.clear();
      }
    }
  }
}
