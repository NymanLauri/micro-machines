#include "PhysicsObject.hpp"
#include "Settings.hpp"

// Constructor for circle shapes.
PhysicsObject::PhysicsObject(b2World& world, float32 radius, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) {
    shape = std::make_shared<sf::CircleShape>(radius * METERSTOPIX);
    shape->setFillColor(color);
    shape->setOrigin(radius * METERSTOPIX, radius * METERSTOPIX);
    b2CircleShape bodyShape;
    bodyShape.m_radius = radius;
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

// Constructor for rectangle shapes.
PhysicsObject::PhysicsObject(b2World& world, b2Vec2 rectDims, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) {
    shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(rectDims.x * METERSTOPIX, rectDims.y * METERSTOPIX));
    shape->setFillColor(color);
    shape->setOrigin(0.5 * rectDims.x * METERSTOPIX, 0.5 * rectDims.y * METERSTOPIX);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(0.5 * rectDims.x, 0.5 * rectDims.y);
    fixtureDef.shape = &bodyShape;
    body = world.CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

// Constructor for arbitrary convex polygon shapes.
PhysicsObject::PhysicsObject(b2World& world, std::vector<std::pair<float,float>>& vertices, b2BodyDef bodyDef, b2FixtureDef fixtureDef, sf::Color color) {
    auto tempShape = std::make_shared<sf::ConvexShape>(vertices.size());
    // Find the largest y coordinate value from the vertices vector
    // to perform axis conversions between SFML and Box2D.
    const std::pair<float,float> maxYPair = *std::max_element(vertices.cbegin(), vertices.cend(),
        [](const std::pair<float,float> left, const std::pair<float,float> right){
            return left.second < right.second;
        });
    const float maxY = maxYPair.second;
    body = world.CreateBody(&bodyDef);
    // Create vertex vector for the fixture's shape.
    b2Vec2 bodyVertices[vertices.size()];
    // Create the rendered shape object.
    for (size_t i = 0; i < vertices.size(); i++) {
        const std::pair<float, float> currentPair = vertices.at(i);
        bodyVertices[i].Set(currentPair.first, currentPair.second);
        tempShape->setPoint(i, sf::Vector2f(currentPair.first * METERSTOPIX, (maxY - currentPair.second) * METERSTOPIX));
    }
    // Define the physical body's shape using the body vertex vector and tie the shape
    // to the body.
    b2PolygonShape bodyShape;
    bodyShape.Set(bodyVertices, vertices.size());
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);
    // Tie the rendered shape to the physical body.
    tempShape->setOrigin(body->GetLocalCenter().x * METERSTOPIX, (maxY - body->GetLocalCenter().y) * METERSTOPIX);
    tempShape->setFillColor(color);
    shape = tempShape;
    // Move the body so that the center of mass is at the given bodyDef coordinates,
    // instead of the origin of the body (which is one of the vertices).
    b2Vec2 transformCoordinates = -body->GetLocalCenter();
    transformCoordinates += body->GetPosition();
    body->SetTransform(transformCoordinates, body->GetAngle());
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

b2Vec2 PhysicsObject::getWorldCenter() const {
    return body->GetWorldCenter();
}

float32 PhysicsObject::getAngle() const {
    return body->GetAngle();
}

void PhysicsObject::applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake) {
    body->ApplyLinearImpulse(impulse, point, wake);
}
