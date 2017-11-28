#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"

class Tire {
    public:
        Tire(b2World& world, Settings& s, b2Vec2 position, float drag = 1.0, float maxLateralImpulse = 10);
        void drawTo(sf::RenderWindow& window, Settings& s) { tireObject->drawTo(window, s); }
        b2Body* const getBody() const { return tireObject->getBody(); }
        b2Vec2 getLateralVelocity() const;
        b2Vec2 getParallelVelocity() const;
        bool isSliding() const;
        void applyFriction();
        void accelerate(float force, float maxFwdSpeed);
        void decelerate(float force, float maxRevSpeed);
        void updateMovement();
    private:
        std::shared_ptr<PhysicsObject> tireObject;
        float drag;
        float maxLateralImpulse;
};
