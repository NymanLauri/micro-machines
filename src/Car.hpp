/* The class for the cars controlled by the players. Car constructor takes as parameters:
 *     - the b2World into which the car will be created
 *     - the settings for coordinate conversions etc.
 *     - the level into which the car will be placed
 *     - the starting position of the car
 *     - the color of the car's body (optional, defaults to white).
 */

#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Level.hpp"
#include "Tire.hpp"

class Level;
class Tire;
class Car {
    public:
        Car(b2World& world, const Settings& s, Level& l, b2Vec2 position, sf::Color color = sf::Color::White);
        void drawTo(sf::RenderWindow& window);
        void accelerate();
        void decelerate();
        void turnLeft();
        void turnRight();
        void updateMovement(); // This method must be called with every loop of the physics simulation to handle the friction and turning correctly.
        int getLap(){return this->lap;};
        void addLap(){this->lap += 1;};
        void addCheckpoint(unsigned int checkpoint, unsigned int numLevelCheckpoints);
  //std::vector<unsigned int> getCheckpoints() {return this->checkpoints;}
        b2Vec2 getPosition(){return this->bodyObject->getPosition();}
  unsigned int checkpointVecSize() {return this->checkpoints.size();}
    private:
        std::vector<unsigned int> checkpoints;
        int lap = 1;
        std::shared_ptr<PhysicsObject> bodyObject;
        std::vector<Tire> tires;
        std::vector<b2RevoluteJoint*> tireJoints;
        const Settings& s;
        Level& level;
        float maxForwardSpeed = 100.0;
        float maxReverseSpeed = 10.0;
        float acceleration = 60.0;
        float deceleration = 60.0;
        float turnPerStep = 3.0;
        float maxTurnAngle = 30.0;
        bool turning = false;
};

#endif
