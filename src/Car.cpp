#include "Car.hpp"
#include "Settings.hpp"
#include "Constants.hpp"
#include <algorithm>
Car::Car(b2World& world, const Settings& s, Level& l, b2Vec2 position, sf::Color color) : s(s), level(l) { // The constructor of the Car-class.
    // Create the body of the car.
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
    // Set the positions of the tires relative to the center of the mass of the car's body.
    std::vector<std::pair<float,float>> tireOffsets = {
        std::make_pair(-1.0, 1.25),
        std::make_pair(1.0, 1.25),
        std::make_pair(-1.0, -1.0),
        std::make_pair(1.0, -1.0)
    };
    b2Vec2 bodyPos = bodyObject->getBody()->GetWorldCenter();
    // Create the Tire objects of the car and attach them to the body of the car
    // using b2RevoluteJoints.
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
    // Only the front tires accelerate the car.
    for (size_t i = 0; i < 2; i++) {
        tires.at(i).accelerate(acceleration, maxForwardSpeed);
    }
}

void Car::decelerate() {
    // All tires brake.
    for (auto it : tires) {
        it.decelerate(deceleration, maxReverseSpeed);
    }
}

void Car::turnLeft() { // Turn the car to the left.
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

void Car::turnRight() { // Turn the car to the right.
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
    // If the car has been set to turn during this iteration, set the turning boolean to false for the
    // next iteration (where it may be set to true again, if the turning key is still pressed).
    // If the car is not turning, quickly restore the tires to the default position.
    if (turning) {
        turning = false;
    } else {
        for (size_t i = 0; i < 2; i++) {
            b2RevoluteJoint* joint = tireJoints.at(i);
            joint->SetLimits(0.25 * joint->GetUpperLimit(), 0.25 * joint->GetUpperLimit());
        }
    }
}

void Car::drawTo(sf::RenderWindow& window) { // Draw the car to the game window.
    bodyObject->drawTo(window);
    for (auto it : tires) {
        it.drawTo(window);
    }
}

// This function is used to tell the program that a car has passed a certain checkpoint.
void Car::addCheckpoint(unsigned int checkpoint, unsigned int numLevelCheckpoints){
  // Do nothing if a car already has a certain checkpoint.
  if(std::find(this->checkpoints.begin(), this->checkpoints.end(), checkpoint) != this->checkpoints.end()){
    
  }
  // Checkpoints are ordered (by the pointer's index std::find(...) - this->checkpoints.begin()). Checking if a checkpoint is
  // the correct next checkpoint (assuming correct order of checkpoints) is comparing the checkpoint's index by the car's checkpoint vector's length.
  else {
    if(this->checkpoints.size()  == checkpoint) {
      this->checkpoints.push_back(checkpoint);
      // If the added checkpoint fills the car's checkpoint vector, add a lap and reinitialize
      if(this->checkpoints.size() == numLevelCheckpoints){
	this->addLap();
	this->checkpoints.clear();
      }
    }
  }
}
