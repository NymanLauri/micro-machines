/* This is a short SFML test file for messing around, not intended to be used in the
 * project.
 * Compiled by typing:
 * g++ -g -Wall -o test sfml_test.cpp -lsfml-graphics -lsfml-window -lsfml-system 
 */

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#define PI 3.14159265

int main() {
    // Context settings are used here to set the antialiasing level.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Create 1000x1000 pixel window titled "SFML test" using above context settings.
    sf::RenderWindow window(sf::VideoMode(1000,1000), "SFML test", sf::Style::Default, settings);
    // Create a "circle of radius 20 with 3 corners", i.e., a triangle shape.
    sf::CircleShape shape(20.f, 3);
    // Transfer the origin of the triangle (the point around which the triangle rotates)
    // to the center of the triangle. (The default would be the top left corner of the shape.)
    shape.setOrigin(shape.getRadius(),shape.getRadius());
    // Move the triangle to the center coordinates of the window.
    shape.setPosition(500,500);
    shape.setFillColor(sf::Color::Green);

    // Initialize a clock for measuring fps.
    sf::Clock clock;
    float fps;

    // Main program loop.
    while (window.isOpen()) {
        fps = 1.0/clock.getElapsedTime().asSeconds();
        clock.restart();
        // sf::Event holds information about every event (a key press, mouse movement etc.)
        // which occurs during the program loop.
        sf::Event event;
        // Event loop handles all events which have occurred.
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Key presses are handled here, excluding movement keys (see below).    
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::I:
                            // Print information to console for debugging purposes when I is pressed.
                            std::cout << "fps: " << fps << std::endl;
                            std::cout << "rot: " << shape.getRotation() << std::endl;
                            std::cout << "x: " << shape.getPosition().x << ", y: " << shape.getPosition().y << std::endl;
                        default:
                            // Empty default case included to stop compiler from giving warnings.
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        // Because of reasons explained in the SFML documentation ("smooth motion"), movement
        // keys are handled in the main program loop instead of the event loop, by checking
        // which keys are pressed at any given moment. The new position of the triangle is
        // calculated using sine and cosine from the cmath header.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            // Only allow rotations when up or down is pressed at the same time, since a
            // car can only turn when it is moving.
            shape.move(sin(shape.getRotation()*PI/180),-cos(shape.getRotation()*PI/180));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.rotate(-0.5);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.rotate(0.5);
        }   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { 
            shape.move(-0.5*sin(shape.getRotation()*PI/180),0.5*cos(shape.getRotation()*PI/180));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.rotate(-0.5);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.rotate(0.5);
        }
        // Clear previously displayed window, draw the new position of the triangle to
        // the window and display the newly drawn window.
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
