/* This is a test program for the PhysicsObject class.
 * Creates some dynamic physics objects to the screen
 * and a controllable circle for poking them around. */

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "Car.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include <iostream>

int main(void) {
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);
    
    sf::VideoMode videomode = sf::VideoMode(1800,1000);

    Settings s(videomode.width, videomode.height, 180, 100);

    Level level("map1.txt", world, s);
    level.createScreenBorders(world);

    auto car1 = std::make_shared<Car>(world, s, level, b2Vec2(0.12*s.worldWidth, 0.5*s.worldHeight), sf::Color::Red);
    level.addCar(car1);
    
    Player player;
    KeySettings keys = player.getKeys();
    
    float timeStep = 1.0/60.0;

    sf::RenderWindow window(videomode, "LevelTest");
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
                    std::cout << car1->getPosition().x << " " << car1->getPosition().y << std::endl;
                    std::cout << level.getFrictionMultiplier(car1->getPosition()) << std::endl;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(keys.up)) car1->accelerate();
        if (sf::Keyboard::isKeyPressed(keys.down)) car1->decelerate();
        if (sf::Keyboard::isKeyPressed(keys.left)) car1->turnLeft();
        if (sf::Keyboard::isKeyPressed(keys.right)) car1->turnRight();
        car1->updateMovement();
        world.Step(timeStep, 8, 3);
        window.clear();
        level.drawTo(window);
        window.display();
    }
    return 0;
}
