/* PhysicsObject ties a physical Box2D body to a shape rendered using SFML.
 * The purpose of the class is to allow easy drawing of Box2D bodies.
 * PhysicsObjects are constructed using an existing b2Body,
 * a b2FixtureDef and a drawable SFML shape. The constructor assigns a Box2D shape
 * (which matches the drawable SFML shape) to the given b2FixtureDef, and creates the
 * new fixture on the body.
 * The SFML shape can be given as a shared pointer to an existing RectangleShape or CircleShape, 
 * or as a vector of the vertices of the desired shape, in which case the constructor 
 * will create a new sf::ConvexShape from it.
 * Optionally, a color for the shape can be given (defaults to white). */

#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

class PhysicsObject {
    public:
        PhysicsObject(b2World& world, float32 radius, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        PhysicsObject(b2World& world, b2Vec2 rectDims, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        PhysicsObject(b2World& world, std::vector<std::pair<float,float>>& vertices, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        b2Body* const getBody() const;
        b2Vec2 getPosition() const;
        b2Vec2 getWorldCenter() const;
        float32 getAngle() const;
        void applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake);
        void drawTo(sf::RenderWindow& window);
    private:
        b2Body* body;
        std::shared_ptr<sf::Shape> shape;
};

#endif
