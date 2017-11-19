#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>

// This class could inherit from sf::Shape to allow window.draw(object)
// syntax rather than object.draw(window). Possible TODO
class PhysicsObject /*: sf::Shape */ {
    public:
        PhysicsObject(b2Body* body, sf::Shape& shape, double scaling) : body(body), shape(shape), scaling(scaling) { }
        b2Vec2 getPosition() const;
        float32 getAngle() const;
        void drawTo(sf::RenderWindow& window);
        //void updateShapeLocation()
        //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        b2Body* body;
        sf::Shape& shape;
        double scaling;
};
