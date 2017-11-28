/* This is a test program for the PhysicsObject class.
 * Creates some dynamic physics objects to the screen
 * and a controllable circle for poking them around. */

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Box2D/Box2D.h"
#include "Car.hpp"
#include "Player.hpp"
#include "Settings.hpp"

int main(void) {
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    sf::VideoMode videomode = sf::VideoMode(1800,1000);
    
    Settings s(videomode.width, //screenWidth
               videomode.height, //screenHeight
               180.0,            //worldWidth
               90.0);           //worldHeight

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

    // Create two cars in the middle of the screen
    Car car1(world, s, b2Vec2((videomode.width/2 - 50)* s.pixelsToMeters, videomode.height/2 * s.pixelsToMeters), sf::Color::Red);
    Car car2(world, s, b2Vec2((videomode.width/2 + 50) * s.pixelsToMeters, videomode.height/2 * s.pixelsToMeters), sf::Color::Blue);

    // Create player for moving the car.
    Player player1(KeySettings{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D});
    Player player2(KeySettings{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right});
    KeySettings p1keys = player1.getKeys();
    KeySettings p2keys = player2.getKeys();

    sf::RenderWindow window(videomode, "CarTest");
    // At the moment changing the framerate limit will break the physics.
    window.setFramerateLimit(60);
    float timeStep = 1.0/60.0;

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

        if (sf::Keyboard::isKeyPressed(p1keys.up)) car1.accelerate();
        if (sf::Keyboard::isKeyPressed(p1keys.down)) car1.decelerate();
        if (sf::Keyboard::isKeyPressed(p1keys.left)) car1.turnLeft();
        if (sf::Keyboard::isKeyPressed(p1keys.right)) car1.turnRight();
        car1.updateMovement(); // This handles friction and resetting wheel angles.
        if (sf::Keyboard::isKeyPressed(p2keys.up)) car2.accelerate();
        if (sf::Keyboard::isKeyPressed(p2keys.down)) car2.decelerate();
        if (sf::Keyboard::isKeyPressed(p2keys.left)) car2.turnLeft();
        if (sf::Keyboard::isKeyPressed(p2keys.right)) car2.turnRight();
        car2.updateMovement();
  
        world.Step(timeStep, 8, 3); 
        window.clear(sf::Color(170, 170, 170, 255));
        car1.drawTo(window, s);
        car2.drawTo(window, s);
        window.display();
    }
    return 0;
}
