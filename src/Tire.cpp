/* Some methods of the Tire class are loosely based on the Box2D top-down car physics
 * tutorial found at http://www.iforce2d.net/b2dtut/top-down-car
 */

#ifndef TIRE_HPP
#define TIRE_HPP

#include "Tire.hpp"
#include "Settings.hpp"
#include <iostream>
Tire::Tire(b2World& world, b2Vec2 position, float drag, float mli) : drag(drag), maxLateralImpulse(mli) {
    b2BodyDef tireBodyDef;
    tireBodyDef.type = b2_dynamicBody;
    tireBodyDef.position = position;
    b2FixtureDef tireFixtureDef;
    tireFixtureDef.density = 1.0;
    tireFixtureDef.friction = 0.3;
    tireObject = std::make_shared<PhysicsObject>(world, b2Vec2(0.25, 0.75), tireBodyDef, tireFixtureDef, sf::Color::Black);
};

b2Vec2 Tire::getLateralVelocity() const {
    b2Vec2 lateralDirection = getBody()->GetWorldVector(b2Vec2(1.0, 0.0));
    float projectionLength = b2Dot(getBody()->GetLinearVelocity(), lateralDirection);
    return projectionLength * lateralDirection;
}

b2Vec2 Tire::getParallelVelocity() const {
    b2Vec2 forwardDirection = getBody()->GetWorldVector(b2Vec2(0.0, 1.0));
    float projectionLength = b2Dot(getBody()->GetLinearVelocity(), forwardDirection);
    return projectionLength * forwardDirection;
}

void Tire::applyFriction() {
    b2Body* const body = getBody();
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    b2Vec2 direction = -getParallelVelocity();
    direction.Normalize();
    b2Vec2 forceVec = body->GetMass() * 10 * drag * direction;
    forceVec += 0.1 * drag * -getParallelVelocity();
    body->ApplyForce(forceVec, body->GetWorldCenter(), true); 
}

void Tire::accelerate(float force, float maxFwdSpeed) {
    if (getParallelVelocity().Length() < maxFwdSpeed) {
        b2Body* const body = getBody();
        b2Vec2 direction = body->GetWorldVector(b2Vec2(0.0, 1.0));
        direction.Normalize();
        body->ApplyForce(force * direction, body->GetWorldCenter(), true);
    }
}

void Tire::decelerate(float force, float maxRevSpeed) {
    b2Vec2 moveDirection = getBody()->GetLinearVelocity();
    b2Vec2 forwardsDirection = getBody()->GetWorldVector(b2Vec2(0.0, 1.0));
    float cosAngle = b2Dot(moveDirection, forwardsDirection) / (moveDirection.Length() * forwardsDirection.Length());
    if (cosAngle > 0 || (getParallelVelocity().Length() < maxRevSpeed)) {
        b2Body* const body = getBody();
        b2Vec2 direction = -forwardsDirection;
        direction.Normalize();
        body->ApplyForce(force * direction, body->GetWorldCenter(), true);
    }
}


void Tire::updateMovement() {
    applyFriction();
}

#endif
