#include "PhysicsObject.hpp"
#include "Settings.hpp"
#include "Constants.hpp"
#include <iostream>

// Constructor for circle shapes.
PhysicsObject::PhysicsObject(b2World& world, const Settings& s, float32 radius, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) : s(s) {
    shape = std::make_shared<sf::CircleShape>(radius * s.metersToPixels);
    shape->setFillColor(color);
    shape->setOrigin(radius * s.metersToPixels, radius * s.metersToPixels);
    b2CircleShape bodyShape;
    bodyShape.m_radius = radius;
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

// Constructor for rectangle shapes.
PhysicsObject::PhysicsObject(b2World& world, const Settings& s, b2Vec2 rectDims, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) : s(s) {
    shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectDims.x * s.metersToPixels, rectDims.y * s.metersToPixels));
    shape->setFillColor(color);
    shape->setOrigin(0.5 * rectDims.x * s.metersToPixels, 0.5 * rectDims.y * s.metersToPixels);
    b2PolygonShape bodyShape;
    // Dimensios multiplied by 0.5 because the rectangle created by SetAsBox has double the side
    // lengths given as arguments.
    bodyShape.SetAsBox(0.5 * rectDims.x, 0.5 * rectDims.y);
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

// Constructor for arbitrary convex polygon shapes.
PhysicsObject::PhysicsObject(b2World& world, const Settings& s, std::vector<std::pair<float,float>>& vertices, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) : s(s) {
    // Create the SFML shape for the body.
    auto tempShape = std::make_shared<sf::ConvexShape>(vertices.size());
    // Create vertex vector for the Box2D body's shape.
    b2Vec2 bodyVertices[vertices.size()];
    // Find the largest y coordinate value from the vertices vector to perform axis conversions between SFML and Box2D.
    // (The y-coordinates have to be "flipped" for the SFML-shape because of the different y-axis directions.)
    const std::pair<float,float> maxYPair = *std::max_element(vertices.cbegin(), vertices.cend(),
        [](const std::pair<float,float> left, const std::pair<float,float> right){
            return left.second < right.second;
        });
    const float maxY = maxYPair.second;
    // Create the Box2D body for the PhysicsObject.
    body = world.CreateBody(&bodyDef);
    for (size_t i = 0; i < vertices.size(); i++) {
        const std::pair<float, float> currentPair = vertices.at(i);
        // Set the vertices of the Box2D body's shape.
        bodyVertices[i].Set(currentPair.first, currentPair.second);
        // Set the vertices of the SFML shape, converting meters to pixels and flipping the y-axis.
        tempShape->setPoint(i, sf::Vector2f(currentPair.first * s.metersToPixels, (maxY - currentPair.second) * s.metersToPixels));
    }
    // Create the Box2D shape object from the vertex vector and assign the shape to the fixtureDef.
    b2PolygonShape bodyShape;
    bodyShape.Set(bodyVertices, vertices.size());
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);
    // Set the origin of the SFML shape to the center of the mass of the Box2D body.
    tempShape->setOrigin(body->GetLocalCenter().x * s.metersToPixels, (maxY - body->GetLocalCenter().y) * s.metersToPixels);
    tempShape->setFillColor(color);
    shape = tempShape;
    // Move the Box2D body so that the center of mass is at the given bodyDef coordinates,
    // instead of the origin of the body (which is one of the vertices).
    b2Vec2 transformCoordinates = -body->GetLocalCenter();
    transformCoordinates += body->GetPosition();
    body->SetTransform(transformCoordinates, body->GetAngle());
}

// Calculate and set the correct position and rotation of the SFML shape and draw it.
void PhysicsObject::drawTo(sf::RenderWindow& window) {
    b2Vec2 position = body->GetWorldCenter();
    shape->setRotation(-body->GetAngle() * RADTODEG);
    shape->setPosition(position.x * s.metersToPixels, (-position.y * s.metersToPixels) + window.getSize().y);
    window.draw(*shape);
}

b2Body* const PhysicsObject::getBody() const {
    return body;
}

b2Vec2 PhysicsObject::getPosition() const {
    return body->GetPosition();
}

b2Vec2 PhysicsObject::getWorldCenter() const {
    return body->GetWorldCenter();
}

float32 PhysicsObject::getAngle() const {
    return body->GetAngle();
}

void PhysicsObject::applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake) {
    body->ApplyLinearImpulse(impulse, point, wake);
}
