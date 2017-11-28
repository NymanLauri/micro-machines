/* Some methods of the Tire class are loosely based on the Box2D top-down car physics
 * tutorial found at http://www.iforce2d.net/b2dtut/top-down-car
 */

#include "Tire.hpp"
#include "Settings.hpp"

Tire::Tire(b2World& world, Settings& s, b2Vec2 position, float drag, float mli) : drag(drag), maxLateralImpulse(mli) {
    b2BodyDef tireBodyDef;
    tireBodyDef.type = b2_dynamicBody;
    tireBodyDef.position = position;
    b2FixtureDef tireFixtureDef;
    tireFixtureDef.density = 1.0;
    tireFixtureDef.friction = 0.3;
    tireObject = std::make_shared<PhysicsObject>(world, s, b2Vec2(0.25, 0.75), tireBodyDef, tireFixtureDef, sf::Color::Black);
}

void Tire::drawTo(sf::RenderWindow& window, Settings& s) {
    tireObject->drawTo(window, s);
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

void Tire::applyFriction(const Level& level) {
    b2Body* const body = getBody();
    float friction = drag * level.getFrictionMultiplier(getBody()->GetPosition());
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    b2Vec2 direction = -getParallelVelocity();
    direction.Normalize();
    b2Vec2 forceVec = body->GetMass() * 10 * friction * direction;
    forceVec += 0.1 * friction * -getParallelVelocity();
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
    b2Vec2 forwardDirection = getBody()->GetWorldVector(b2Vec2(0.0, 1.0));
    // Check if the car is moving forwards or backwards using the cosine formula for vectors.
    float cosAngle = b2Dot(moveDirection, forwardDirection) / (moveDirection.Length() * forwardDirection.Length());
    // If the car is moving forwards (cosAngle > 0), apply braking force opposite to move direction.
    if (cosAngle > 0) {
        b2Vec2 direction = -moveDirection;
        direction.Normalize();
        getBody()->ApplyForce(force * direction, getBody()->GetWorldCenter(), true);
    // If the car is moving backwards at less than maximum reverse speed, apply accelerating force
    // opposite to forward direction.
    } else if (getParallelVelocity().Length() < maxRevSpeed) {
        b2Vec2 direction = -forwardDirection;
        direction.Normalize();
        getBody()->ApplyForce(force * direction, getBody()->GetWorldCenter(), true);
    }
}


void Tire::updateMovement(const Level& level) {
    applyFriction(level);
}
