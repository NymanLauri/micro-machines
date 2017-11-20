#include "PhysicsObject.hpp"
#define RADTODEG (180.0/3.14159265358979)

// Constructor for circle shapes.
PhysicsObject::PhysicsObject(b2Body* b, b2FixtureDef fixtureDef, std::shared_ptr<sf::CircleShape> shape, const double scaling, sf::Color color) : 
    body(b), shape(shape), scaling(scaling) {
    //TODO Check that the circle shape is a real circle (not a triangle, for example)
    b2CircleShape bodyShape;
    bodyShape.m_radius = (shape->getRadius() * 1.0/scaling);
    fixtureDef.shape = &bodyShape;
    b->CreateFixture(&fixtureDef);
    shape->setOrigin(shape->getRadius(), shape->getRadius());
    shape->setFillColor(color);
}

// Constructor for rectangle shapes.
PhysicsObject::PhysicsObject(b2Body* b, b2FixtureDef fixtureDef, std::shared_ptr<sf::RectangleShape> shape, const double scaling, sf::Color color) : 
    body(b), shape(shape), scaling(scaling) {
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(shape->getSize().x * 0.5 * 1.0/scaling, shape->getSize().y * 0.5 * 1.0/scaling);
    fixtureDef.shape = &bodyShape;
    b->CreateFixture(&fixtureDef);
    shape->setOrigin(shape->getSize().x/2, shape->getSize().y/2);
    shape->setFillColor(color);
}

// Constructor for arbitrary convex polygon shapes.
PhysicsObject::PhysicsObject(b2Body* b, b2FixtureDef fixtureDef, std::vector<std::pair<int,int>>& vertices, const double scaling, sf::Color color) :
    body(b), scaling(scaling) {
    // Find the largest y coordinate value from the vertices vector
    // to perform axis conversions between SFML and Box2D.
    const std::pair<int,int> maxYPair = *std::max_element(vertices.cbegin(), vertices.cend(),
        [](const std::pair<int,int> left, const std::pair<int,int> right){
            return left.second < right.second;
        });
    const int maxY = maxYPair.second;
    // Create vertex vector for the fixture's shape.
    b2Vec2 bodyVertices[vertices.size()];
    // Create the rendered shape object.
    std::shared_ptr<sf::ConvexShape> objectShape = std::make_shared<sf::ConvexShape>(vertices.size());
    // Initialize the body vertex vector and the render shape vertices.
    for (size_t i = 0; i < vertices.size(); i++) {
        const std::pair<int, int> currentPair = vertices.at(i);
        bodyVertices[i].Set(currentPair.first * 1.0/scaling, (maxY - currentPair.second) * 1.0/scaling);
        objectShape->setPoint(i, sf::Vector2f(currentPair.first, currentPair.second));
    }
    // Define the physical body's shape using the body vertex vector and tie the shape
    // to the body.
    b2PolygonShape polyShape;
    polyShape.Set(bodyVertices, vertices.size());
    fixtureDef.shape = &polyShape;
    b->CreateFixture(&fixtureDef);
    // Tie the rendered shape to the physical body.
    objectShape->setOrigin(b->GetLocalCenter().x * scaling, maxY - b->GetLocalCenter().y * scaling);
    objectShape->setFillColor(color);
    shape = objectShape;
}

void PhysicsObject::drawTo(sf::RenderWindow& window) {
    b2Vec2 position = body->GetWorldCenter();
    shape->setRotation(-body->GetAngle() * RADTODEG);
    shape->setPosition(position.x * scaling, (-position.y * scaling) + window.getSize().y);
    window.draw(*shape);
}

b2Vec2 PhysicsObject::getPosition() const {
    return body->GetPosition();
}

float32 PhysicsObject::getAngle() const {
    return body->GetAngle();
}
