#include <iostream>
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "PhysicsObject.hpp"
#include <cmath>
#include "Player.hpp"

#define PIXTOMETERS (1.0/20.0)
#define METERSTOPIX (20.0/1.0)
// Compile: g++ -g -Wall -std=c++11 -o test PhysObjTest.cpp PhysicsObject.cpp -lBox2D -IBox2D -L. -lsfml-graphics -lsfml-window -lsfml-system
int main(void) {
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    sf::VideoMode videomode = sf::VideoMode(1000,1000);//sf::VideoMode::getDesktopMode();
    
    double boxWidth = 40.0 * PIXTOMETERS;
    double boxHeight = 40.0 * PIXTOMETERS;
    b2BodyDef shapeDef;
    shapeDef.type = b2_dynamicBody;
    shapeDef.position.Set(videomode.width/2 * PIXTOMETERS, (videomode.height-100) * PIXTOMETERS);
    b2Body* shapeBody = world.CreateBody(&shapeDef);
    b2PolygonShape box;
    box.SetAsBox(boxWidth/2.0, boxHeight/2.0);
    b2FixtureDef fixDef;
    fixDef.shape = &box;
    fixDef.density = 1.0;
    fixDef.friction = 0.3;
    shapeBody->CreateFixture(&fixDef);

    //Create car body
    b2BodyDef carBodyDef;
    carBodyDef.type = b2_dynamicBody;
    carBodyDef.position.Set(200*PIXTOMETERS,200*PIXTOMETERS);
    b2Body* carBody = world.CreateBody(&carBodyDef);
    
    /*b2PolygonShape carBox;
    carBox.SetAsBox(20*PIXTOMETERS, 20*PIXTOMETERS);*/
    b2FixtureDef carFixtureDef;
    carFixtureDef.density = 1.0;
    carFixtureDef.friction = 0.3;
    //carFixtureDef.shape = &carBox;
    //carBody->CreateFixture(&carFixtureDef);

    /*
    b2CircleShape circle;
    circle.m_p.Set(20*PIXTOMETERS, 40*PIXTOMETERS);
    circle.m_radius = 20.0 * PIXTOMETERS;
    carFixtureDef.shape = &circle;
    carBody->CreateFixture(&carFixtureDef);
    */
    //std::cout << carBodyDef.position.x << " " << carBodyDef.position.y << std::endl;
    
    b2Vec2 carV[5];
    carV[0].Set(0, 0);
    carV[1].Set(0, 40*PIXTOMETERS);
    carV[2].Set(20*PIXTOMETERS, 60*PIXTOMETERS);
    carV[3].Set(40*PIXTOMETERS, 40*PIXTOMETERS);
    carV[4].Set(40*PIXTOMETERS, 0*PIXTOMETERS);
    b2PolygonShape cs;
    cs.Set(carV, 5);
    carFixtureDef.shape = &cs;
    carBody->CreateFixture(&carFixtureDef);

    sf::ConvexShape carBodyTexture;
    carBodyTexture.setPointCount(5);
    carBodyTexture.setPoint(0, sf::Vector2f(0,60));
    carBodyTexture.setPoint(1, sf::Vector2f(0,20));
    carBodyTexture.setPoint(2, sf::Vector2f(20,0));
    carBodyTexture.setPoint(3, sf::Vector2f(40,20));
    carBodyTexture.setPoint(4, sf::Vector2f(40,60));
    //std::cout << carBodyTexture.getOrigin().x << " " << carBodyTexture.getOrigin().y << std::endl;
    carBodyTexture.setOrigin(carBody->GetLocalCenter().x * METERSTOPIX, 60 - carBody->GetLocalCenter().y * METERSTOPIX);

    PhysicsObject carObj(carBody, carBodyTexture, METERSTOPIX);
    std::cout << carBody->GetLocalCenter().x * METERSTOPIX << " " << carBody->GetLocalCenter().y * METERSTOPIX << std::endl;

    /*b2EdgeShape edge;
    edge.Set(b2Vec2(videomode.width * PIXTOMETERS, 0.0 * PIXTOMETERS),b2Vec2(videomode.width * PIXTOMETERS, videomode.height * PIXTOMETERS));
    b2BodyDef edgeBodyDef;
    b2Body* edgeBody = world.CreateBody(&edgeBodyDef);
    fixDef.shape = &edge;
    edgeBody->CreateFixture(&fixDef);
    std::cout << edgeBody->GetPosition().x << " " << edgeBody->GetPosition().y << std::endl;*/
    
    // Create chain shape for screen borders
    b2BodyDef borderDef;
    b2Body* borderBody = world.CreateBody(&borderDef);
    b2Vec2 vertices[4];
    vertices[0].Set(0.0, 0.0);
    vertices[1].Set(0.0, videomode.height * PIXTOMETERS);
    vertices[2].Set(videomode.width * PIXTOMETERS, videomode.height * PIXTOMETERS);
    vertices[3].Set(videomode.width * PIXTOMETERS, 0.0);
    b2ChainShape screenBorders; screenBorders.CreateLoop(vertices, 4);
    borderBody->CreateFixture(&screenBorders, 1.0);

    sf::RectangleShape shape(sf::Vector2f(40.0f, 40.0f));
    shape.setOrigin(20.0f, 20.0f);
    shape.setFillColor(sf::Color::Green);

    PhysicsObject obj(shapeBody, shape, METERSTOPIX);
    Player player;

    KeySettings p2keys = {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right};
    Player player2(p2keys);

    b2BodyDef shape2Def;
    shape2Def.type = b2_dynamicBody;
    shape2Def.position.Set(videomode.width/2 * PIXTOMETERS, (videomode.height) * PIXTOMETERS);
    b2Body* shape2Body = world.CreateBody(&shape2Def);
    b2PolygonShape box2;
    box2.SetAsBox(boxWidth/2.0, boxHeight/2.0);
    shape2Body->CreateFixture(&fixDef);

    sf::RectangleShape shape2(sf::Vector2f(40.0f, 40.0f));
    shape2.setOrigin(20.0f, 20.0f);
    shape2.setFillColor(sf::Color::Red);

    PhysicsObject obj2(shape2Body, shape2, METERSTOPIX);

    
    sf::RenderWindow window(videomode, "PhysObjTest"/*, sf::Style::Fullscreen*/);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::I) {
                    //std::cout << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
                    //std::cout << shapeBody->GetPosition().x * METERSTOPIX << " " << videomode.height + (-shapeBody->GetPosition().y * METERSTOPIX) << std::endl;
                    //std::cout << carObj.getPosition().x << " " << carObj.getPosition().y << std::endl;
                    //std::cout << carObj.getPosition().x * METERSTOPIX << " " << videomode.height + (-carObj.getPosition().y * METERSTOPIX) << std::endl;
                    //std::cout << carBodyTexture.getPosition().x << " " << carBodyTexture.getPosition().y << std::endl;
                    std::cout << carBodyTexture.getRotation() << std::endl;
                    std::cout << carBody->GetAngle() * 180/3.14159265 << std::endl;
                }
            }
        }

        //float32 angle = obj.getAngle();
        KeySettings p1keys = player.getKeys();
	//if (sf::Keyboard::isKeyPressed(p1keys.up)) shapeBody->ApplyLinearImpulse(b2Vec2(sin(angle) * 0.01f, cos(angle) * 0.01f), shapeBody->GetWorldCenter(), true);
        //if (sf::Keyboard::isKeyPressed(p1keys.down)) shapeBody->ApplyLinearImpulse(b2Vec2(sin(angle) * -0.01f, cos(angle) * -0.01f), shapeBody->GetWorldCenter(), true);
        //if (sf::Keyboard::isKeyPressed(p1keys.left)) shapeBody->ApplyTorque(-0.05f, true);
        //if (sf::Keyboard::isKeyPressed(p1keys.right)) shapeBody->ApplyTorque(0.05f, true);
        if (sf::Keyboard::isKeyPressed(p1keys.up)) shapeBody->ApplyLinearImpulse(b2Vec2(0.00f, 0.01f), shapeBody->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.down)) shapeBody->ApplyLinearImpulse(b2Vec2(0.00f, -0.01f), shapeBody->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.left)) shapeBody->ApplyLinearImpulse(b2Vec2(-0.01f, 0.00f), shapeBody->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p1keys.right)) shapeBody->ApplyLinearImpulse(b2Vec2(0.01f, 0.00f), shapeBody->GetWorldCenter(), true);

        float32 angle2 = carObj.getAngle();
        if (sf::Keyboard::isKeyPressed(p2keys.up)) carBody->ApplyLinearImpulse(b2Vec2(sin(angle2) * -0.005f, cos(angle2) * 0.005f), carBody->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p2keys.down)) carBody->ApplyLinearImpulse(b2Vec2(sin(angle2) * 0.005f, cos(angle2) * -0.005f), carBody->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(p2keys.left)) carBody->ApplyTorque(0.05f, true);
        if (sf::Keyboard::isKeyPressed(p2keys.right)) carBody->ApplyTorque(-0.05f, true);

        world.Step(1.0/60.0, 8, 3); 
        window.clear();
        obj.drawTo(window);
        obj2.drawTo(window);
        carObj.drawTo(window);
        window.display();
    }
    return 0;
}
