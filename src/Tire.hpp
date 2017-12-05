#ifndef TIRE_HPP
#define TIRE_HPP

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Level.hpp"

class Level;
class Tire {
    public:
        Tire(b2World& world, Settings& s, b2Vec2 position);
        void drawTo(sf::RenderWindow& window, Settings& s);
        b2Body* const getBody() const;
        b2Vec2 getLateralVelocity() const;
        b2Vec2 getParallelVelocity() const;
        void applyFriction(const Level& level);
        void accelerate(float force, float maxFwdSpeed, const Level& level);
        void decelerate(float force, float maxRevSpeed, const Level& level);
        void updateMovement(const Level& level);
    private:
        std::shared_ptr<PhysicsObject> tireObject;
        float drag = 0;
        float maxLateralImpulse = 5;
};

#endif
