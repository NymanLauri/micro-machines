#include "PhysicsObject.hpp"
#include "Settings.hpp"

// Constructor for circle shapes.
PhysicsObject::PhysicsObject(b2World& world, std::shared_ptr<sf::CircleShape> shape, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) :
    shape(shape) {
    //TODO Check that the circle shape is a real circle (not a triangle, for example)
    b2CircleShape bodyShape;
    bodyShape.m_radius = (shape->getRadius() * PIXTOMETERS);
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    shape->setOrigin(shape->getRadius(), shape->getRadius());
    shape->setFillColor(color);
}

// Constructor for rectangle shapes.
PhysicsObject::PhysicsObject(b2World& world, std::shared_ptr<sf::RectangleShape> shape, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) : 
    shape(shape) {
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(shape->getSize().x * 0.5 * PIXTOMETERS, shape->getSize().y * 0.5 * PIXTOMETERS);
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    shape->setOrigin(shape->getSize().x/2, shape->getSize().y/2);
    shape->setFillColor(color);
}

// Constructor for arbitrary convex polygon shapes.
PhysicsObject::PhysicsObject(b2World& world, std::vector<std::pair<int,int>>& vertices, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) {
    // Find the largest y coordinate value from the vertices vector
    // to perform axis conversions between SFML and Box2D.
    const std::pair<int,int> maxYPair = *std::max_element(vertices.cbegin(), vertices.cend(),
        [](const std::pair<int,int> left, const std::pair<int,int> right){
            return left.second < right.second;
        });
    const int maxY = maxYPair.second;
    body = world.CreateBody(&bodyDef);
    // Create vertex vector for the fixture's shape.
    b2Vec2 bodyVertices[vertices.size()];
    // Create the rendered shape object.
    std::shared_ptr<sf::ConvexShape> objectShape = std::make_shared<sf::ConvexShape>(vertices.size());
    // Initialize the body vertex vector and the render shape vertices.
    for (size_t i = 0; i < vertices.size(); i++) {
        const std::pair<int, int> currentPair = vertices.at(i);
        bodyVertices[i].Set(currentPair.first * PIXTOMETERS, (maxY - currentPair.second) * PIXTOMETERS);
        objectShape->setPoint(i, sf::Vector2f(currentPair.first, currentPair.second));
    }
    // Define the physical body's shape using the body vertex vector and tie the shape
    // to the body.
    b2PolygonShape polyShape;
    polyShape.Set(bodyVertices, vertices.size());
    fixtureDef.shape = &polyShape;
    body->CreateFixture(&fixtureDef);
    // Tie the rendered shape to the physical body.
    objectShape->setOrigin(body->GetLocalCenter().x * METERSTOPIX, maxY - body->GetLocalCenter().y * METERSTOPIX);
    objectShape->setFillColor(color);
    shape = objectShape;
}

void PhysicsObject::drawTo(sf::RenderWindow& window) {
    b2Vec2 position = body->GetWorldCenter();
    shape->setRotation(-body->GetAngle() * RADTODEG);
    shape->setPosition(position.x * METERSTOPIX, (-position.y * METERSTOPIX) + window.getSize().y);
    window.draw(*shape);
}

b2Vec2 PhysicsObject::getPosition() const {
    return body->GetPosition();
}

float32 PhysicsObject::getAngle() const {
    return body->GetAngle();
}
