/* This is a test program for the PhysicsObject class.
 * Creates some dynamic physics objects to the screen
 * and a controllable square for poking them around. */

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Player.hpp"

#define PIXTOMETERS (1.0/20.0)
#define METERSTOPIX (20.0/1.0)

int main(void) {
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    sf::VideoMode videomode = sf::VideoMode(1000,1000);

    // Create screen borders
    b2BodyDef borderDef;
    b2Body* borderBody = world.CreateBody(&borderDef);
    b2Vec2 vertices[4];
    vertices[0].Set(0.0, 0.0);
    vertices[1].Set(0.0, videomode.height * PIXTOMETERS);
    vertices[2].Set(videomode.width * PIXTOMETERS, videomode.height * PIXTOMETERS);
    vertices[3].Set(videomode.width * PIXTOMETERS, 0.0);
    b2ChainShape screenBorders;
    screenBorders.CreateLoop(vertices, 4);
    borderBody->CreateFixture(&screenBorders, 1.0);

    // physObj1 should be a green rotated square (using vertex constructor) in the middle of the screen.
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(500 * PIXTOMETERS, 500 * PIXTOMETERS);
    b2Body* body1 = world.CreateBody(&bodyDef1);

    b2FixtureDef fixtureDef1;
    fixtureDef1.density = 1.0;
    fixtureDef1.friction = 0.3;

    std::vector<std::pair<int,int>> bodyVertices1 = {
        std::make_pair(20,40),
        std::make_pair(0,20),
        std::make_pair(20,0),
        std::make_pair(40,20)
    };

    PhysicsObject physObj1(body1, fixtureDef1, bodyVertices1, METERSTOPIX, sf::Color::Green);

    // physObj2 should be a tall red triangle (using vertex constructor) in the top left corner of the screen.
    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(200 * PIXTOMETERS, 800 * PIXTOMETERS);
    b2Body* body2 = world.CreateBody(&bodyDef2);

    b2FixtureDef fixtureDef2;
    fixtureDef2.density = 1.0;
    fixtureDef2.friction = 0.3;

    std::vector<std::pair<int,int>> bodyVertices2 = {
        std::make_pair(0,60),
        std::make_pair(30, 0),
        std::make_pair(60, 60),
    };

    PhysicsObject physObj2(body2, fixtureDef2, bodyVertices2, METERSTOPIX, sf::Color::Red);

    // physObj3 should be a heavy blue irregular object (using vertex constructor) in the bottom right corner of the screen.
    b2BodyDef bodyDef3;
    bodyDef3.type = b2_dynamicBody;
    bodyDef3.position.Set(800 * PIXTOMETERS, 200 * PIXTOMETERS);
    b2Body* body3 = world.CreateBody(&bodyDef3);

    b2FixtureDef fixtureDef3;
    fixtureDef3.density = 3.0;
    fixtureDef3.friction = 0.3;

    std::vector<std::pair<int,int>> bodyVertices3 = {
        std::make_pair(0,0),
        std::make_pair(30, -10),
        std::make_pair(60, 10),
        std::make_pair(80, 50),
        std::make_pair(40, 50),
        std::make_pair(10, 30),
    };

    PhysicsObject physObj3(body3, fixtureDef3, bodyVertices3, METERSTOPIX, sf::Color::Blue);
    
    // physObj4 should be a lightweight yellow rectangle (using rectangle constructor) in the bottom left corner of the screen.
    b2BodyDef bodyDef4;
    bodyDef4.type = b2_dynamicBody;
    bodyDef4.position.Set(200 * PIXTOMETERS, 200 * PIXTOMETERS);
    b2Body* body4 = world.CreateBody(&bodyDef4);

    b2FixtureDef fixtureDef4;
    fixtureDef4.density = 0.2;
    fixtureDef4.friction = 0.3;

    std::shared_ptr<sf::RectangleShape> bodyShape4 = std::make_shared<sf::RectangleShape>(sf::Vector2f(80, 40));

    PhysicsObject physObj4(body4, fixtureDef4, bodyShape4, METERSTOPIX, sf::Color::Yellow);
    
    // physObj5 should be a white circle (using circle constructor and default color) in the top right corner of the screen.
    b2BodyDef bodyDef5;
    bodyDef5.type = b2_dynamicBody;
    bodyDef5.position.Set(800 * PIXTOMETERS, 800 * PIXTOMETERS);
    b2Body* body5 = world.CreateBody(&bodyDef5);

    b2FixtureDef fixtureDef5;
    fixtureDef5.density = 1.0;
    fixtureDef5.friction = 0.3;

    std::shared_ptr<sf::CircleShape> bodyShape5 = std::make_shared<sf::CircleShape>(30);

    PhysicsObject physObj5(body5, fixtureDef5, bodyShape5, METERSTOPIX);

    // playerObj should be a movable cyan circle (using circle constructor)
    b2BodyDef bodyDef6;
    bodyDef6.type = b2_dynamicBody;
    bodyDef6.position.Set(500 * PIXTOMETERS, 900 * PIXTOMETERS);
    b2Body* body6 = world.CreateBody(&bodyDef6);

    b2FixtureDef fixtureDef6;
    fixtureDef6.density = 1.0;
    fixtureDef6.friction = 0.3;

    std::shared_ptr<sf::CircleShape> bodyShape6 = std::make_shared<sf::CircleShape>(30);

    PhysicsObject playerObj(body6, fixtureDef6, bodyShape6, METERSTOPIX, sf::Color::Cyan);

    // Create player for moving the playerObj.
    Player player1;
    KeySettings p1keys = player1.getKeys();

    sf::RenderWindow window(videomode, "PhysObjTest");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(p1keys.up)) body6->ApplyLinearImpulse(b2Vec2(0.00f, 0.01f), body6->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.down)) body6->ApplyLinearImpulse(b2Vec2(0.00f, -0.01f), body6->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.left)) body6->ApplyLinearImpulse(b2Vec2(-0.01f, 0.00f), body6->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.right)) body6->ApplyLinearImpulse(b2Vec2(0.01f, 0.00f), body6->GetWorldCenter(), true);

        world.Step(1.0/60.0, 8, 3); 
        window.clear();
        physObj1.drawTo(window);
        physObj2.drawTo(window);
        physObj3.drawTo(window);
        physObj4.drawTo(window);
        physObj5.drawTo(window);
        playerObj.drawTo(window);
        window.display();
    }
    return 0;
}
