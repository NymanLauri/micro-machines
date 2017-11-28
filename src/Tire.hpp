#ifndef TIRE_HPP
#define TIRE_HPP

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Level.hpp"

class Level;
class Tire {
    public:
        Tire(b2World& world, Settings& s, b2Vec2 position, float drag = 1.0, float maxLateralImpulse = 10);
        void drawTo(sf::RenderWindow& window, Settings& s);
        b2Body* const getBody() const;
        b2Vec2 getLateralVelocity() const;
        b2Vec2 getParallelVelocity() const;
        //bool isSliding() const;
        void applyFriction(const Level& level);
        void accelerate(float force, float maxFwdSpeed);
        void decelerate(float force, float maxRevSpeed);
        void updateMovement(const Level& level);
    private:
        std::shared_ptr<PhysicsObject> tireObject;
        float drag;
        float maxLateralImpulse;
};

#endif
