/* This is a test program for the PhysicsObject class.
 * Creates some dynamic physics objects to the screen
 * and a controllable circle for poking them around. */

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include <iostream>

int main(void) {
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    sf::VideoMode videomode = sf::VideoMode(1000,1000);

    Settings s(videomode.width, videomode.height, 50, 50);

    // Create screen borders
    b2BodyDef borderDef;
    b2Body* borderBody = world.CreateBody(&borderDef);
    b2Vec2 vertices[4];
    vertices[0].Set(0.0, 0.0);
    vertices[1].Set(0.0, videomode.height * s.pixelsToMeters);
    vertices[2].Set(videomode.width * s.pixelsToMeters, videomode.height * s.pixelsToMeters);
    vertices[3].Set(videomode.width * s.pixelsToMeters, 0.0);
    b2ChainShape screenBorders;
    screenBorders.CreateLoop(vertices, 4);
    borderBody->CreateFixture(&screenBorders, 1.0);

    // physObj1 should be a green rotated square (using vertex constructor) in the middle of the screen.
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(500 * s.pixelsToMeters, 500 * s.pixelsToMeters);

    b2FixtureDef fixtureDef1;
    fixtureDef1.density = 1.0;
    fixtureDef1.friction = 0.3;

    std::vector<std::pair<float,float>> bodyVertices1 = {
        std::make_pair(1.0, 2.0),
        std::make_pair(0.0, 1.0),
        std::make_pair(1.0, 0.0),
        std::make_pair(2.0, 1.0)
    };

    PhysicsObject physObj1(world, s, bodyVertices1, bodyDef1, fixtureDef1, sf::Color::Green);

    // physObj2 should be a tall red triangle (using vertex constructor) in the top left corner of the screen.
    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(200 * s.pixelsToMeters, 800 * s.pixelsToMeters);

    b2FixtureDef fixtureDef2;
    fixtureDef2.density = 1.0;
    fixtureDef2.friction = 0.3;

    std::vector<std::pair<float,float>> bodyVertices2 = {
        std::make_pair(0.0, 0.0),
        std::make_pair(1.5, 3.0),
        std::make_pair(3.0, 0.0),
    };

    PhysicsObject physObj2(world, s, bodyVertices2, bodyDef2, fixtureDef2, sf::Color::Red);

    // physObj3 should be a heavy blue irregular object (using vertex constructor) in the bottom right corner of the screen.
    b2BodyDef bodyDef3;
    bodyDef3.type = b2_dynamicBody;
    bodyDef3.position.Set(800 * s.pixelsToMeters, 200 * s.pixelsToMeters);

    b2FixtureDef fixtureDef3;
    fixtureDef3.density = 3.0;
    fixtureDef3.friction = 0.3;

    std::vector<std::pair<float,float>> bodyVertices3 = {
        std::make_pair(0.0, 0.0),
        std::make_pair(1.5, -0.5),
        std::make_pair(3.0, 0.5),
        std::make_pair(4.0, 2.5),
        std::make_pair(2.0, 2.5),
        std::make_pair(0.5, 1.5),
    };

    PhysicsObject physObj3(world, s, bodyVertices3, bodyDef3, fixtureDef3, sf::Color::Blue);
    
    // physObj4 should be a lightweight yellow rectangle (using rectangle constructor) in the bottom left corner of the screen.
    b2BodyDef bodyDef4;
    bodyDef4.type = b2_dynamicBody;
    bodyDef4.position.Set(200 * s.pixelsToMeters, 200 * s.pixelsToMeters);

    b2FixtureDef fixtureDef4;
    fixtureDef4.density = 0.2;
    fixtureDef4.friction = 0.3;

    PhysicsObject physObj4(world, s, b2Vec2(4.0, 2.0), bodyDef4, fixtureDef4, sf::Color::Yellow);
    
    // physObj5 should be a white circle (using circle constructor and default color) in the top right corner of the screen.
    b2BodyDef bodyDef5;
    bodyDef5.type = b2_dynamicBody;
    bodyDef5.position.Set(800 * s.pixelsToMeters, 800 * s.pixelsToMeters);

    b2FixtureDef fixtureDef5;
    fixtureDef5.density = 1.0;
    fixtureDef5.friction = 0.3;

    PhysicsObject physObj5(world, s, 1.5, bodyDef5, fixtureDef5);

    // playerObj should be a movable cyan circle (using circle constructor)
    b2BodyDef bodyDefPlayer;
    bodyDefPlayer.type = b2_dynamicBody;
    bodyDefPlayer.position.Set(500 * s.pixelsToMeters, 900 * s.pixelsToMeters);

    b2FixtureDef fixtureDefPlayer;
    fixtureDefPlayer.density = 1.0;
    fixtureDefPlayer.friction = 0.3;

    PhysicsObject playerObj(world, s, 1.5, bodyDefPlayer, fixtureDefPlayer, sf::Color::Cyan);
    
    // Create player for moving the playerObj.
    Player player1;
    KeySettings p1keys = player1.getKeys();
    
    sf::RenderWindow window(videomode, "PhysObjTest");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::I) {
                    std::cout << physObj3.getPosition().x * s.metersToPixels << " " << physObj3.getPosition().y * s.metersToPixels << std::endl;
                    std::cout << physObj3.getWorldCenter().x * s.metersToPixels << " " << physObj3.getWorldCenter(). y * s.metersToPixels << std::endl;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(p1keys.up)) playerObj.applyLinearImpulse(b2Vec2(0.0f, 3.0f), playerObj.getWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.down)) playerObj.applyLinearImpulse(b2Vec2(0.0f, -3.0f), playerObj.getWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.left)) playerObj.applyLinearImpulse(b2Vec2(-3.0f, 0.0f), playerObj.getWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.right)) playerObj.applyLinearImpulse(b2Vec2(3.0f, 0.0f), playerObj.getWorldCenter(), true);

        world.Step(1.0/60.0, 8, 3); 
        window.clear();
        physObj1.drawTo(window, s);
        physObj2.drawTo(window, s);
        physObj3.drawTo(window, s);
        physObj4.drawTo(window, s);
        physObj5.drawTo(window, s);
        playerObj.drawTo(window, s);
        window.display();
    }
    return 0;
}
