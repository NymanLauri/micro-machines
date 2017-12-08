/* PhysicsObject ties a physical Box2D body to a shape rendered using SFML.
 * The purpose of the class is to allow easy drawing of Box2D bodies.
 * PhysicsObject constructor requires the following arguments:
 *      - world is a reference to the b2World into which the object will be added
 *      - settings is a reference to the scale settings defined at the start of the program
 *      - one of the following parameters describing the shape of the object (all distances are in meters):
 *          - a single float argument creates a circle of the given radius
 *          - a b2Vec2 argument creates a rectangle using the dimensions given in the b2Vec2-vector
 *          - a std::vector<std::pair<float,float>> creates an arbitrary convex polygon shape
 *            whose vertex coordinates are the pairs given in the vector (assumes that the coordinates
 *            in the vector are vertices of a convex polygon and that the coordinates are given in clockwise
 *            or counter-clockwise order).
 * and takes the following optional arguments:
 *      - a b2BodyDef for the body (uses the default b2BodyDef if no def is given)
 *      - a b2FixtureDef for the fixture created on the body (uses the default b2FixtureDef
 *        if none is given, and ignores any existing shape-values of the def)
 *      - an sf::Color for the SFML shape (defaults to white)
 */

#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Settings.hpp"

class PhysicsObject {
    public:
        // The different constructors for circle, rectangle and convex polygon shaped objects.
        PhysicsObject(b2World& world, const Settings& s, float32 radius, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        PhysicsObject(b2World& world, const Settings& s, b2Vec2 rectDims, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        PhysicsObject(b2World& world, const Settings& s, std::vector<std::pair<float,float>>& vertices, b2BodyDef bodyDef = b2BodyDef(), b2FixtureDef fixtureDef = b2FixtureDef(), sf::Color color = sf::Color::White);
        // The body of the object can be accessed and modified, but the pointer cannot be changed to another body.
        b2Body* const getBody() const;
        // Some (possibly temporary) methods for easier access to the properties of the body.
        b2Vec2 getPosition() const; // Returns the origin of the body.
        b2Vec2 getWorldCenter() const; // Returns the coordinates of the body's center of mass.
        float32 getAngle() const;
        void applyLinearImpulse(b2Vec2 impulse, b2Vec2 point, bool wake);
        // The method for easy drawing of the Box2D object; automatically calculates the correct
        // position of the SFML-shape before drawing.
        void drawTo(sf::RenderWindow& window);
    private:
        b2Body* body;
        std::shared_ptr<sf::Shape> shape;
        const Settings& s;
};

#endif
