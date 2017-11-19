#include "PhysicsObject.hpp"
#define RADTODEG (180.0/3.14159265358979)

void PhysicsObject::drawTo(sf::RenderWindow& window) {
    b2Vec2 position = body->GetWorldCenter();
    shape.setRotation(-body->GetAngle() * RADTODEG);
    shape.setPosition(position.x * scaling, (-position.y * scaling) + window.getSize().y);
    window.draw(shape);
}

b2Vec2 PhysicsObject::getPosition() const {
    return body->GetPosition();
}

float32 PhysicsObject::getAngle() const {
    return body->GetAngle();
}
