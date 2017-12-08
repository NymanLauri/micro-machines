#include "Tire.hpp"
#include "Settings.hpp"

Tire::Tire(b2World& world, const Settings& s, Level& l, b2Vec2 position) : s(s), level(l) {
    b2BodyDef tireBodyDef;
    tireBodyDef.type = b2_dynamicBody;
    tireBodyDef.position = position;
    b2FixtureDef tireFixtureDef;
    tireFixtureDef.density = 1.0;
    tireFixtureDef.friction = 0.3;
    tireObject = std::make_shared<PhysicsObject>(world, s, b2Vec2(0.25, 0.75), tireBodyDef, tireFixtureDef, sf::Color::Black);
}

void Tire::drawTo(sf::RenderWindow& window) {
    tireObject->drawTo(window);
}

b2Body* const Tire::getBody() const {
    return tireObject->getBody();
}

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
    float friction = level.getFrictionMultiplier(body->GetPosition());
    // Get the magnitude and direction of the impulse needed to stop all lateral motion of
    // of the car.
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    // Scale down the impulse if it is larger than the maximum value.
    if (impulse.Length() > maxLateralImpulse * friction) {
        impulse.Normalize();
        impulse *= maxLateralImpulse * friction;
    }
    // Multiply the impulse by 0.8 so that the sideways velocity is never killed completely;
    // this gives the car a more "gamey" feel.
    impulse *= 0.8;
    // Apply the impulse.
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    b2Vec2 direction = -getParallelVelocity();
    direction.Normalize();
    // Apply a force opposite to the direction the car is moving in;
    // this simulates friction between the road and the tires and drag.
    b2Vec2 forceVec = body->GetMass() * 10 * friction * direction;
    forceVec += 0.1 * friction * -getParallelVelocity();
    body->ApplyForce(forceVec, body->GetWorldCenter(), true); 
}

void Tire::accelerate(float force, float maxFwdSpeed) {
    // Get the friction multiplier for the tire's position from the level.
    float friction = level.getFrictionMultiplier(getBody()->GetPosition());
    // If the friction multiplier is less than 1, the car will accelerate more slowly.
    // Otherwise the acceleration is unaffected.
    friction = friction < 1.0 ? friction : 1.0;
    if (getParallelVelocity().Length() < maxFwdSpeed) {
        b2Body* const body = getBody();
        b2Vec2 direction = body->GetWorldVector(b2Vec2(0.0, 1.0));
        direction.Normalize();
        body->ApplyForce(force * friction * direction, body->GetWorldCenter(), true);
    }
}

void Tire::decelerate(float force, float maxRevSpeed) {
    float friction = level.getFrictionMultiplier(getBody()->GetPosition());
    friction = friction < 1.0 ? friction : 1.0;
    b2Vec2 moveDirection = getBody()->GetLinearVelocity();
    b2Vec2 forwardDirection = getBody()->GetWorldVector(b2Vec2(0.0, 1.0));
    // Check if the car is moving forwards or backwards using the cosine formula for vectors.
    float cosAngle = b2Dot(moveDirection, forwardDirection) / (moveDirection.Length() * forwardDirection.Length());
    // If the car is moving forwards (cosAngle > 0), apply braking force opposite to move direction.
    if (cosAngle > 0) {
        b2Vec2 direction = -moveDirection;
        direction.Normalize();
        getBody()->ApplyForce(force * friction * direction, getBody()->GetWorldCenter(), true);
    // If the car is moving backwards at less than maximum reverse speed, apply accelerating force
    // opposite to forward direction.
    } else if (getParallelVelocity().Length() < maxRevSpeed) {
        b2Vec2 direction = -forwardDirection;
        direction.Normalize();
        getBody()->ApplyForce(force * friction * direction, getBody()->GetWorldCenter(), true);
    }
}

// Update movement is a separate method in order to enable easy addition of other movement affecting features
// than only friction.
void Tire::updateMovement() {
    applyFriction();
}
