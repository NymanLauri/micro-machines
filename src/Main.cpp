#include <iostream>
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "PhysicsObject.hpp"
#include <cmath>
#include "Player.hpp"
#include "Functions.hpp"
#include "KeySettings.hpp"
#include "Settings.hpp"
// How to compile: g++ -g -Wall -o game Main.cpp Functions.cpp PhysicsObject.cpp -lBox2D -IBox2D -L. -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

// In this function we initialize 4 players. We do not have to use them all.
int main()
{
  Player player1;
  Player player2;
  Player player3;
  Player player4;
  KeySettings p1keys = {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right}; // We define keys for player 1.
  player1.setKeys(p1keys); // We set p1keys to be the keys for player 1.
  KeySettings p2keys = {sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D};
  player2.setKeys(p2keys);
  KeySettings p3keys = {sf::Keyboard::T, sf::Keyboard::G, sf::Keyboard::F, sf::Keyboard::H};
  player3.setKeys(p3keys);
  KeySettings p4keys = {sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L};
  player4.setKeys(p4keys);
  menu(player1, player2, player3, player4);
  return 0;
}

// This loop controls the menu-windows. The players are given as parameters so that we can adjust their properties.
int menu(Player &player1, Player &player2, Player &player3, Player &player4)
{
  sf::RenderWindow window(sf::VideoMode(1800, 1000),/*sf::VideoMode::getDesktopMode()*/ "Micro Machines", sf::Style::Default); // Create a window in fullscreen mode.
  sf::Event event; // Create an event that stores the actions that the user does.
  window.setFramerateLimit(60); // Set frame limit to be 60.
  int MousePosX = 0; // This will contain the x-coordinate of the cursor.
  int MousePosY = 0; // This will contain the y-coordinate of the cursor.
  sf::Font font;
  font.loadFromFile("Ubuntu-B.ttf"); // Load a font from a file.
  int retValue = -1;

  // Create different kinds of texts and set the colors and positions of them.
  sf::Text ExitButton("Exit", font, 100); // Create a text "Exit".
  sf::Text OptionsButton("Options", font, 100);
  sf::Text StartButton("Start Game", font, 100);
  sf::Text Title("Game name here", font, 150);
  sf::Text LevelButton("Level Editor", font, 100);
  ExitButton.setColor(sf::Color::Black); // Set the color of a text to be black.
  ExitButton.setPosition(window.getSize().x/2-ExitButton.getLocalBounds().width/2, window.getSize().y-ExitButton.getLocalBounds().height*2); // Set the position of a text.
  OptionsButton.setColor(sf::Color::Black);
  OptionsButton.setPosition(window.getSize().x/2-OptionsButton.getLocalBounds().width/2, window.getSize().y-OptionsButton.getLocalBounds().height*3.5);
  StartButton.setColor(sf::Color::Black);
  StartButton.setPosition(window.getSize().x/2-StartButton.getLocalBounds().width/2, window.getSize().y-StartButton.getLocalBounds().height*9);
  LevelButton.setColor(sf::Color::Black);
  LevelButton.setPosition(window.getSize().x/2-LevelButton.getLocalBounds().width/2, window.getSize().y-LevelButton.getLocalBounds().height*6.2);
  Title.setColor(sf::Color::Red);
  Title.setStyle(sf::Text::Underlined); // Set a text to be underlined.
  Title.setPosition(window.getSize().x/2-Title.getLocalBounds().width/2, window.getSize().y-Title.getLocalBounds().height*8.5);

  
  while (window.isOpen()) // The main loop of the menu-window.
    {
      MousePosX = sf::Mouse::getPosition(window).x; // Get the x-coordinate of the position of the mouse.
      MousePosY = sf::Mouse::getPosition(window).y; // Get the y-coordinate of the position of the mouse.
      if (MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 && MousePosY >= ExitButton.getPosition().y*1.03 &&
	  MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the position of the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue); // Change the color of the text to blue.
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black); // Otherwise, keep the color black.
	}
      
      if (MousePosX >= OptionsButton.getPosition().x*1.01 && MousePosX <= OptionsButton.getPosition().x+OptionsButton.getLocalBounds().width*1.1 && MousePosY >= OptionsButton.getPosition().y*1.03 &&
	  MousePosY <= OptionsButton.getPosition().y+OptionsButton.getLocalBounds().height*1.5) // If the position of the mouse is on top of the Options-button.
	{
	  OptionsButton.setColor(sf::Color::Blue);
	}
      else
	{
	  OptionsButton.setColor(sf::Color::Black);
	}
      
      if (MousePosX >= StartButton.getPosition().x*1.01 && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.1 && MousePosY >= StartButton.getPosition().y*1.03 &&
	  MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the position of the mouse is on top of the Start Game -button.
	{
	  StartButton.setColor(sf::Color::Blue);
	}
      else
	{
	  StartButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= LevelButton.getPosition().x*1.01 && MousePosX <= LevelButton.getPosition().x+LevelButton.getLocalBounds().width*1.1 && MousePosY >= LevelButton.getPosition().y*1.03 &&
	  MousePosY <= LevelButton.getPosition().y+LevelButton.getLocalBounds().height*1.5) // If the position of the mouse is on top of the Level Editor -button.
	{
	  LevelButton.setColor(sf::Color::Blue);
	}
      else
	{
	  LevelButton.setColor(sf::Color::Black);
	}
      
      while (window.pollEvent(event)) // Loop through different events.
	{ 
	  switch (event.type)
	    {
	    case sf::Event::Closed: // If the user wants to close the window.
	      window.close(); // Close the window.
	      break;

	    case sf::Event::KeyPressed: // If some keyboard key is pressed.
	      switch(event.key.code)
		{
		case sf::Keyboard::Escape: // If ESC is pressed.
		  window.close();
		  break;

		default:
		  break;
		}
	      
	    case sf::Event::MouseButtonPressed: // If some mouse button is pressed.
	      if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 &&
		  MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  window.close();
		  break;
		}
	      
	      else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= OptionsButton.getPosition().x*1.01 &&
		       MousePosX <= OptionsButton.getPosition().x+OptionsButton.getLocalBounds().width*1.1 && MousePosY >= OptionsButton.getPosition().y*1.03 &&
		       MousePosY <= OptionsButton.getPosition().y+OptionsButton.getLocalBounds().height*1.5) // If the user clicks the options-button.
		{
		  OptionsWindow(window, font, player1, player2, player3, player4); // Go to function OptionsWindow (found in Functions.cpp) that opens a window where the player can adjust settings
		}

	      else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= LevelButton.getPosition().x*1.01 && MousePosX <= LevelButton.getPosition().x+LevelButton.getLocalBounds().width*1.1 &&
		       MousePosY >= LevelButton.getPosition().y*1.03 && MousePosY <= LevelButton.getPosition().y+LevelButton.getLocalBounds().height*1.5) // If the user clicks on the Level Editor -button
		{
		  EditorWindow(window, font); // Go to function EditorWindow (found in Functions.cpp) that opens a window where the user can create levels.
		}

	      else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= StartButton.getPosition().x*1.01 && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.1 &&
		       MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the user clicks on the "Start game"-button.
		{
		  // Go to function StartWindow (found in Functions.cpp) that opens a window where the player will for example choose the maps.
		  retValue = StartWindow(window, font, player1, player2, player3, player4);
		  if (retValue == 1) // retValue is 1 if the user clicked on the "Start"-button in the StartWindow.
		    {
		      Game(window, font, player1, player2, player3, player4); // Go to Game-function that controls the actual game.
		      retValue = 0;
		    }
		}
	      
	    default:
	      break;
	    }
	}
      window.clear(sf::Color::White); // Pain the window white.
      if (retValue == 1)
	{
	  break;
	}
      // Draw different textures and display them on the screen.
      window.draw(ExitButton);
      window.draw(OptionsButton);
      window.draw(StartButton);
      window.draw(LevelButton);
      window.draw(Title);
      window.display();
    }
  return 0;
}

// This function handles the actual gaming.
int Game(sf::RenderWindow &window, sf::Font font, Player &player1, Player &player2, Player &player3, Player &player4)
{
  b2Vec2 gravity(0.0f, 0.0f); // Create gravity for the game world. In this case, it is zero.
  b2World world(gravity); // Create a world.
  
  sf::VideoMode videomode = sf::VideoMode(1800,1000);//sf::VideoMode::getDesktopMode();
  sf::Event event;
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

  // Create another player
  b2BodyDef bodyDefPlayer2;
  bodyDefPlayer2.type = b2_dynamicBody;
  bodyDefPlayer2.position.Set(100 * s.pixelsToMeters, 100 * s.pixelsToMeters);

  b2FixtureDef fixtureDefPlayer2;
  fixtureDefPlayer2.density = 1.0;
  fixtureDefPlayer2.friction = 0.3;

  PhysicsObject playerObj2(world, s, 1.5, bodyDefPlayer2, fixtureDefPlayer, sf::Color::Red);
  
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      } else if (event.type == sf::Event::KeyPressed) {
	if (event.key.code == sf::Keyboard::Escape) {
	  window.close();
	}
	
	else if (event.key.code == sf::Keyboard::P) // If the player pauses the game.
	  {
	    // Create some texts and set their positions etc.
	    sf::Text QuitButton("Exit", font, 80);
	    sf::Text MenuButton("Main Menu", font, 80);
	    QuitButton.setColor(sf::Color::White);
	    MenuButton.setColor(sf::Color::White);
	    QuitButton.setPosition(window.getSize().x/2-QuitButton.getLocalBounds().width/2, window.getSize().y-QuitButton.getLocalBounds().height*4);
	    MenuButton.setPosition(window.getSize().x/2-MenuButton.getLocalBounds().width/2, window.getSize().y-MenuButton.getLocalBounds().height*7);
	    int pauseVar = 0; // This is a variable that controls when to exit the pause-loop.
	    while (1) // Start the pause-loop.
	      {
		int MousePosX = sf::Mouse::getPosition(window).x;
		int MousePosY = sf::Mouse::getPosition(window).y;
		if (MousePosX >= QuitButton.getPosition().x*1.01 && MousePosX <= QuitButton.getPosition().x+QuitButton.getLocalBounds().width*1.2 && MousePosY >= QuitButton.getPosition().y*1.03 &&
		    MousePosY <= QuitButton.getPosition().y+QuitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
		  {
		    QuitButton.setColor(sf::Color::Blue); // Set the color of the button to be blue.
		  }
		else
		  {
		    QuitButton.setColor(sf::Color::White); // Set the color of the button to be white.
		  }
		
		if (MousePosX >= MenuButton.getPosition().x*1.01 && MousePosX <= MenuButton.getPosition().x+MenuButton.getLocalBounds().width*1.1 && MousePosY >= MenuButton.getPosition().y*1.03 &&
		    MousePosY <= MenuButton.getPosition().y+MenuButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main menu"-button.
		  {
		    MenuButton.setColor(sf::Color::Blue);
		  }
		else
		  {
		    MenuButton.setColor(sf::Color::White);
		  }
		
		window.clear();
		// Draw all the player and some other textures to the screen.
		physObj1.drawTo(window, s);
		physObj2.drawTo(window, s);
		physObj3.drawTo(window, s);
		physObj4.drawTo(window, s);
		physObj5.drawTo(window, s);
		playerObj.drawTo(window, s);
		playerObj2.drawTo(window, s);
		window.draw(QuitButton);
		window.draw(MenuButton);
		window.display();
		while (window.pollEvent(event))
		  {
		    if (event.type == sf::Event::KeyPressed)
		      {
			if (event.key.code == sf::Keyboard::P) // If the user presses p to continue the game.
			  {
			    pauseVar = 1;
			    break;
			  }
			else if (event.key.code == sf::Keyboard::Escape) // If the user clicks ESC.
			  {
			    window.close();
			    pauseVar = 1;
			    break;
			  }
		      }
		    else if (event.type == sf::Event::MouseButtonPressed)
		      {
			if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= QuitButton.getPosition().x*1.01 &&
			    MousePosX <= QuitButton.getPosition().x+QuitButton.getLocalBounds().width*1.2 && MousePosY >= QuitButton.getPosition().y*1.03 &&
			    MousePosY <= QuitButton.getPosition().y+QuitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
			  {
			    pauseVar = 1;
			    window.close();
			    break;
			  }
			
			else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= MenuButton.getPosition().x*1.01 &&
				 MousePosX <= MenuButton.getPosition().x+MenuButton.getLocalBounds().width*1.1 && MousePosY >= MenuButton.getPosition().y*1.03 &&
				 MousePosY <= MenuButton.getPosition().y+MenuButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
			  {
			    return 0;
			  }
		      }
		  }
		if (pauseVar == 1)
		  {
		    break;
		  }
	      }
	  }
      }
    }

    // Control the movement of player 1. This is done by applying impulses to the player according to pressed keys.
    if (sf::Keyboard::isKeyPressed(player1.getKeys().up)) playerObj.applyLinearImpulse(b2Vec2(0.0f, 3.0f), playerObj.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player1.getKeys().down)) playerObj.applyLinearImpulse(b2Vec2(0.0f, -3.0f), playerObj.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player1.getKeys().left)) playerObj.applyLinearImpulse(b2Vec2(-3.0f, 0.0f), playerObj.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player1.getKeys().right)) playerObj.applyLinearImpulse(b2Vec2(3.0f, 0.0f), playerObj.getWorldCenter(), true);

    // Control the movement of player 2.
    if (sf::Keyboard::isKeyPressed(player2.getKeys().up)) playerObj2.applyLinearImpulse(b2Vec2(0.0f, 3.0f), playerObj2.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player2.getKeys().down)) playerObj2.applyLinearImpulse(b2Vec2(0.0f, -3.0f), playerObj2.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player2.getKeys().left)) playerObj2.applyLinearImpulse(b2Vec2(-3.0f, 0.0f), playerObj2.getWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(player2.getKeys().right)) playerObj2.applyLinearImpulse(b2Vec2(3.0f, 0.0f), playerObj2.getWorldCenter(), true);
    
    world.Step(1.0/60.0, 8, 3); 
    window.clear();
    physObj1.drawTo(window, s);
    physObj2.drawTo(window, s);
    physObj3.drawTo(window, s);
    physObj4.drawTo(window, s);
    physObj5.drawTo(window, s);
    playerObj.drawTo(window, s);
    playerObj2.drawTo(window, s);
    window.display();
  }
  return 0;
}
