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


// This loop controls the window in which the user chooses map etc. befor starting the game.
int StartWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  w.setFramerateLimit(60);
  // Create a vector playerKeys that contains keys of all the players. This is used to check that all keys are unqiue, that is, that many players do not try to use same keys.
  std::vector<sf::Keyboard::Key> playerKeys {p1.getKeys().up, p1.getKeys().down, p1.getKeys().left, p1.getKeys().right, p2.getKeys().up, p2.getKeys().down, p2.getKeys().left, p2.getKeys().right,
      p3.getKeys().up, p3.getKeys().down, p3.getKeys().left, p3.getKeys().right, p4.getKeys().up, p4.getKeys().down, p4.getKeys().left, p4.getKeys().right};
  std::sort(playerKeys.begin(), playerKeys.end()); // Sort the vectror playerKeys.
  int var = 0;
  int numOfPlayers = 1;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  // Create some texts.
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text StartButton("Start", f, 100);
  sf::Text Heading1("Number of player", f, 80);
  sf::Text Lkm1("1", f, 80);
  sf::Text Lkm2("2", f, 80);
  sf::Text Lkm3("3", f, 80);
  sf::Text Lkm4("4", f, 80);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  StartButton.setColor(sf::Color::Black);
  Heading1.setColor(sf::Color::Red);
  Lkm1.setColor(sf::Color::Black);
  Lkm2.setColor(sf::Color::Black);
  Lkm3.setColor(sf::Color::Black);
  Lkm4.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  StartButton.setPosition(w.getSize().x/2-StartButton.getLocalBounds().width/2, w.getSize().y/2-StartButton.getLocalBounds().height/2);
  Heading1.setPosition(w.getSize().x/5.5-Heading1.getLocalBounds().width/2, w.getSize().y/9-Heading1.getLocalBounds().height);
  Lkm1.setPosition(w.getSize().x/5.5-Lkm1.getLocalBounds().width/2, w.getSize().y/5-Lkm1.getLocalBounds().height);
  Lkm2.setPosition(w.getSize().x/5.5-Lkm2.getLocalBounds().width/2, w.getSize().y/3-Lkm2.getLocalBounds().height);
  Lkm3.setPosition(w.getSize().x/5.5-Lkm3.getLocalBounds().width/2, w.getSize().y/2.1-Lkm3.getLocalBounds().height);
  Lkm4.setPosition(w.getSize().x/5.5-Lkm4.getLocalBounds().width/2, w.getSize().y/1.6-Lkm4.getLocalBounds().height);

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
      if (MousePosX >= Lkm1.getPosition().x && MousePosX <= Lkm1.getPosition().x+Lkm1.getLocalBounds().width && MousePosY >= Lkm1.getPosition().y && MousePosY <= Lkm1.getPosition().y+Lkm1.getLocalBounds().height)
	{
	  Lkm1.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm1.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm2.getPosition().x && MousePosX <= Lkm2.getPosition().x+Lkm2.getLocalBounds().width && MousePosY >= Lkm2.getPosition().y && MousePosY <= Lkm2.getPosition().y+Lkm2.getLocalBounds().height)
	{
	  Lkm2.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm2.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm3.getPosition().x && MousePosX <= Lkm3.getPosition().x+Lkm3.getLocalBounds().width && MousePosY >= Lkm3.getPosition().y && MousePosY <= Lkm3.getPosition().y+Lkm3.getLocalBounds().height)
	{
	  Lkm3.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm3.setColor(sf::Color::Black);
	}
      if (MousePosX >= Lkm4.getPosition().x && MousePosX <= Lkm4.getPosition().x+Lkm4.getLocalBounds().width && MousePosY >= Lkm4.getPosition().y && MousePosY <= Lkm4.getPosition().y+Lkm4.getLocalBounds().height)
	{
	  Lkm4.setColor(sf::Color::Red);
	}
      else
	{
	  Lkm4.setColor(sf::Color::Black);
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
		      std::cout << numOfPlayers << std::endl;
		      return numOfPlayers; // This return value tells the menu()-function to start the game.
		    }
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm1.getPosition().x && MousePosX <= Lkm1.getPosition().x+Lkm1.getLocalBounds().width && MousePosY >= Lkm1.getPosition().y && MousePosY <= Lkm1.getPosition().y+Lkm1.getLocalBounds().height)
		{
		  Lkm1.setColor(sf::Color::Red);
		  numOfPlayers = 1;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm2.getPosition().x && MousePosX <= Lkm2.getPosition().x+Lkm2.getLocalBounds().width && MousePosY >= Lkm2.getPosition().y && MousePosY <= Lkm2.getPosition().y+Lkm2.getLocalBounds().height)
		{
		  Lkm2.setColor(sf::Color::Red);
		  numOfPlayers = 2;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm3.getPosition().x && MousePosX <= Lkm3.getPosition().x+Lkm3.getLocalBounds().width && MousePosY >= Lkm3.getPosition().y && MousePosY <= Lkm3.getPosition().y+Lkm3.getLocalBounds().height)
		{
		  Lkm3.setColor(sf::Color::Red);
		  numOfPlayers = 3;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Lkm4.getPosition().x && MousePosX <= Lkm4.getPosition().x+Lkm4.getLocalBounds().width && MousePosY >= Lkm4.getPosition().y && MousePosY <= Lkm4.getPosition().y+Lkm4.getLocalBounds().height)
		{
		  Lkm4.setColor(sf::Color::Red);
		  numOfPlayers = 4;
		}
	    default:
	      break;
	    }
	  if (var == 1)
	    {
	      return 0;
	    }
	}
      // Draw some textures.
      w.clear(sf::Color::White);
      w.draw(ReturnButton);
      w.draw(ExitButton);
      w.draw(StartButton);
      w.draw(Heading1);
      w.draw(Lkm1);
      w.draw(Lkm2);
      w.draw(Lkm3);
      w.draw(Lkm4);
      w.display();
    }
  return 0;
}

// We will enter this function when the user clicks on the Options-button in the first menu-screen.
int OptionsWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  w.setFramerateLimit(60);
  //int select = -1; // This variable is used to control whose controls are being changed.
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  std::map <sf::Keyboard::Key, std::string> Keys{{sf::Keyboard::Q, "Q"}, {sf::Keyboard::W, "W"}, {sf::Keyboard::E, "E"}, {sf::Keyboard::R, "R"}, {sf::Keyboard::T, "T"},
					         {sf::Keyboard::Y, "Y"}, {sf::Keyboard::U, "U"}, {sf::Keyboard::I, "I"}, {sf::Keyboard::O, "O"}, {sf::Keyboard::P, "P"},
						 {sf::Keyboard::A, "A"}, {sf::Keyboard::S, "S"}, {sf::Keyboard::D, "D"}, {sf::Keyboard::F, "F"}, {sf::Keyboard::G, "G"},
						 {sf::Keyboard::H, "H"}, {sf::Keyboard::J, "J"}, {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"}, {sf::Keyboard::Z, "Z"},
						 {sf::Keyboard::X, "X"}, {sf::Keyboard::C, "C"}, {sf::Keyboard::V, "V"}, {sf::Keyboard::B, "B"}, {sf::Keyboard::N, "N"},
						 {sf::Keyboard::M, "M"}, {sf::Keyboard::Up, "Up Arrow"}, {sf::Keyboard::Down, "Down Arrow"}, {sf::Keyboard::Left, "Left Arrow"},
						 {sf::Keyboard::Right, "Right Arrow"}, {sf::Keyboard::Numpad0, "0"}, {sf::Keyboard::Numpad1, "1"}, {sf::Keyboard::Numpad2, "2"},
						 {sf::Keyboard::Numpad3, "3"}, {sf::Keyboard::Numpad4, "4"}, {sf::Keyboard::Numpad5, "5"}, {sf::Keyboard::Numpad6, "6"},
						 {sf::Keyboard::Numpad7, "7"}, {sf::Keyboard::Numpad8, "8"}, {sf::Keyboard::Numpad9, "9"}};
  // Create some texts.
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

  while (w.isOpen()) // This is the actual game loop.
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
	  ReturnButton.setColor(sf::Color::Black);
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
      if (MousePosX >= p1up.getPosition().x && MousePosX <= p1up.getPosition().x+p1up.getLocalBounds().width && MousePosY >= p1up.getPosition().y && MousePosY <= p1up.getPosition().y+p1up.getLocalBounds().height)
	{
	  p1up.setColor(sf::Color::Blue);
	}
      else
	{
	  p1up.setColor(sf::Color::Black);
	}
      if (MousePosX >= p1down.getPosition().x && MousePosX <= p1down.getPosition().x+p1down.getLocalBounds().width && MousePosY >= p1down.getPosition().y && MousePosY <= p1down.getPosition().y+p1down.getLocalBounds().height)
	{
	  p1down.setColor(sf::Color::Blue);
	}
      else
	{
	  p1down.setColor(sf::Color::Black);
	}
      if (MousePosX >= p1left.getPosition().x && MousePosX <= p1left.getPosition().x+p1left.getLocalBounds().width && MousePosY >= p1left.getPosition().y && MousePosY <= p1left.getPosition().y+p1left.getLocalBounds().height)
	{
	  p1left.setColor(sf::Color::Blue);
	}
      else
	{
	  p1left.setColor(sf::Color::Black);
	}
      if (MousePosX >= p1right.getPosition().x && MousePosX <= p1right.getPosition().x+p1right.getLocalBounds().width && MousePosY >= p1right.getPosition().y && MousePosY <= p1right.getPosition().y+p1right.getLocalBounds().height)
	{
	  p1right.setColor(sf::Color::Blue);
	}
      else
	{
	  p1right.setColor(sf::Color::Black);
	}
      if (MousePosX >= p2up.getPosition().x && MousePosX <= p2up.getPosition().x+p2up.getLocalBounds().width && MousePosY >= p2up.getPosition().y && MousePosY <= p2up.getPosition().y+p2up.getLocalBounds().height)
	{
	  p2up.setColor(sf::Color::Blue);
	}
      else
	{
	  p2up.setColor(sf::Color::Black);
	}
      if (MousePosX >= p2down.getPosition().x && MousePosX <= p2down.getPosition().x+p2down.getLocalBounds().width && MousePosY >= p2down.getPosition().y && MousePosY <= p2down.getPosition().y+p2down.getLocalBounds().height)
	{
	  p2down.setColor(sf::Color::Blue);
	}
      else
	{
	  p2down.setColor(sf::Color::Black);
	}
      if (MousePosX >= p2left.getPosition().x && MousePosX <= p2left.getPosition().x+p2left.getLocalBounds().width && MousePosY >= p2left.getPosition().y && MousePosY <= p2left.getPosition().y+p2left.getLocalBounds().height)
	{
	  p2left.setColor(sf::Color::Blue);
	}
      else
	{
	  p2left.setColor(sf::Color::Black);
	}
      if (MousePosX >= p2right.getPosition().x && MousePosX <= p2right.getPosition().x+p2right.getLocalBounds().width && MousePosY >= p2right.getPosition().y && MousePosY <= p2right.getPosition().y+p2right.getLocalBounds().height)
	{
	  p2right.setColor(sf::Color::Blue);
	}
      else
	{
	  p2right.setColor(sf::Color::Black);
	}
      if (MousePosX >= p3up.getPosition().x && MousePosX <= p3up.getPosition().x+p3up.getLocalBounds().width && MousePosY >= p3up.getPosition().y && MousePosY <= p3up.getPosition().y+p3up.getLocalBounds().height)
	{
	  p3up.setColor(sf::Color::Blue);
	}
      else
	{
	  p3up.setColor(sf::Color::Black);
	}
      if (MousePosX >= p3down.getPosition().x && MousePosX <= p3down.getPosition().x+p3down.getLocalBounds().width && MousePosY >= p3down.getPosition().y && MousePosY <= p3down.getPosition().y+p3down.getLocalBounds().height)
	{
	  p3down.setColor(sf::Color::Blue);
	}
      else
	{
	  p3down.setColor(sf::Color::Black);
	}
      if (MousePosX >= p3left.getPosition().x && MousePosX <= p3left.getPosition().x+p3left.getLocalBounds().width && MousePosY >= p3left.getPosition().y && MousePosY <= p3left.getPosition().y+p3left.getLocalBounds().height)
	{
	  p3left.setColor(sf::Color::Blue);
	}
      else
	{
	  p3left.setColor(sf::Color::Black);
	}
      if (MousePosX >= p3right.getPosition().x && MousePosX <= p3right.getPosition().x+p3right.getLocalBounds().width && MousePosY >= p3right.getPosition().y && MousePosY <= p3right.getPosition().y+p3right.getLocalBounds().height)
	{
	  p3right.setColor(sf::Color::Blue);
	}
      else
	{
	  p3right.setColor(sf::Color::Black);
	}
      if (MousePosX >= p4up.getPosition().x && MousePosX <= p4up.getPosition().x+p4up.getLocalBounds().width && MousePosY >= p4up.getPosition().y && MousePosY <= p4up.getPosition().y+p4up.getLocalBounds().height)
	{
	  p4up.setColor(sf::Color::Blue);
	}
      else
	{
	  p4up.setColor(sf::Color::Black);
	}
      if (MousePosX >= p4down.getPosition().x && MousePosX <= p4down.getPosition().x+p4down.getLocalBounds().width && MousePosY >= p4down.getPosition().y && MousePosY <= p4down.getPosition().y+p4down.getLocalBounds().height)
	{
	  p4down.setColor(sf::Color::Blue);
	}
      else
	{
	  p4down.setColor(sf::Color::Black);
	}
      if (MousePosX >= p4left.getPosition().x && MousePosX <= p4left.getPosition().x+p4left.getLocalBounds().width && MousePosY >= p4left.getPosition().y && MousePosY <= p4left.getPosition().y+p4left.getLocalBounds().height)
	{
	  p4left.setColor(sf::Color::Blue);
	}
      else
	{
	  p4left.setColor(sf::Color::Black);
	}
      if (MousePosX >= p4right.getPosition().x && MousePosX <= p4right.getPosition().x+p4right.getLocalBounds().width && MousePosY >= p4right.getPosition().y && MousePosY <= p4right.getPosition().y+p4right.getLocalBounds().height)
	{
	  p4right.setColor(sf::Color::Blue);
	}
      else
	{
	  p4right.setColor(sf::Color::Black);
	}
      
      
      while (w.pollEvent(e)) // Loop through all events.
	{
	  switch (e.type)
	    {
	    case sf::Event::Closed:
	      w.close();
	      break;

	    case sf::Event::KeyPressed:
	      switch(e.key.code)
		{
		case sf::Keyboard::Escape:
		  w.close();
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
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1up.getPosition().x && MousePosX <= p1up.getPosition().x+p1up.getLocalBounds().width && MousePosY >= p1up.getPosition().y && MousePosY <= p1up.getPosition().y+p1up.getLocalBounds().height)
		{
		  p1up.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 1, Keys);
		  p1up.setString(Keys.at(p1.getKeys().up));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1down.getPosition().x && MousePosX <= p1down.getPosition().x+p1down.getLocalBounds().width && MousePosY >= p1down.getPosition().y && MousePosY <= p1down.getPosition().y+p1down.getLocalBounds().height)
		{
		  p1down.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 2, Keys);
		  p1down.setString(Keys.at(p1.getKeys().down));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1left.getPosition().x && MousePosX <= p1left.getPosition().x+p1left.getLocalBounds().width && MousePosY >= p1left.getPosition().y && MousePosY <= p1left.getPosition().y+p1left.getLocalBounds().height)
		{
		  p1left.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 3, Keys);
		  p1left.setString(Keys.at(p1.getKeys().left));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p1right.getPosition().x && MousePosX <= p1right.getPosition().x+p1right.getLocalBounds().width && MousePosY >= p1right.getPosition().y && MousePosY <= p1right.getPosition().y+p1right.getLocalBounds().height)
		{
		  p1right.setColor(sf::Color::Blue);
		  WaitForKey(w, p1, 4, Keys);
		  p1right.setString(Keys.at(p1.getKeys().right));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2up.getPosition().x && MousePosX <= p2up.getPosition().x+p2up.getLocalBounds().width && MousePosY >= p2up.getPosition().y && MousePosY <= p2up.getPosition().y+p2up.getLocalBounds().height)
		{
		  p2up.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 1, Keys);
		  p2up.setString(Keys.at(p2.getKeys().up));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2down.getPosition().x && MousePosX <= p2down.getPosition().x+p2down.getLocalBounds().width && MousePosY >= p2down.getPosition().y && MousePosY <= p2down.getPosition().y+p2down.getLocalBounds().height)
		{
		  p2down.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 2, Keys);
		  p2down.setString(Keys.at(p2.getKeys().down));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2left.getPosition().x && MousePosX <= p2left.getPosition().x+p2left.getLocalBounds().width && MousePosY >= p2left.getPosition().y && MousePosY <= p2left.getPosition().y+p2left.getLocalBounds().height)
		{
		  p2left.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 3, Keys);
		  p2left.setString(Keys.at(p2.getKeys().left));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p2right.getPosition().x && MousePosX <= p2right.getPosition().x+p2right.getLocalBounds().width && MousePosY >= p2right.getPosition().y && MousePosY <= p2right.getPosition().y+p2right.getLocalBounds().height)
		{
		  p2right.setColor(sf::Color::Blue);
		  WaitForKey(w, p2, 4, Keys);
		  p2right.setString(Keys.at(p2.getKeys().right));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3up.getPosition().x && MousePosX <= p3up.getPosition().x+p3up.getLocalBounds().width && MousePosY >= p3up.getPosition().y && MousePosY <= p3up.getPosition().y+p3up.getLocalBounds().height)
		{
		  p3up.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 1, Keys);
		  p3up.setString(Keys.at(p3.getKeys().up));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3down.getPosition().x && MousePosX <= p3down.getPosition().x+p3down.getLocalBounds().width && MousePosY >= p3down.getPosition().y && MousePosY <= p3down.getPosition().y+p3down.getLocalBounds().height)
		{
		  p3down.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 2, Keys);
		  p3down.setString(Keys.at(p3.getKeys().down));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3left.getPosition().x && MousePosX <= p3left.getPosition().x+p3left.getLocalBounds().width && MousePosY >= p3left.getPosition().y && MousePosY <= p3left.getPosition().y+p3left.getLocalBounds().height)
		{
		  p3left.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 3, Keys);
		  p3left.setString(Keys.at(p3.getKeys().left));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p3right.getPosition().x && MousePosX <= p3right.getPosition().x+p3right.getLocalBounds().width && MousePosY >= p3right.getPosition().y && MousePosY <= p3right.getPosition().y+p3right.getLocalBounds().height)
		{
		  p3right.setColor(sf::Color::Blue);
		  WaitForKey(w, p3, 4, Keys);
		  p3right.setString(Keys.at(p3.getKeys().right));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4up.getPosition().x && MousePosX <= p4up.getPosition().x+p4up.getLocalBounds().width && MousePosY >= p4up.getPosition().y && MousePosY <= p4up.getPosition().y+p4up.getLocalBounds().height)
		{
		  p4up.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 1, Keys);
		  p4up.setString(Keys.at(p4.getKeys().up));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4down.getPosition().x && MousePosX <= p4down.getPosition().x+p4down.getLocalBounds().width && MousePosY >= p4down.getPosition().y && MousePosY <= p4down.getPosition().y+p4down.getLocalBounds().height)
		{
		  p4down.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 2, Keys);
		  p4down.setString(Keys.at(p4.getKeys().down));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4left.getPosition().x && MousePosX <= p4left.getPosition().x+p4left.getLocalBounds().width && MousePosY >= p4left.getPosition().y && MousePosY <= p4left.getPosition().y+p4left.getLocalBounds().height)
		{
		  p4left.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 3, Keys);
		  p4left.setString(Keys.at(p4.getKeys().left));
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= p4right.getPosition().x && MousePosX <= p4right.getPosition().x+p4right.getLocalBounds().width && MousePosY >= p4right.getPosition().y && MousePosY <= p4right.getPosition().y+p4right.getLocalBounds().height)
		{
		  p4right.setColor(sf::Color::Blue);
		  WaitForKey(w, p4, 4, Keys);
		  p4right.setString(Keys.at(p4.getKeys().right));
		}
	    }
	  if (var == 1)
	    {
	      return 0;
	    }
	}
      w.clear(sf::Color::White);
      w.draw(ReturnButton);
      w.draw(ExitButton);
      w.draw(Up);
      w.draw(Down);
      w.draw(Left);
      w.draw(Right);
      w.draw(p1up);
      w.draw(p1down);
      w.draw(p1left);
      w.draw(p1right);
      w.draw(p2up);
      w.draw(p2down);
      w.draw(p2left);
      w.draw(p2right);
      w.draw(p3up);
      w.draw(p3down);
      w.draw(p3left);
      w.draw(p3right);
      w.draw(p4up);
      w.draw(p4down);
      w.draw(p4left);
      w.draw(p4right);
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
  //std::ofstream f("./Level/map1.txt");
    
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
			      w.close();
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
			      w.close();
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
	  case sf::Keyboard::S: //Saves matrix to the file "level1.txt"
	    for(int i = 0; i < y; i++) {
	      for(int j = 0; j < x; j++) {
		f << A[i][j] << " ";
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
      i->drawTo(w,s);

    w.display();
  }
  return 0;
}

int WaitForKey(sf::RenderWindow &w, Player &p, int x, std::map<sf::Keyboard::Key, std::string> K)
{
  sf::Event e;
  while (1)
    {
      while (w.pollEvent(e))
	{
	  if (e.type == sf::Event::KeyPressed)
	    {
	      if (K.count(e.key.code) != 0)
		{
		  if (x == 1)
		    {
		      p.getKeys().up = e.key.code;
		      return 1;
		    }
		  else if (x == 2)
		    {
		      p.getKeys().down = e.key.code;
		      return 1;
		    }
		  else if (x == 3)
		    {
		      p.getKeys().left = e.key.code;
		      return 1;
		    }
		  else if (x == 4)
		    {
		      p.getKeys().right = e.key.code;
		      return 1;
		    }
		}
	    }
	}
    }
}
