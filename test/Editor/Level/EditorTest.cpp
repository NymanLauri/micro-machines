/* Loading from a file added to the beginning of the code. */

/* This is a test program for the PhysicsObject class.
 * Creates some dynamic physics objects to the screen
 * and a controllable circle for poking them around. */

#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>
#include <iostream>
#include "Level.hpp"
#include "fstream"
#include "Car.hpp"
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include <string> 
#include <memory>

#define WIDTH 1800
#define HEIGHT 1000


int main(void) {

  //The width and height in 10x10 tiles
  //int x = WIDTH/10;
  //int y = HEIGHT/10;

  b2Vec2 gravity(0.0f, 0.0f);
  b2World world(gravity);
  unsigned int currentLap;
  sf::VideoMode videomode = sf::VideoMode(WIDTH,HEIGHT);

  Settings s(videomode.width, videomode.height, 180, 100);

  
  //Download level from a file
  std::string levelfile = "level1.txt";
  Level l(levelfile, world, s);
  //std::vector<b2Vec2> checkpointVector;

  // Create screen borders
  l.createScreenBorders(world, s);
  
  /*
  std::list<PhysicsObject> objects;
  std::vector<b2Vec2> checkpointVector;

  //Create map tiles
  sf::RectangleShape tiles[y][x];
  for(int i = 0; i < y; i++) {
    for(int j = 0; j < x; j++) {
      sf::RectangleShape rectangle(sf::Vector2f(10, 10));	
      rectangle.setPosition(j*10, i*10);
		
      //Parameters for the physics engine could be determined here
      switch( A[i][j] ){
      case 0: {
	rectangle.setFillColor(sf::Color::Black);
	break;	
      }
      case 1: {
	rectangle.setFillColor(sf::Color::Green);
	break;
      }
      case 2: {
	rectangle.setFillColor(sf::Color::White);
	break;
      }
      case 3:{
	rectangle.setFillColor(sf::Color::Blue);
	break;
      }
      case 9: {
	rectangle.setFillColor(sf::Color::Yellow);
	//Checkpoint vector in meters.
	b2Vec2 checkPointlocation((j+0.5)*10.0*s.pixelsToMeters, (HEIGHT - (i+0.5)*10.0)*s.pixelsToMeters);
	checkpointVector.push_back(checkPointlocation);
	break;
      }
      case 10: {
	rectangle.setFillColor(sf::Color(200,200,200,200));
				
	//For creating static objects
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(j*10.0*s.pixelsToMeters, (HEIGHT - (i+1)*10.0)*s.pixelsToMeters); //Mirror image with respect to x-axis. Not the best implementation, but works
	myBodyDef.angle = 0;

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.density = 0;
	boxFixtureDef.friction = 0.3;
				
	std::vector<std::pair<float,float>> bodyVertices1 = {
	  std::make_pair(10.0 * s.pixelsToMeters, 10.0 * s.pixelsToMeters),
	  std::make_pair(10.0 * s.pixelsToMeters, 0.0),
	  std::make_pair(0.0, 0.0),
	  std::make_pair(0.0, 10.0 * s.pixelsToMeters)
	};
				
	PhysicsObject physObj(world, bodyVertices1, myBodyDef, boxFixtureDef, sf::Color(200,200,200,200));
				
	objects.push_back(physObj);
	
	//sprite.setScale(10/sprite.getLocalBounds().width, 10/sprite.getLocalBounds().height);

	break;
      }
      default: {
	rectangle.setFillColor(sf::Color::Black);
      }
      }
      tiles[i][j] = rectangle;
    }
  }
*/
  // Order the second half of the route's checkpoints. E.g. 
  // 0 1  -> 0 1
  // 2 3     3 2
  //std::reverse(checkpointVector.begin() + checkpointVector.size()/2, checkpointVector.end());

  //Finding out what material the body is located at 
  //b2Vec2 pos = dynamicBody->GetPosition();
  //int x = floor(pos.x/10);
  //int y = floor(pos.y/10);
  //int material = mat[x][y];
	  

  auto car1 = std::make_shared<Car>(world, s, b2Vec2((videomode.width/17)* s.pixelsToMeters, videomode.height/2 * s.pixelsToMeters), sf::Color::Red);
  auto car2 = std::make_shared<Car>(world, s, b2Vec2((videomode.width/17)* s.pixelsToMeters, videomode.height/3 * s.pixelsToMeters), sf::Color::Blue);
  l.addCar(car1);
  l.addCar(car2);
  Player player1(KeySettings{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D});
  Player player2(KeySettings{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right});
  KeySettings p1keys = player1.getKeys();
  KeySettings p2keys = player2.getKeys();
      
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
	}
      }
    }

    /*
    for(auto it : checkpointVector){
      if(b2Distance(car1->getPosition(), it) < 10.0){
	car1->addCheckpoint(std::find(checkpointVector.begin(), checkpointVector.end(), it) - checkpointVector.begin(), checkpointVector.size());
      }
      if(b2Distance(car2->getPosition(), it) < 10.0){
	car2->addCheckpoint(std::find(checkpointVector.begin(), checkpointVector.end(), it) - checkpointVector.begin(), checkpointVector.size());
      }
    }
    */
    if (sf::Keyboard::isKeyPressed(p1keys.up)) car1->accelerate();
    if (sf::Keyboard::isKeyPressed(p1keys.down)) car1->decelerate();
    if (sf::Keyboard::isKeyPressed(p1keys.left)) car1->turnLeft();
    if (sf::Keyboard::isKeyPressed(p1keys.right)) car1->turnRight();
    car1->updateMovement(l);
    if (sf::Keyboard::isKeyPressed(p2keys.up)) car2->accelerate();
    if (sf::Keyboard::isKeyPressed(p2keys.down)) car2->decelerate();
    if (sf::Keyboard::isKeyPressed(p2keys.left)) car2->turnLeft();
    if (sf::Keyboard::isKeyPressed(p2keys.right)) car2->turnRight();
    car2->updateMovement(l);

    world.Step(1.0/60.0, 8, 3); 
    window.clear();

    currentLap = std::max(car1->getLap(), car2->getLap());
    
    std::cout << currentLap << std::endl;
    // std::cout << car1.getPosition().x << " " << car1.getPosition().y << std::endl;
    
    
    //for (auto i: objects)
    //  i.drawTo(window);
        
    l.drawTo(window,s);

    window.display();

    /*
    // This would've been for having a text box showing the lap number, but I felt like I had enough for this day.
    sf::Text lapText;
    lapText.setPosition(50,50);
    lapText.setColor(sf::Color::Red);
    lapText.setString(std::to_string(car1.getLap()));*/
  }
  return 0;
}
