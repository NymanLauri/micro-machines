#include <iostream>
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "PhysicsObject.hpp"
#include <cmath>
#include <vector>
#include <map>
#include "Player.hpp"
#include "Level.hpp"
#include "Car.hpp"
#include "Tile.hpp"
#include "Functions.hpp"
#include "KeySettings.hpp"
#include "Settings.hpp"
#define boxwidth 10

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
  sf::RenderWindow window(sf::VideoMode(1800, 1000), "Micro Machines", sf::Style::Default); // Create a window in fullscreen mode.
  sf::Event event; // Create an event that stores the actions that the user does.
  window.setFramerateLimit(60); // Set frame limit to be 60.
  int MousePosX = 0; // This will contain the x-coordinate of the cursor.
  int MousePosY = 0; // This will contain the y-coordinate of the cursor.
  sf::Font font;
  font.loadFromFile("Ubuntu-B.ttf"); // Load a font from a file.
  std::pair <int, int> retValues; // This is the pair that is returned from the function startWindow().
  int ret = -1; // This is the return value of function EditorWindow

  // Create different kinds of texts and set the colors and positions of them.
  sf::Text ExitButton("Exit", font, 100); // Create a text "Exit".
  sf::Text OptionsButton("Options", font, 100);
  sf::Text StartButton("Start Game", font, 100);
  sf::Text Title("Game name here", font, 150);
  sf::Text LevelButton("Level Editor", font, 100);
  ExitButton.setColor(sf::Color::Black);
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
		  window.close(); // Close the window.
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
		  ret = EditorWindow(window, font); // Go to function EditorWindow (found in Functions.cpp) that opens a window where the user can create levels.
		  if (ret == 1) // Exit the game.
		    {
		      return 0;
		    }
		}

	      else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= StartButton.getPosition().x*1.01 && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.1 &&
		       MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the user clicks on the "Start game"-button.
		{
		  // Go to function StartWindow (found in Functions.cpp) that opens a window where the player will for example choose the maps.
		  retValues = StartWindow(window, font, player1, player2, player3, player4);
		  if (retValues.first != 0)
		    {
		      Game(window, font, player1, player2, player3, player4, retValues.first, retValues.second); // Go to Game-function that controls the actual game.
		    }
		}
	      
	    default:
	      break;
	    }
	}
      window.clear(sf::Color::White); // Paint the window white.
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
int Game(sf::RenderWindow &window, sf::Font font, Player &player1, Player &player2, Player &player3, Player &player4, int retValue, int mapValue)
{
  b2Vec2 gravity(0.0f, 0.0f); // Create gravity, which is zero.
  b2World world(gravity); // Create world.
  
  sf::VideoMode videomode = sf::VideoMode(1800,1000);

  Settings s(videomode.width, videomode.height, 180, 100); // Create Settings s that contains information about for example the size of the window.
  int x = s.screenWidth/boxwidth;
  int y = s.screenHeight/boxwidth;
  std::vector <Level> L; // This vector contains one created level.
  int returnValue = -1; // This is the return value of function EndWindow().
  
  try {
    if (mapValue == 1) // If mapValue is 1, we create level according to file map1.txt.
      {
	Level level("map1.txt", world, s);
	L.push_back(level); // Insert this created level to the vector L.
      }
    else if (mapValue == 2)
      {
      	Level level("map2.txt", world, s); // If mapValue is 2, we create level accroding to file map2.txt.
	L.push_back(level);
      }
    else if (mapValue == 3)
      {
	Level level("map3.txt", world, s); // If mapValue is 3, we create level according to file map3.txt.
	L.push_back(level);
      }
    else if (mapValue == 4)
      {
	Level level("map4.txt", world, s); // If mapValue is 4, we create level according to file map4.txt.
	L.push_back(level);
      }
    L[0].createScreenBorders(world); // Create borders for the created world.
    std::vector<int> co = L[0].getCoords(); // co contains the x- and y-coordinates of all starting points of the cars. We use these to set the initial positions of the cars.

    // PlayersAndCars have integer keys (such that 0-->player1, 1-->player2...) and cars as values. With this we can get the car according to the player.
    std::map <int, std::shared_ptr<Car>> PlayersAndCars;
    std::vector<Player> Players; // This vector contains the players.

    if (retValue >= 1) // If retValue (= the number of players) is greater or equal to 1, we create car1.
      {
        auto car1 = std::make_shared<Car>(world, s, L[0], b2Vec2(co[0]/boxwidth, 100-co[1]/boxwidth), sf::Color::Red); // Create car1, set it's position and color.
        L[0].addCar(car1); // Add car to the level.
        PlayersAndCars.insert (std::pair<int, std::shared_ptr<Car>>(0, car1)); // Add the car and corresponding integer (player) to the map PlayersAndCars.
        Players.push_back(player1); // Add player1 to the vector Players.
      }
    if (retValue >= 2) // If retValue is greater or equal to 2, we create car2.
      {
        auto car2 = std::make_shared<Car>(world, s, L[0], b2Vec2(co[2]/boxwidth, 100-co[3]/boxwidth), sf::Color::Blue);
        L[0].addCar(car2);
        PlayersAndCars.insert (std::pair<int, std::shared_ptr<Car>>(1, car2));
        Players.push_back(player2);
      }
    if (retValue >= 3)
      {
        auto car3 = std::make_shared<Car>(world, s, L[0], b2Vec2(co[4]/boxwidth, 100-co[5]/boxwidth), sf::Color::Green);
        L[0].addCar(car3);
        PlayersAndCars.insert (std::pair<int, std::shared_ptr<Car>>(2, car3));
        Players.push_back(player3);
      }
    if (retValue >= 4)
      {
        auto car4 = std::make_shared<Car>(world, s, L[0], b2Vec2(co[6]/boxwidth, 100-co[7]/boxwidth), sf::Color::Yellow);
        L[0].addCar(car4);
        PlayersAndCars.insert (std::pair<int, std::shared_ptr<Car>>(3, car4));
        Players.push_back(player4);
      }
      
    float timeStep = 1.0/60.0;

    window.setFramerateLimit(60); // Set the limit of the framerate to 60.
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) { // Loop through different events.
        if (event.type == sf::Event::Closed) { // If the window is closed.
	  window.close();
        } else if (event.type == sf::Event::KeyPressed) { // If some key is pressed.
	  if (event.key.code == sf::Keyboard::Escape) { // If ESC is pressed.
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
		  int MousePosX = sf::Mouse::getPosition(window).x; // The x-coordinate of the cursor.
		  int MousePosY = sf::Mouse::getPosition(window).y; // The y-coordinate of the cursor.
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

		  // Refresh the screen.
		  window.clear();
		  L[0].drawTo(window);
		  window.draw(QuitButton);
		  window.draw(MenuButton);
		  window.display();
		  while (window.pollEvent(event)) // Loop through events.
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
		      else if (event.type == sf::Event::MouseButtonPressed) // Is some mouse button is pressed.
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
      L[0].checkpointChecker();
      L[0].sortCars(); // Sort the cars such that the car that is leading the game is at index 0 in a list that belongs to the level.
      if(L[0].getLevelLap() > 3) {
	if (L[0].getCar() == PlayersAndCars.at(0)) // If the leading car belongs to player 1 and that car has completed all laps.
	  {
	    returnValue = EndWindow(window, font, 1);
	  }
	else if (L[0].getCar() == PlayersAndCars.at(1)) // If the leading car belongs to player 2 and that car has completed all laps.
	  {
	    returnValue = EndWindow(window, font, 2);
	  }
	else if (L[0].getCar() == PlayersAndCars.at(2)) // If the leading car belongs to player 3 and that car has completed all laps.
	  {
	    returnValue = EndWindow(window, font, 3);
	  }
	else if (L[0].getCar() == PlayersAndCars.at(3)) // If the leading car belongs to player 4 and that car has completed all laps.
	  {
	    returnValue == EndWindow(window, font, 4);
	  }
	if (returnValue == 1)
	  {
	    return 0;
	  }
      }
      for (int i = 0; i < Players.size(); ++i) // Loop through all the player in the vector players.
        {
	  // If some key is pressed and that key is some control of player Players[i], apply force to the car associated with that player using the map PlayersAndCars.
	  if (sf::Keyboard::isKeyPressed(Players[i].getKeys().up)) PlayersAndCars.at(i)->accelerate();
	  if (sf::Keyboard::isKeyPressed(Players[i].getKeys().down)) PlayersAndCars.at(i)->decelerate();
	  if (sf::Keyboard::isKeyPressed(Players[i].getKeys().left)) PlayersAndCars.at(i)->turnLeft();
	  if (sf::Keyboard::isKeyPressed(Players[i].getKeys().right)) PlayersAndCars.at(i)->turnRight();
	  PlayersAndCars.at(i)->updateMovement();
        }
      world.Step(timeStep, 8, 3);
      // Refresh the screen.
      window.clear();
      L[0].drawTo(window);
      window.display();
    }
    
  } catch(std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
