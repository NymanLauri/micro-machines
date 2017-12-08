/* The class for the tires of the car. Tires handle the movement of the car.
 * Some methods of the Tire class are loosely based on the Box2D top-down car physics
 * tutorial found at http://www.iforce2d.net/b2dtut/top-down-car
 */

#ifndef TIRE_HPP
#define TIRE_HPP

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Level.hpp"

class Level;
class Tire {
    public:
        Tire(b2World& world, const Settings& s, Level& l, b2Vec2 position);
        void drawTo(sf::RenderWindow& window);
        b2Body* const getBody() const;
        b2Vec2 getLateralVelocity() const;
        b2Vec2 getParallelVelocity() const;
        void applyFriction();
        void accelerate(float force, float maxFwdSpeed);
        void decelerate(float force, float maxRevSpeed);
        void updateMovement();
    private:
        std::shared_ptr<PhysicsObject> tireObject;
        const Settings& s;
        Level& level;
        float maxLateralImpulse = 5;
};

#endif
