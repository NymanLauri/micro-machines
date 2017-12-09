#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "fstream"
#include "Player.hpp"
#include "KeySettings.hpp"
#include "Settings.hpp"
#include "PhysicsObject.hpp"
#include "Constants.hpp"
#include "Functions.hpp"
#define WIDTH 1800
#define HEIGHT 1000
#define boxwidth 10


// This window opens, when somebody wins the game.
int EndWindow(sf::RenderWindow &w, sf::Font f, int player_num)
{
  w.setFramerateLimit(60);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  // Create some texts.
  sf::Text MenuButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text EndText("None", f, 150);
  // We print the right text depending on which player has won the game.
  if (player_num == 1)
    {
      EndText.setString("Player 1 wins!");
    }
  else if (player_num == 2)
    {
      EndText.setString("Player 2 wins!");
    }
  else if (player_num == 3)
    {
      EndText.setString("Player 3 wins!");
    }
  else if (player_num == 4)
    {
      EndText.setString("Player 4 wins!");
    }
  // Set the colors and locations of the texts.
  MenuButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  EndText.setColor(sf::Color::Red);
  MenuButton.setPosition(w.getSize().x/6-MenuButton.getLocalBounds().width/2, w.getSize().y-MenuButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  EndText.setPosition(w.getSize().x/2-EndText.getLocalBounds().width/2, w.getSize().y/2-EndText.getLocalBounds().height/2);
  while (w.isOpen()) // The actual game loop that controls all the events done by the user.
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
      if (MousePosX >= MenuButton.getPosition().x*1.01 && MousePosX <= MenuButton.getPosition().x+MenuButton.getLocalBounds().width*1.1 && MousePosY >= MenuButton.getPosition().y*1.03 &&
	  MousePosY <= MenuButton.getPosition().y+MenuButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main menu"-button.
	{
	  MenuButton.setColor(sf::Color::Blue); // Set the color of the text to be blue.
	}
      else
	{
	  MenuButton.setColor(sf::Color::Black); // Set the color of the text to be black.
	}

      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 &&
	  MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}
      while (w.pollEvent(e)) // Loop through all events.
	{
	  switch (e.type)
	    {
	    case sf::Event::Closed: // If the window is closed.
	      w.close();
	      break;

	    case sf::Event::KeyPressed: // If some key is pressed.
	      switch(e.key.code)
		{
		case sf::Keyboard::Escape: // If ESC is pressed.
		  w.close();
		  break;

		default:
		  break;
		}

	    case sf::Event::MouseButtonPressed:
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= MenuButton.getPosition().x*1.01 && MousePosX <= MenuButton.getPosition().x+MenuButton.getLocalBounds().width*1.1 &&
		  MousePosY >= MenuButton.getPosition().y*1.03 && MousePosY <= MenuButton.getPosition().y+MenuButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
		{
		  var = 1; // This variable controls when to exit this function.
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 &&
		       MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  w.close(); // Close the window.
		  break;
		}
	    default:
	      break;
	    }
	  if (var == 1)
	    {
	      return 1;
	    }
	}
      // Refresh the screen.
      w.clear(sf::Color::White);
      w.draw(MenuButton);
      w.draw(ExitButton);
      w.draw(EndText);
      w.display();
    }
  return 0;
}

std::pair <int, int> StartWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  w.setFramerateLimit(60);
  // Create a vector playerKeys that contains keys of all the players. This is used to check that all keys are unqiue, that is, that many players do not try to use same keys.
  std::vector<sf::Keyboard::Key> playerKeys {p1.getKeys().up, p1.getKeys().down, p1.getKeys().left, p1.getKeys().right, p2.getKeys().up, p2.getKeys().down, p2.getKeys().left,
      p2.getKeys().right, p3.getKeys().up, p3.getKeys().down, p3.getKeys().left, p3.getKeys().right, p4.getKeys().up, p4.getKeys().down, p4.getKeys().left, p4.getKeys().right};
  std::sort(playerKeys.begin(), playerKeys.end()); // Sort the vectror playerKeys.
  int var = 0;
  std::pair<int, int> returns;
  int numOfPlayers = 1;
  int mapNum = 1;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  // Create some texts and set their color and locations.
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text StartButton("Start", f, 100);
  sf::Text Heading1("Number of players", f, 80);
  sf::Text Heading2("Choose the map", f, 80);
  sf::Text Lkm1("1", f, 80);
  sf::Text Lkm2("2", f, 80);
  sf::Text Lkm3("3", f, 80);
  sf::Text Lkm4("4", f, 80);
  sf::Text Map1("Map 1", f, 80);
  sf::Text Map2("Map 2", f, 80);
  sf::Text Map3("Map 3", f, 80);
  sf::Text Map4("Map 4", f, 80);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  StartButton.setColor(sf::Color::Black);
  Heading1.setColor(sf::Color::Red);
  Heading2.setColor(sf::Color::Red);
  Lkm1.setColor(sf::Color::Black);
  Lkm2.setColor(sf::Color::Black);
  Lkm3.setColor(sf::Color::Black);
  Lkm4.setColor(sf::Color::Black);
  Map1.setColor(sf::Color::Black);
  Map2.setColor(sf::Color::Black);
  Map3.setColor(sf::Color::Black);
  Map4.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  StartButton.setPosition(w.getSize().x/2-StartButton.getLocalBounds().width/2, w.getSize().y/2-StartButton.getLocalBounds().height/2);
  Heading1.setPosition(w.getSize().x/5.0-Heading1.getLocalBounds().width/2, w.getSize().y/9-Heading1.getLocalBounds().height);
  Heading2.setPosition(w.getSize().x/1.22-Heading2.getLocalBounds().width/2, w.getSize().y/9-Heading2.getLocalBounds().height);
  Lkm1.setPosition(w.getSize().x/5.5-Lkm1.getLocalBounds().width/2, w.getSize().y/5-Lkm1.getLocalBounds().height);
  Lkm2.setPosition(w.getSize().x/5.5-Lkm2.getLocalBounds().width/2, w.getSize().y/3-Lkm2.getLocalBounds().height);
  Lkm3.setPosition(w.getSize().x/5.5-Lkm3.getLocalBounds().width/2, w.getSize().y/2.1-Lkm3.getLocalBounds().height);
  Lkm4.setPosition(w.getSize().x/5.5-Lkm4.getLocalBounds().width/2, w.getSize().y/1.6-Lkm4.getLocalBounds().height);
  Map1.setPosition(w.getSize().x/1.2-Map1.getLocalBounds().width/2, w.getSize().y/5-Map1.getLocalBounds().height);
  Map2.setPosition(w.getSize().x/1.2-Map2.getLocalBounds().width/2, w.getSize().y/3-Map2.getLocalBounds().height);
  Map3.setPosition(w.getSize().x/1.2-Map3.getLocalBounds().width/2, w.getSize().y/2.1-Map3.getLocalBounds().height);
  Map4.setPosition(w.getSize().x/1.2-Map4.getLocalBounds().width/2, w.getSize().y/1.6-Map4.getLocalBounds().height);

  while (w.isOpen()) // The actual game loop that controls all the events done by the user.
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
      if (MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 &&
	  MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main menu"-button.
	{
	  ReturnButton.setColor(sf::Color::Blue); // Set the color of the text to be blue.
	}
      else
	{
	  ReturnButton.setColor(sf::Color::Black); // Set the color of the text to be black.
	}

      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 &&
	  MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 && MousePosY >= StartButton.getPosition().y*1.03 &&
	  MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the mouse is on top of the Start-button.
	{
	  StartButton.setColor(sf::Color::Blue);
	}
      else
	{
	  StartButton.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm1.getPosition().x && MousePosX <= Lkm1.getPosition().x+Lkm1.getLocalBounds().width && MousePosY >= Lkm1.getPosition().y*1.03 &&
	  MousePosY <= Lkm1.getPosition().y+Lkm1.getLocalBounds().height*1.5) // If the mouse is on top of the number 1 under "Number of player".
	{
	  Lkm1.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm1.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm2.getPosition().x && MousePosX <= Lkm2.getPosition().x+Lkm2.getLocalBounds().width && MousePosY >= Lkm2.getPosition().y*1.03 &&
	  MousePosY <= Lkm2.getPosition().y+Lkm2.getLocalBounds().height*1.5) // If the mouse is on top of the number 2 under "Number of player".
	{
	  Lkm2.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm2.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm3.getPosition().x && MousePosX <= Lkm3.getPosition().x+Lkm3.getLocalBounds().width && MousePosY >= Lkm3.getPosition().y*1.03 &&
	  MousePosY <= Lkm3.getPosition().y+Lkm3.getLocalBounds().height*1.5) // If the mouse is on top of the number 3 under "Number of player".
	{
	  Lkm3.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm3.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm4.getPosition().x && MousePosX <= Lkm4.getPosition().x+Lkm4.getLocalBounds().width && MousePosY >= Lkm4.getPosition().y*1.03 &&
	  MousePosY <= Lkm4.getPosition().y+Lkm4.getLocalBounds().height*1.5) // If the mouse is on top of the number 4 under "Number of player".
	{
	  Lkm4.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm4.setColor(sf::Color::Black);
	}
      if (MousePosX >= Map1.getPosition().x && MousePosX <= Map1.getPosition().x+Map1.getLocalBounds().width && MousePosY >= Map1.getPosition().y*1.03 &&
	  MousePosY <= Map1.getPosition().y+Map1.getLocalBounds().height*1.5) // If the mouse is on top of the text "Map 1".
	{
	  Map1.setColor(sf::Color::Red);
	}
      else
	{
	  Map1.setColor(sf::Color::Black);
	}
      if (MousePosX >= Map2.getPosition().x && MousePosX <= Map2.getPosition().x+Map2.getLocalBounds().width && MousePosY >= Map2.getPosition().y*1.03 &&
	  MousePosY <= Map2.getPosition().y+Map2.getLocalBounds().height*1.5) // If the mouse is on top of the text "Map 2".
	{
	  Map2.setColor(sf::Color::Red);
	}
      else
	{
	  Map2.setColor(sf::Color::Black);
	}
      if (MousePosX >= Map3.getPosition().x && MousePosX <= Map3.getPosition().x+Map3.getLocalBounds().width && MousePosY >= Map3.getPosition().y*1.03 &&
	  MousePosY <= Map3.getPosition().y+Map3.getLocalBounds().height*1.5) // If the mouse is on top of the text "Map 3".
	{
	  Map3.setColor(sf::Color::Red);
	}
      else
	{
	  Map3.setColor(sf::Color::Black);
	}
      if (MousePosX >= Map4.getPosition().x && MousePosX <= Map4.getPosition().x+Map4.getLocalBounds().width && MousePosY >= Map4.getPosition().y*1.03 &&
	  MousePosY <= Map4.getPosition().y+Map4.getLocalBounds().height*1.5) // If the mouse is on top of the text "Map 4".
	{
	  Map4.setColor(sf::Color::Red);
	}
      else
	{
	  Map4.setColor(sf::Color::Black);
	}
      
      while (w.pollEvent(e)) // Loop through all events.
	{
	  switch (e.type)
	    {
	    case sf::Event::Closed: // If the window is closed.
	      var = 1;
	      w.close();
	      break;

	    case sf::Event::KeyPressed: // If some key is pressed.
	      switch(e.key.code)
		{
		case sf::Keyboard::Escape: // If ESC is pressed.
		  var = 1;
		  w.close();
		  break;

		default:
		  break;
		}

	    case sf::Event::MouseButtonPressed:
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 &&
		  MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
		{
		  var = 1; // This is used to control the loop such that we return to the function that called this function.
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 &&
		       MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 &&
		       MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the user clicks on the start-button.
		{
		  if (std::unique(playerKeys.begin(), playerKeys.end()) == playerKeys.end()) // If all the keys in the playerKeys-vector are unique.
		    {
		      returns = std::make_pair(numOfPlayers, mapNum);
		      return returns; // This return value tells the menu()-function to start the game with right amount of players.
		    }
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm1.getPosition().x && MousePosX <= Lkm1.getPosition().x+Lkm1.getLocalBounds().width &&
		       MousePosY >= Lkm1.getPosition().y*1.03 && MousePosY <= Lkm1.getPosition().y+Lkm1.getLocalBounds().height*1.5) // If the user clicks on 1 under "Number of players".
		{
		  Lkm1.setColor(sf::Color::Red);
		  numOfPlayers = 1;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm2.getPosition().x && MousePosX <= Lkm2.getPosition().x+Lkm2.getLocalBounds().width &&
		       MousePosY >= Lkm2.getPosition().y*1.03 && MousePosY <= Lkm2.getPosition().y+Lkm2.getLocalBounds().height*1.5) // If the user clicks on 2 under "Number of players".
		{
		  Lkm2.setColor(sf::Color::Red);
		  numOfPlayers = 2;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm3.getPosition().x && MousePosX <= Lkm3.getPosition().x+Lkm3.getLocalBounds().width &&
		       MousePosY >= Lkm3.getPosition().y*1.03 && MousePosY <= Lkm3.getPosition().y+Lkm3.getLocalBounds().height*1.5) // If the user clicks on 3 under "Number of players".
		{
		  Lkm3.setColor(sf::Color::Red);
		  numOfPlayers = 3;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm4.getPosition().x && MousePosX <= Lkm4.getPosition().x+Lkm4.getLocalBounds().width &&
		       MousePosY >= Lkm4.getPosition().y*1.03 && MousePosY <= Lkm4.getPosition().y+Lkm4.getLocalBounds().height*1.5) // If the user clicks on 4 under "Number of players".
		{
		  Lkm4.setColor(sf::Color::Red);
		  numOfPlayers = 4;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Map1.getPosition().x && MousePosX <= Map1.getPosition().x+Map1.getLocalBounds().width &&
		       MousePosY >= Map1.getPosition().y*1.03 && MousePosY <= Map1.getPosition().y+Map1.getLocalBounds().height*1.5) // If the user clicks on "Map 1".
		{
		  mapNum = 1;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Map2.getPosition().x && MousePosX <= Map2.getPosition().x+Map2.getLocalBounds().width &&
		       MousePosY >= Map2.getPosition().y*1.03 && MousePosY <= Map2.getPosition().y+Map2.getLocalBounds().height*1.5) // If the user clicks on "Map 2".
		{
		  mapNum = 2;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Map3.getPosition().x && MousePosX <= Map3.getPosition().x+Map3.getLocalBounds().width &&
		       MousePosY >= Map3.getPosition().y*1.03 && MousePosY <= Map3.getPosition().y+Map3.getLocalBounds().height*1.5) // If the user clicks on "Map 3".
		{
		  mapNum = 3;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Map4.getPosition().x && MousePosX <= Map4.getPosition().x+Map4.getLocalBounds().width &&
		       MousePosY >= Map4.getPosition().y*1.03 && MousePosY <= Map4.getPosition().y+Map4.getLocalBounds().height*1.5) // If the user clicks on "Map 4".
		{
		  mapNum = 4;
		}
	    default:
	      break;
	    }
	  if (var == 1)
	    {
	      returns = std::make_pair(0, 0);
	      return returns;
	    }
	}
      // Refresh the screen.
      w.clear(sf::Color::White);
      w.draw(ReturnButton);
      w.draw(ExitButton);
      w.draw(StartButton);
      w.draw(Heading1);
      w.draw(Heading2);
      w.draw(Lkm1);
      w.draw(Lkm2);
      w.draw(Lkm3);
      w.draw(Lkm4);
      w.draw(Map1);
      w.draw(Map2);
      w.draw(Map3);
      w.draw(Map4);
      w.display();
    }
  returns = std::make_pair(-1, -1);
  return returns;
}
// We will enter this function when the user clicks on the Options-button in the first menu-screen.
int OptionsWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  w.setFramerateLimit(60);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  // This is a map contains some keyboard keys paired with the corrsedponding std::string.
  std::map <sf::Keyboard::Key, std::string> Keys{{sf::Keyboard::Q, "Q"}, {sf::Keyboard::W, "W"}, {sf::Keyboard::E, "E"}, {sf::Keyboard::R, "R"}, {sf::Keyboard::T, "T"},
					         {sf::Keyboard::Y, "Y"}, {sf::Keyboard::U, "U"}, {sf::Keyboard::I, "I"}, {sf::Keyboard::O, "O"}, {sf::Keyboard::P, "P"},
						 {sf::Keyboard::A, "A"}, {sf::Keyboard::S, "S"}, {sf::Keyboard::D, "D"}, {sf::Keyboard::F, "F"}, {sf::Keyboard::G, "G"},
						 {sf::Keyboard::H, "H"}, {sf::Keyboard::J, "J"}, {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"}, {sf::Keyboard::Z, "Z"},
						 {sf::Keyboard::X, "X"}, {sf::Keyboard::C, "C"}, {sf::Keyboard::V, "V"}, {sf::Keyboard::B, "B"}, {sf::Keyboard::N, "N"},
						 {sf::Keyboard::M, "M"}, {sf::Keyboard::Up, "Up Arrow"}, {sf::Keyboard::Down, "Down Arrow"}, {sf::Keyboard::Left, "Left Arrow"},
						 {sf::Keyboard::Right, "Right Arrow"}, {sf::Keyboard::Numpad0, "0"}, {sf::Keyboard::Numpad1, "1"}, {sf::Keyboard::Numpad2, "2"},
						 {sf::Keyboard::Numpad3, "3"}, {sf::Keyboard::Numpad4, "4"}, {sf::Keyboard::Numpad5, "5"}, {sf::Keyboard::Numpad6, "6"},
						 {sf::Keyboard::Numpad7, "7"}, {sf::Keyboard::Numpad8, "8"}, {sf::Keyboard::Numpad9, "9"}};
  // Create some texts and set their colors and locations.
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text Player1Opts("Player 1", f, 60);
  sf::Text Player2Opts("Player 2", f, 60);
  sf::Text Player3Opts("Player 3", f, 60);
  sf::Text Player4Opts("Player 4", f, 60);
  sf::Text Up("Up", f, 60);
  sf::Text Down("Down", f, 60);
  sf::Text Left("Left", f, 60);
  sf::Text Right("Right", f, 60);
  sf::Text p1up(Keys.at(p1.getKeys().up), f, 45);
  sf::Text p1down(Keys.at(p1.getKeys().down), f, 45);
  sf::Text p1left(Keys.at(p1.getKeys().left), f, 45);
  sf::Text p1right(Keys.at(p1.getKeys().right), f, 45);
  sf::Text p2up(Keys.at(p2.getKeys().up), f, 45);
  sf::Text p2down(Keys.at(p2.getKeys().down), f, 45);
  sf::Text p2left(Keys.at(p2.getKeys().left), f, 45);
  sf::Text p2right(Keys.at(p2.getKeys().right), f, 45);
  sf::Text p3up(Keys.at(p3.getKeys().up), f, 45);
  sf::Text p3down(Keys.at(p3.getKeys().down), f, 45);
  sf::Text p3left(Keys.at(p3.getKeys().left), f, 45);
  sf::Text p3right(Keys.at(p3.getKeys().right), f, 45);
  sf::Text p4up(Keys.at(p4.getKeys().up), f, 45);
  sf::Text p4down(Keys.at(p4.getKeys().down), f, 45);
  sf::Text p4left(Keys.at(p4.getKeys().left), f, 45);
  sf::Text p4right(Keys.at(p4.getKeys().right), f, 45);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  Player1Opts.setColor(sf::Color::Black);
  Player2Opts.setColor(sf::Color::Black);
  Player3Opts.setColor(sf::Color::Black);
  Player4Opts.setColor(sf::Color::Black);
  Up.setColor(sf::Color::Black);
  Down.setColor(sf::Color::Black);
  Left.setColor(sf::Color::Black);
  Right.setColor(sf::Color::Black);
  p1up.setColor(sf::Color::Black);
  p1down.setColor(sf::Color::Black);
  p1left.setColor(sf::Color::Black);
  p1right.setColor(sf::Color::Black);
  p2up.setColor(sf::Color::Black);
  p2down.setColor(sf::Color::Black);
  p2left.setColor(sf::Color::Black);
  p2right.setColor(sf::Color::Black);
  p3up.setColor(sf::Color::Black);
  p3down.setColor(sf::Color::Black);
  p3left.setColor(sf::Color::Black);
  p3right.setColor(sf::Color::Black);
  p4up.setColor(sf::Color::Black);
  p4down.setColor(sf::Color::Black);
  p4left.setColor(sf::Color::Black);
  p4right.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  Up.setPosition(w.getSize().x/12-Up.getLocalBounds().width/2, w.getSize().y-Up.getLocalBounds().height*15);
  Down.setPosition(w.getSize().x/12-Down.getLocalBounds().width/2, w.getSize().y-Down.getLocalBounds().height*15.5);
  Left.setPosition(w.getSize().x/12-Left.getLocalBounds().width/2, w.getSize().y-Left.getLocalBounds().height*11.8);
  Right.setPosition(w.getSize().x/12-Right.getLocalBounds().width/2, w.getSize().y-Right.getLocalBounds().height*7.6);
  Player1Opts.setPosition(w.getSize().x/3.8-Player1Opts.getLocalBounds().width/2, w.getSize().y-Player1Opts.getLocalBounds().height*16);
  Player2Opts.setPosition(w.getSize().x/2.3-Player2Opts.getLocalBounds().width/2, w.getSize().y-Player2Opts.getLocalBounds().height*16);
  Player3Opts.setPosition(w.getSize().x/1.6-Player3Opts.getLocalBounds().width/2, w.getSize().y-Player3Opts.getLocalBounds().height*16);
  Player4Opts.setPosition(w.getSize().x/1.2-Player4Opts.getLocalBounds().width/2, w.getSize().y-Player4Opts.getLocalBounds().height*16);
  p1up.setPosition(w.getSize().x/3.8-p1up.getLocalBounds().width/2, w.getSize().y/4.5);
  p1down.setPosition(w.getSize().x/3.8-p1down.getLocalBounds().width/2, w.getSize().y/3.05);
  p1left.setPosition(w.getSize().x/3.8-p1left.getLocalBounds().width/2, w.getSize().y/2.25);
  p1right.setPosition(w.getSize().x/3.8-p1right.getLocalBounds().width/2, w.getSize().y/1.75);
  p2up.setPosition(w.getSize().x/2.3-p2up.getLocalBounds().width/2, w.getSize().y/4.5);
  p2down.setPosition(w.getSize().x/2.3-p2down.getLocalBounds().width/2, w.getSize().y/3.05);
  p2left.setPosition(w.getSize().x/2.3-p2left.getLocalBounds().width/2, w.getSize().y/2.25);
  p2right.setPosition(w.getSize().x/2.3-p2right.getLocalBounds().width/2, w.getSize().y/1.75);
  p3up.setPosition(w.getSize().x/1.6-p3up.getLocalBounds().width/2, w.getSize().y/4.5);
  p3down.setPosition(w.getSize().x/1.6-p3down.getLocalBounds().width/2, w.getSize().y/3.05);
  p3left.setPosition(w.getSize().x/1.6-p3left.getLocalBounds().width/2, w.getSize().y/2.25);
  p3right.setPosition(w.getSize().x/1.6-p3right.getLocalBounds().width/2, w.getSize().y/1.75);
  p4up.setPosition(w.getSize().x/1.2-p4up.getLocalBounds().width/2, w.getSize().y/4.5);
  p4down.setPosition(w.getSize().x/1.2-p4down.getLocalBounds().width/2, w.getSize().y/3.05);
  p4left.setPosition(w.getSize().x/1.2-p4left.getLocalBounds().width/2, w.getSize().y/2.25);
  p4right.setPosition(w.getSize().x/1.2-p4right.getLocalBounds().width/2, w.getSize().y/1.75);
  std::vector<sf::Text> Texts {p1up, p1down, p1left, p1right, p2up, p2down, p2left, p2right,
      p3up, p3down, p3left, p3right, p4up, p4down, p4left, p4right}; // This vector contains some texts so that they are easier to draw.


  while (w.isOpen()) // This is the actual game loop.
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
      for (auto it = Texts.begin(); it != Texts.end(); ++it) // Iterate through the vector Texts.
	{
	  if (MousePosX >= it->getPosition().x && MousePosX <= it->getPosition().x+it->getLocalBounds().width && MousePosY >= it->getPosition().y*1.03 &&
	      MousePosY <= it->getPosition().y+it->getLocalBounds().height*1.5) // If the mouse is on top of some text in the vector.
	    {
	      it->setColor(sf::Color::Blue); // Set the color of the text to blue.
	    }
	  else
	    {
	      it->setColor(sf::Color::Black); // Set the color of the text to black.
	    }
	}
      if (MousePosX >= ReturnButton.getPosition().x && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width && MousePosY >= ReturnButton.getPosition().y*1.03 &&
	  MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main Menu"-button.
	{
	  ReturnButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ReturnButton.setColor(sf::Color::Black);
	}
      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width && MousePosY >= ExitButton.getPosition().y*1.03 &&
	  MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}
      
      while (w.pollEvent(e)) // Loop through all events.
	{
	  switch (e.type)
	    {
	    case sf::Event::Closed:
	      w.close();
	      break;

	    case sf::Event::KeyPressed: // If some keyboard key is pressed.
	      switch(e.key.code)
		{
		case sf::Keyboard::Escape: // If ESC is pressed.
		  w.close(); // Close the window.
		  break;

		default:
		  break;
		}

	    case sf::Event::MouseButtonPressed:
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 &&
		  MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
		{
		  var = 1; // This controls the loop such that we return to the function that called this function.
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 &&
		       MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1up.getPosition().x && MousePosX <= p1up.getPosition().x+p1up.getLocalBounds().width && MousePosY >= p1up.getPosition().y*1.03 && MousePosY <= p1up.getPosition().y+p1up.getLocalBounds().height*1.5) // If the user clicks on the up-key of player 1.
		{
		  p1up.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 1, Keys); // Go to function WaitForKey (found bottom of this file).
		  p1up.setString(Keys.at(p1.getKeys().up)); // Set the string of the pressed key to be drawn on the window in place of corresponding key.
		  Texts[0] = p1up; // Insert the new key to the vector Texts.
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1down.getPosition().x && MousePosX <= p1down.getPosition().x+p1down.getLocalBounds().width && MousePosY >= p1down.getPosition().y*1.03 && MousePosY <= p1down.getPosition().y+p1down.getLocalBounds().height*1.5) // If the user clicks on the down-key of player 1.
		{
		  p1down.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 2, Keys);
		  p1down.setString(Keys.at(p1.getKeys().down));
		  Texts[1] = p1down;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1left.getPosition().x && MousePosX <= p1left.getPosition().x+p1left.getLocalBounds().width && MousePosY >= p1left.getPosition().y*1.03 && MousePosY <= p1left.getPosition().y+p1left.getLocalBounds().height*1.5) // If the user clicks on the left-key of player 1.
		{
		  p1left.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 3, Keys);
		  p1left.setString(Keys.at(p1.getKeys().left));
		  Texts[2] = p1left;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1right.getPosition().x && MousePosX <= p1right.getPosition().x+p1right.getLocalBounds().width && MousePosY >= p1right.getPosition().y*1.03 && MousePosY <= p1right.getPosition().y+p1right.getLocalBounds().height*1.5) // If the user clicks on the right-key of player 1.
		{
		  p1right.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 4, Keys);
		  p1right.setString(Keys.at(p1.getKeys().right));
		  Texts[3] = p1right;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2up.getPosition().x && MousePosX <= p2up.getPosition().x+p2up.getLocalBounds().width && MousePosY >= p2up.getPosition().y*1.03 && MousePosY <= p2up.getPosition().y+p2up.getLocalBounds().height*1.5) // If the user clicks on the up-key of player 2.
		{
		  p2up.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 1, Keys);
		  p2up.setString(Keys.at(p2.getKeys().up));
		  Texts[4] = p2up;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2down.getPosition().x && MousePosX <= p2down.getPosition().x+p2down.getLocalBounds().width && MousePosY >= p2down.getPosition().y*1.03 && MousePosY <= p2down.getPosition().y+p2down.getLocalBounds().height*1.5) // If the user clicks on the down-key of player 2.
		{
		  p2down.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 2, Keys);
		  p2down.setString(Keys.at(p2.getKeys().down));
		  Texts[5] = p2down;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2left.getPosition().x && MousePosX <= p2left.getPosition().x+p2left.getLocalBounds().width && MousePosY >= p2left.getPosition().y*1.03 && MousePosY <= p2left.getPosition().y+p2left.getLocalBounds().height*1.5) // If the user clicks on the left-key of player 2.
		{
		  p2left.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 3, Keys);
		  p2left.setString(Keys.at(p2.getKeys().left));
		  Texts[6] = p2left;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2right.getPosition().x && MousePosX <= p2right.getPosition().x+p2right.getLocalBounds().width && MousePosY >= p2right.getPosition().y*1.03 && MousePosY <= p2right.getPosition().y+p2right.getLocalBounds().height*1.5) // If the user clicks on the right-key of player 2.
		{
		  p2right.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 4, Keys);
		  p2right.setString(Keys.at(p2.getKeys().right));
		  Texts[7] = p2right;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3up.getPosition().x && MousePosX <= p3up.getPosition().x+p3up.getLocalBounds().width && MousePosY >= p3up.getPosition().y*1.03 && MousePosY <= p3up.getPosition().y+p3up.getLocalBounds().height*1.5) // If the user clicks on the up-key of player 3.
		{
		  p3up.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 1, Keys);
		  p3up.setString(Keys.at(p3.getKeys().up));
		  Texts[8] = p3up;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3down.getPosition().x && MousePosX <= p3down.getPosition().x+p3down.getLocalBounds().width && MousePosY >= p3down.getPosition().y*1.03 && MousePosY <= p3down.getPosition().y+p3down.getLocalBounds().height*1.5) // If the user clicks on the down-key of player 3.
		{
		  p3down.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 2, Keys);
		  p3down.setString(Keys.at(p3.getKeys().down));
		  Texts[9] = p3down;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3left.getPosition().x && MousePosX <= p3left.getPosition().x+p3left.getLocalBounds().width && MousePosY >= p3left.getPosition().y*1.03 && MousePosY <= p3left.getPosition().y+p3left.getLocalBounds().height*1.5) // If the user clicks on the left-key of player 3.
		{
		  p3left.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 3, Keys);
		  p3left.setString(Keys.at(p3.getKeys().left));
		  Texts[10] = p3left;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3right.getPosition().x && MousePosX <= p3right.getPosition().x+p3right.getLocalBounds().width && MousePosY >= p3right.getPosition().y*1.03 && MousePosY <= p3right.getPosition().y+p3right.getLocalBounds().height*1.5) // If the user clicks on the right-key of player 3.
		{
		  p3right.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 4, Keys);
		  p3right.setString(Keys.at(p3.getKeys().right));
		  Texts[11] = p3right;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4up.getPosition().x && MousePosX <= p4up.getPosition().x+p4up.getLocalBounds().width && MousePosY >= p4up.getPosition().y*1.03 && MousePosY <= p4up.getPosition().y+p4up.getLocalBounds().height*1.5) // If the user clicks on the up-key of player 4.
		{
		  p4up.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 1, Keys);
		  p4up.setString(Keys.at(p4.getKeys().up));
		  Texts[12] = p4up;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4down.getPosition().x && MousePosX <= p4down.getPosition().x+p4down.getLocalBounds().width && MousePosY >= p4down.getPosition().y*1.03 && MousePosY <= p4down.getPosition().y+p4down.getLocalBounds().height*1.5) // If the user clicks on the down-key of player 4.
		{
		  p4down.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 2, Keys);
		  p4down.setString(Keys.at(p4.getKeys().down));
		  Texts[13] = p4down;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4left.getPosition().x && MousePosX <= p4left.getPosition().x+p4left.getLocalBounds().width && MousePosY >= p4left.getPosition().y*1.03 && MousePosY <= p4left.getPosition().y+p4left.getLocalBounds().height*1.5) // If the user clicks on the left-key of player 4.
		{
		  p4left.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 3, Keys);
		  p4left.setString(Keys.at(p4.getKeys().left));
		  Texts[14] = p4left;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4right.getPosition().x && MousePosX <= p4right.getPosition().x+p4right.getLocalBounds().width && MousePosY >= p4right.getPosition().y*1.03 && MousePosY <= p4right.getPosition().y+p4right.getLocalBounds().height*1.5) // If the user clicks on the right-key of player 4.
		{
		  p4right.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 4, Keys);
		  p4right.setString(Keys.at(p4.getKeys().right));
		  Texts[15] = p4right;
		}
	    }
	  if (var == 1)
	    {
	      return 0;
	    }
	}
      w.clear(sf::Color::White);
      for (auto it = Texts.begin(); it != Texts.end(); ++it) // Loop through the vector Texts and draw the content.
	{
	  w.draw(*it);
	}
      // Draw some other content and refrest the screen.
      w.draw(ReturnButton);
      w.draw(ExitButton);
      w.draw(Up);
      w.draw(Down);
      w.draw(Left);
      w.draw(Right);
      w.draw(Player1Opts);
      w.draw(Player2Opts);
      w.draw(Player3Opts);
      w.draw(Player4Opts);
      w.display();
    }
  return 0;
}

// This function controls the window in which the user can create levels.
int EditorWindow(sf::RenderWindow &w, sf::Font fo)
{
  // Context settings are used here to set the antialiasing level.
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  //sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "SFML test", sf::Style::Default, settings);
  Settings s(WIDTH, HEIGHT, 180, 100);
  //The width and height in 10x10 tiles
  int x = s.screenWidth/boxwidth;
  int y = s.screenHeight/boxwidth;
  //Checkpoint counter
  int checkpoint = 100;
  int A[y][x]; //If 1800x1000 pixels and 180x100 tiles
  std::vector<std::shared_ptr<PhysicsObject>> obstacles;

  //Creating an empty level, x tiles wide, y tiles high
  sf::RectangleShape* tiles[y][x];
  for(int i = 0; i < y; i++)
    {
      for(int j = 0; j < x; j++)
	{
	  sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(boxwidth, boxwidth));	
	  rectangle->setPosition((j)*boxwidth, i*boxwidth);
	  rectangle->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[i][j] = rectangle;
	  A[i][j] = 0;
	}
    }

  w.setFramerateLimit(60); // Set fps to be 200.

  b2Vec2 gravity(0.f, 0.0f); // Define gravity, in this case it will be zero.
  b2World world(gravity); // Define world.

  //Writing the matrix to file level1.txt
  std::ofstream f("./Level/level1.txt");
  std::ifstream f2("./Level/map1.txt");
    
  // Main program loop.
  while (w.isOpen()) {
    world.Step(1/60.f, 8, 3); // This is used to simulate the world.
    // sf::Event holds information about every event (a key press, mouse movement etc.)
    // which occurs during the program loop.
    sf::Event event;
    // Event loop handles all events which have occurred.
	
	
    while (w.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:{
	w.close();
	break;
	case sf::Event::KeyPressed:
	  switch (event.key.code) {
	  case sf::Keyboard::Escape:
	    w.close();
	    break;
	  case sf::Keyboard::P:
	    {
	      // Create some texts and set their positions etc.
	      sf::Text QuitButton("Exit", fo, 80);
	      sf::Text MenuButton("Main Menu", fo, 80);
	      QuitButton.setColor(sf::Color::White);
	      MenuButton.setColor(sf::Color::White);
	      QuitButton.setPosition(w.getSize().x/2-QuitButton.getLocalBounds().width/2, w.getSize().y-QuitButton.getLocalBounds().height*4);
	      MenuButton.setPosition(w.getSize().x/2-MenuButton.getLocalBounds().width/2, w.getSize().y-MenuButton.getLocalBounds().height*7);
	      int pauseVar = 0; // This is a variable that controls when to exit the pause-loop.
	      while (1) // Start the pause-loop.
		{
		  int MousePosX = sf::Mouse::getPosition(w).x;
		  int MousePosY = sf::Mouse::getPosition(w).y;
		  if (MousePosX >= QuitButton.getPosition().x*1.01 && MousePosX <= QuitButton.getPosition().x+QuitButton.getLocalBounds().width*1.2 && MousePosY >= QuitButton.getPosition().y*1.03 &&
		      MousePosY <= QuitButton.getPosition().y+QuitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
		    {
		      QuitButton.setColor(sf::Color::Blue);
		    }
		  else
		    {
		      QuitButton.setColor(sf::Color::White);
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
		  
		  w.clear();
		  for(int i = 0; i < y; i++)
		    {
		      for(int j = 0; j < x; j++)
			{
			  w.draw(*tiles[i][j]);
			}
		    }
		  for(auto i: obstacles)
		    i->drawTo(w);
		  w.draw(QuitButton);
		  w.draw(MenuButton);
		  w.display();
		  while (w.pollEvent(event))
		    {
		      if (event.type == sf::Event::KeyPressed)
			{
			  if (event.key.code == sf::Keyboard::P) // If the user presses p to continue the game.
			    {
			      pauseVar = 1;
			      break;
			    }
			  else if (event.key.code == sf::Keyboard::Escape)
			    {
			      for (int i = 0; i < y; i++)
				{
				  for (int j = 0; j < x; j++)
				    {
				      delete tiles[i][j];
				    }
				}
			      return 1;
			    }
			}
		      else if (event.type == sf::Event::MouseButtonPressed)
			{
			  if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= QuitButton.getPosition().x*1.01 &&
			      MousePosX <= QuitButton.getPosition().x+QuitButton.getLocalBounds().width*1.2 && MousePosY >= QuitButton.getPosition().y*1.03 &&
			      MousePosY <= QuitButton.getPosition().y+QuitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
			    {
			      for (int i = 0; i < y; i++)
				{
				  for (int j = 0; j < x; j++)
				    {
				      delete tiles[i][j];
				    }
				}
			      return 1;
			    }
			  
			  else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= MenuButton.getPosition().x*1.01 &&
				   MousePosX <= MenuButton.getPosition().x+MenuButton.getLocalBounds().width*1.1 && MousePosY >= MenuButton.getPosition().y*1.03 &&
				   MousePosY <= MenuButton.getPosition().y+MenuButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
			    {
			      for (int i = 0; i < y; i++)
				{
				  for (int j = 0; j < x; j++)
				    {
				      delete tiles[i][j];
				    }
				}
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
	  case sf::Keyboard::S: //Saves matrix to the ofstream f
	    for(int i = 0; i < y; i++) {
	      for(int j = 0; j < x; j++) {
					f << A[i][j] << " ";
	      }
	    }
	    break;
	  case sf::Keyboard::L: //Loads matrix from the ofstream f2
	    for(int i = 0; i < y; i++) {
	      for(int j = 0; j < x; j++) {
		b2BodyDef bd;
		bd.position.Set(j, s.worldHeight - i);
		b2FixtureDef fd;
		fd.friction = 0.3;
		f2 >> A[i][j];
		if(A[i][j] == 0){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		}
		if(A[i][j] == 2){
		  tiles[i][j]->setFillColor(sf::Color::White);
		}
		if(A[i][j] == 1){
		  tiles[i][j]->setFillColor(sf::Color(128, 128, 128, 255));
		}
		if(A[i][j] == 3){
		  tiles[i][j]->setFillColor(sf::Color::Black);
		}
		if(A[i][j] <= 200 && A[i][j] >= 100){
		  tiles[i][j]->setFillColor(sf::Color::Yellow);
		}
		if(A[i][j] == 10){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  std::vector<std::pair<float,float>> bodyVertices = {
		    std::make_pair(0.0, -1.5),
		    std::make_pair(-1.0, -1.3),
		    std::make_pair(-2.0, -0.0),
		    std::make_pair(-1.4, 0.5),
		    std::make_pair(-0.4, 1.1),
		    std::make_pair(1.0, 1.5),
		    std::make_pair(2.0, 0.9),
		    std::make_pair(1.0, -0.7)
		  };
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
		}
		/*if(A[i][j] = 11) {
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  std::vector<std::pair<float,float>> bodyVertices = {
		    std::make_pair(1.0, -2.0),
		    std::make_pair(0.0, -1.5),
		    std::make_pair(-1.0, -0.7),
		    std::make_pair(-2.0, 0.0),
		    std::make_pair(-2.0, 0.5),
		    std::make_pair(-1.0, 1.0),
		    std::make_pair(0.5, 2.2),
		    std::make_pair(2.0, -0.5)
		  };
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
		}*/
		if(A[i][j] == 12){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  std::vector<std::pair<float,float>> bodyVertices = {
		    std::make_pair(0.0, -3.0),
		    std::make_pair(-2.0, -2.6),
		    std::make_pair(-4.0, -0.0),
		    std::make_pair(-2.8, 1.0),
		    std::make_pair(-0.8, 2.2),
		    std::make_pair(2.0, 3.0),
		    std::make_pair(4.0, 1.8),
		    std::make_pair(2.0, -1.4)
		  };
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
		}
		if(A[i][j] == 13){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  std::vector<std::pair<float,float>> bodyVertices = {
		    std::make_pair(2.0, -4.0),
		    std::make_pair(0.0, -3.0),
		    std::make_pair(-2.0, -1.4),
		    std::make_pair(-4.0, 0.0),
		    std::make_pair(-4.0, 1.0),
		    std::make_pair(-2.0, 2.0),
		    std::make_pair(1.0, 4.4),
		    std::make_pair(4.0, -1.0)
		  };
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
		}
		if(A[i][j] == 20){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255)));
		}
		if(A[i][j] == 21){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(1, 20), bd, fd, sf::Color(160,160,160,255)));
		}
		if(A[i][j] == 22){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
		  physObjPtr->getBody()->SetTransform(b2Vec2(j, s.worldHeight-i), -45.0 * DEGTORAD);
		  obstacles.push_back(physObjPtr);
		}
		if(A[i][j] == 23){
		  tiles[i][j]->setFillColor(sf::Color(0, 123, 12, 255));
		  auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
		  physObjPtr->getBody()->SetTransform(b2Vec2(j, s.worldHeight-i), 45.0 * DEGTORAD);
		  obstacles.push_back(physObjPtr);
		}
	      }
	    }
	    break;
	  default:
	    // Empty default case included to stop compiler from giving warnings.
	    break;
	  }
	  break;
      }
      default:
	break;
      }
    }

    //Checking which tile the cursor is located at
    sf::Vector2i mpos = sf::Mouse::getPosition (w);
    int x2 = floor(mpos.x/boxwidth);
    int y2 = floor(mpos.y/boxwidth);

    if (x2 >= 0 && x2<x && y2 >= 0 && y2 < y) {
      // Default settings for all static obstacles
      b2BodyDef bd;
      bd.position.Set(x2, s.worldHeight - y2);
      b2FixtureDef fd;
      fd.friction = 0.3;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 0;
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
	tiles[y2][x2]->setFillColor(sf::Color(128, 128, 128, 255));
	tiles[y2][x2]->setRotation(0);
	A[y2][x2] = 1;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
	  tiles[y2][x2]->setFillColor(sf::Color::White);
	  tiles[y2][x2]->setRotation(0);			
	  A[y2][x2] = 2;	  
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 10;

	  std::vector<std::pair<float,float>> bodyVertices = {
	    std::make_pair(0.0, -1.5),
	    std::make_pair(-1.0, -1.3),
	    std::make_pair(-2.0, -0.0),
	    std::make_pair(-1.4, 0.5),
	    std::make_pair(-0.4, 1.1),
	    std::make_pair(1.0, 1.5),
	    std::make_pair(2.0, 0.9),
	    std::make_pair(1.0, -0.7)
	  };
	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 11;

	    std::vector<std::pair<float,float>> bodyVertices = {
	      std::make_pair(1.0, -2.0),
	      std::make_pair(0.0, -1.5),
	      std::make_pair(-1.0, -0.7),
	      std::make_pair(-2.0, 0.0),
	      std::make_pair(-2.0, 0.5),
	      std::make_pair(-1.0, 1.0),
	      std::make_pair(0.5, 2.2),
	      std::make_pair(2.0, -0.5)
	  };
	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
	}

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 12;

	  std::vector<std::pair<float,float>> bodyVertices = {
	    std::make_pair(0.0, -3.0),
	    std::make_pair(-2.0, -2.6),
	    std::make_pair(-4.0, -0.0),
	    std::make_pair(-2.8, 1.0),
	    std::make_pair(-0.8, 2.2),
	    std::make_pair(2.0, 3.0),
	    std::make_pair(4.0, 1.8),
	    std::make_pair(2.0, -1.4)
	  };
	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 13;

	  std::vector<std::pair<float,float>> bodyVertices = {
	    std::make_pair(2.0, -4.0),
	    std::make_pair(0.0, -3.0),
	    std::make_pair(-2.0, -1.4),
	    std::make_pair(-4.0, 0.0),
	    std::make_pair(-4.0, 1.0),
	    std::make_pair(-2.0, 2.0),
	    std::make_pair(1.0, 4.4),
	    std::make_pair(4.0, -1.0)
	  };
	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));

	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 20;

	  auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255)));
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 21;

	  obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(1, 20), bd, fd, sf::Color(160,160,160,255)));
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 22;

	  auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
	  physObjPtr->getBody()->SetTransform(b2Vec2(x2, s.worldHeight-y2), -45.0 * DEGTORAD);
	  obstacles.push_back(physObjPtr);
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash))
	{
	  tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 23;

	  auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
	  physObjPtr->getBody()->SetTransform(b2Vec2(x2, s.worldHeight-y2), 45.0 * DEGTORAD);
	  obstacles.push_back(physObjPtr);
	}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
	  tiles[y2][x2]->setFillColor(sf::Color::Yellow);
	  tiles[y2][x2]->setRotation(0);
	  if(A[y2][x2] < 100){
	    A[y2][x2] = checkpoint;
	    checkpoint += 1;
	  }
	}
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
	  tiles[y2][x2]->setFillColor(sf::Color::Black);
	  tiles[y2][x2]->setRotation(0);
	  A[y2][x2] = 3;
	}
    }
	
    // Clear previously displayed window, draw the new positions
  
    w.clear();
        
    for(int i = 0; i < y; i++)
      {
	for(int j = 0; j < x; j++)
	  {
	    w.draw(*tiles[i][j]);
	  }
      }
        
    for(auto i: obstacles)
      i->drawTo(w);

    w.display();
  }
  for (int i = 0; i < y; i++)
  {
    for (int j = 0; j < x; j++)
    {
      delete tiles[i][j];
    }
  }
  return 0;
}

// We enter this function from the options-window, when the user clicks on some key of some player.
int WaitForKey(sf::RenderWindow &w, Player &p, int x, std::map<sf::Keyboard::Key, std::string> K)
{
  sf::Event e;
  while (1)
    {
      while (w.pollEvent(e)) // Poll for events.
	{
	  if (e.type == sf::Event::KeyPressed) // If some keyboard key is pressed.
	    {
	      if (K.count(e.key.code) != 0) // If the pressed key can be found in the map K (std::map Keys in Options-window)
		{
		  if (x == 1) // If we want to modify the up-key of a player.
		    {
		      p.getKeys().up = e.key.code;
		      return 1;
		    }
		  else if (x == 2) // If we want to modify the down-key of a player.
		    {
		      p.getKeys().down = e.key.code;
		      return 1;
		    }
		  else if (x == 3) // If we want to modify the left-key of a player.
		    {
		      p.getKeys().left = e.key.code;
		      return 1;
		    }
		  else if (x == 4) // If we want to modify the right-key of a player.
		    {
		      p.getKeys().right = e.key.code;
		      return 1;
		    }
		}
	    }
	}
    }
}
