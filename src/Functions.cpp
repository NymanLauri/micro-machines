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
		      return 1; // This return value tells the menu()-function to start the game.
		    }
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
  int select = -1; // This variable is used to control whose controls are being changed.
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Event e;
  // Create some texts.
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text Player1Opts("Player 1", f, 80);
  sf::Text Player2Opts("Player 2", f, 80);
  sf::Text Player3Opts("Player 3", f, 80);
  sf::Text Player4Opts("Player 4", f, 80);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  Player1Opts.setColor(sf::Color::Black);
  Player2Opts.setColor(sf::Color::Black);
  Player3Opts.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  Player1Opts.setPosition(w.getSize().x/7.5-Player1Opts.getLocalBounds().width/2, w.getSize().y-Player1Opts.getLocalBounds().height*13);
  Player2Opts.setPosition(w.getSize().x/7.5-Player2Opts.getLocalBounds().width/2, w.getSize().y-Player2Opts.getLocalBounds().height*11);
  Player3Opts.setPosition(w.getSize().x/7.5-Player3Opts.getLocalBounds().width/2, w.getSize().y-Player3Opts.getLocalBounds().height*9);
  Player4Opts.setPosition(w.getSize().x/7.5-Player4Opts.getLocalBounds().width/2, w.getSize().y-Player4Opts.getLocalBounds().height*7);

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

      if (MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 && MousePosY >= Player1Opts.getPosition().y*1.03 &&
	  MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 1"-button.
	{
	  Player1Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player1Opts.setColor(sf::Color::Black);
	}

      if (MousePosX >= Player2Opts.getPosition().x*1.01 && MousePosX <= Player2Opts.getPosition().x+Player2Opts.getLocalBounds().width*1.1 && MousePosY >= Player2Opts.getPosition().y*1.03 &&
	  MousePosY <= Player2Opts.getPosition().y+Player2Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 2"-button.
	{
	  Player2Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player2Opts.setColor(sf::Color::Black);
	}

      if (MousePosX >= Player3Opts.getPosition().x*1.01 && MousePosX <= Player3Opts.getPosition().x+Player3Opts.getLocalBounds().width*1.1 && MousePosY >= Player3Opts.getPosition().y*1.03 &&
	  MousePosY <= Player3Opts.getPosition().y+Player3Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 3"-button.
	{
	  Player3Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player3Opts.setColor(sf::Color::Black);
	}

      if (MousePosX >= Player4Opts.getPosition().x*1.01 && MousePosX <= Player4Opts.getPosition().x+Player4Opts.getLocalBounds().width*1.1 && MousePosY >= Player4Opts.getPosition().y*1.03 &&
	  MousePosY <= Player4Opts.getPosition().y+Player4Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 3"-button.
	{
	  Player4Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player4Opts.setColor(sf::Color::Black);
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
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 &&
		       MousePosY >= Player1Opts.getPosition().y*1.03 && MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 1"-button.
		{
		  select = 1;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player2Opts.getPosition().x*1.01 && MousePosX <= Player2Opts.getPosition().x+Player2Opts.getLocalBounds().width*1.1 &&
		       MousePosY >= Player2Opts.getPosition().y*1.03 && MousePosY <= Player2Opts.getPosition().y+Player2Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 2"-button.
		{
		  select = 2;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player3Opts.getPosition().x*1.01 && MousePosX <= Player3Opts.getPosition().x+Player3Opts.getLocalBounds().width*1.1 &&
		       MousePosY >= Player3Opts.getPosition().y*1.03 && MousePosY <= Player3Opts.getPosition().y+Player3Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 2"-button.
		{
		  select = 3;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player4Opts.getPosition().x*1.01 && MousePosX <= Player4Opts.getPosition().x+Player4Opts.getLocalBounds().width*1.1 &&
		       MousePosY >= Player4Opts.getPosition().y*1.03 && MousePosY <= Player4Opts.getPosition().y+Player4Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 2"-button.
		{
		  select = 4;
		}
	      
	      if (select != -1) // If the user had clicked on some "player i"-button. select 1 = player 1, select 2 = player 2, select 3 = player 3, select 4 = player 4.
		{
		  // Std::map Keys contains pairs, each of which containing a key that is allowed to be used as a control for the player and a string representing that key.
		  // This is used to draw to the screen the key that is currently used for each player.
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
		  sf::Text Return("Return", f, 100);
		  sf::Text UpKey("None", f, 80);
		  sf::Text DownKey("None", f, 80);
		  sf::Text LeftKey("None", f, 80);
		  sf::Text RightKey("None", f, 80);
		  // Set the strings and positions of texts according to whose controls we are modifying.
		  if (select == 1)
		    {
		      UpKey.setString(Keys.at(p1.getKeys().up));
		      DownKey.setString(Keys.at(p1.getKeys().down));
		      LeftKey.setString(Keys.at(p1.getKeys().left));
		      RightKey.setString(Keys.at(p1.getKeys().right));
		      UpKey.setPosition(w.getSize().x/3-UpKey.getLocalBounds().width/2, w.getSize().y/2-UpKey.getLocalBounds().height*5.5);
		      DownKey.setPosition(w.getSize().x/3-DownKey.getLocalBounds().width/2, w.getSize().y/2-DownKey.getLocalBounds().height*4.5);
		      LeftKey.setPosition(w.getSize().x/3-LeftKey.getLocalBounds().width/2, w.getSize().y/1.5-LeftKey.getLocalBounds().height*4.8);
		      RightKey.setPosition(w.getSize().x/3-RightKey.getLocalBounds().width/2, w.getSize().y/1.5-RightKey.getLocalBounds().height*1.8);
		    }
		  else if (select == 2)
		    {
		      UpKey.setString(Keys.at(p2.getKeys().up));
		      DownKey.setString(Keys.at(p2.getKeys().down));
		      LeftKey.setString(Keys.at(p2.getKeys().left));
		      RightKey.setString(Keys.at(p2.getKeys().right));
		      UpKey.setPosition(w.getSize().x/3-UpKey.getLocalBounds().width/2, w.getSize().y/2-UpKey.getLocalBounds().height*7);
		      DownKey.setPosition(w.getSize().x/3-DownKey.getLocalBounds().width/2, w.getSize().y/2-DownKey.getLocalBounds().height*4.5);
		      LeftKey.setPosition(w.getSize().x/3-LeftKey.getLocalBounds().width/2, w.getSize().y/2-LeftKey.getLocalBounds().height*2);
		      RightKey.setPosition(w.getSize().x/3-RightKey.getLocalBounds().width/2, w.getSize().y/1.8-RightKey.getLocalBounds().height*0.5);
		    }
		  else if (select == 3)
		    {
		      UpKey.setString(Keys.at(p3.getKeys().up));
		      DownKey.setString(Keys.at(p3.getKeys().down));
		      LeftKey.setString(Keys.at(p3.getKeys().left));
		      RightKey.setString(Keys.at(p3.getKeys().right));
		      UpKey.setPosition(w.getSize().x/3-UpKey.getLocalBounds().width/2, w.getSize().y/2-UpKey.getLocalBounds().height*7);
		      DownKey.setPosition(w.getSize().x/3-DownKey.getLocalBounds().width/2, w.getSize().y/2-DownKey.getLocalBounds().height*4.5);
		      LeftKey.setPosition(w.getSize().x/3-LeftKey.getLocalBounds().width/2, w.getSize().y/2-LeftKey.getLocalBounds().height*2);
		      RightKey.setPosition(w.getSize().x/3-RightKey.getLocalBounds().width/2, w.getSize().y/1.8-RightKey.getLocalBounds().height*0.5);
		    }
		  else if (select == 4)
		    {
		      UpKey.setString(Keys.at(p4.getKeys().up));
		      DownKey.setString(Keys.at(p4.getKeys().down));
		      LeftKey.setString(Keys.at(p4.getKeys().left));
		      RightKey.setString(Keys.at(p4.getKeys().right));
		      UpKey.setPosition(w.getSize().x/3-UpKey.getLocalBounds().width/2, w.getSize().y/2-UpKey.getLocalBounds().height*7);
		      DownKey.setPosition(w.getSize().x/3-DownKey.getLocalBounds().width/2, w.getSize().y/2-DownKey.getLocalBounds().height*4.5);
		      LeftKey.setPosition(w.getSize().x/3-LeftKey.getLocalBounds().width/2, w.getSize().y/2-LeftKey.getLocalBounds().height*2);
		      RightKey.setPosition(w.getSize().x/3-RightKey.getLocalBounds().width/2, w.getSize().y/1.8-RightKey.getLocalBounds().height*0.5);
		    }
		  sf::Text Up("Up", f, 80);
		  sf::Text Down("Down", f, 80);
		  sf::Text Left("Left", f, 80);
		  sf::Text Right("Right", f, 80);
		  sf::Text Controls("Controls", f, 80);
		  
		  Up.setColor(sf::Color::Black);
		  UpKey.setColor(sf::Color::Black);
		  DownKey.setColor(sf::Color::Black);
		  LeftKey.setColor(sf::Color::Black);
		  RightKey.setColor(sf::Color::Black);
		  Down.setColor(sf::Color::Black);
		  Left.setColor(sf::Color::Black);
		  Right.setColor(sf::Color::Black);
		  Return.setColor(sf::Color::Black);
		  Controls.setColor(sf::Color::Red);
		  Controls.setStyle(sf::Text::Underlined);
		  
		  Up.setPosition(w.getSize().x/9-Up.getLocalBounds().width/2, w.getSize().y/2-Up.getLocalBounds().height*5.5);
		  Down.setPosition(w.getSize().x/9-Down.getLocalBounds().width/2, w.getSize().y/2-Down.getLocalBounds().height*4.5);
		  Left.setPosition(w.getSize().x/9-Left.getLocalBounds().width/2, w.getSize().y/2-Left.getLocalBounds().height*1.8);
		  Right.setPosition(w.getSize().x/9-Right.getLocalBounds().width/2, w.getSize().y/1.65-Right.getLocalBounds().height);
		  Controls.setPosition(w.getSize().x/9-Controls.getLocalBounds().width/2, w.getSize().y/10-Controls.getLocalBounds().height/2*3);
		  Return.setPosition(w.getSize().x/6-Return.getLocalBounds().width/1.2, w.getSize().y-Return.getLocalBounds().height*2.5);
		  int var = 0;
		  while(1)
		    {
		      MousePosX = sf::Mouse::getPosition(w).x;
		      MousePosY = sf::Mouse::getPosition(w).y;
		      if (MousePosX >= Return.getPosition().x*1.01 && MousePosX <= Return.getPosition().x+Return.getLocalBounds().width*1.1 && MousePosY >= Return.getPosition().y*1.03 &&
			  MousePosY <= Return.getPosition().y+Return.getLocalBounds().height*1.5) // If the mouse is on top of Return-button.
			{
			  Return.setColor(sf::Color::Blue);
			}
		      else
			{
			  Return.setColor(sf::Color::Black);
			}
		      
		      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 &&
			  MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of Exit-button.
			{
			  ExitButton.setColor(sf::Color::Blue);
			}
		      else
			{
			  ExitButton.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 && MousePosY >= Up.getPosition().y*1.03 &&
			  MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5) // If the mouse is on top of Up-button.
			{
			  Up.setColor(sf::Color::Blue);
			}
		      else
			{
			  Up.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 && MousePosY >= Down.getPosition().y*1.03 &&
			  MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5) // If the mouse is on top of the Down-button.
			{
			  Down.setColor(sf::Color::Blue);
			}
		      else
			{
			  Down.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 && MousePosY >= Left.getPosition().y*1.03 &&
			  MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5) // If the mouse is on top of the Left-button.
			{
			  Left.setColor(sf::Color::Blue);
			}
		      else
			{
			  Left.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 && MousePosY >= Right.getPosition().y*1.03 &&
			  MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5) // If the mouse is on top of the Right-button.
			{
			  Right.setColor(sf::Color::Blue);
			}
		      else
			{
			  Right.setColor(sf::Color::Black);
			}

		      while (w.pollEvent(e)) // Loop through different events.
			{
			  switch(e.type)
			    {
			    case sf::Event::Closed:
			      w.close();
			      var = 1;
			      break;

			    case sf::Event::KeyPressed:
			      switch(e.key.code)
				{
				case sf::Keyboard::Escape:
				  var = 1;
				  w.close();
				  break;

				default:
				  break;
				}
			    case sf::Event::MouseButtonPressed:
			      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 &&
				  MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 &&
				  MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the Return-button.
				{
				  var = 1; // This is used to control the loop such that we don't exit the program but insted return to the previous window.
				  select = -1;
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x &&
				       MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 &&
				       MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
				{
				  var = 1;
				  w.close();
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 &&
				       MousePosY >= Up.getPosition().y*1.03 && MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5) // If the user clicks on the Up-button.
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed) // If some keyboard key is pressed.
					    {
					      if (select == 1) // If we want to adjust the controls of player 1.
						{
						  if (Keys.count(e.key.code) != 0) // If the pressed key can be found in std::map Keys.
						    {
						      p1.getKeys().up = e.key.code; // Set up (throttle) to be the button that was just pressed on the keyboard.
						      UpKey.setString(Keys.at(p1.getKeys().up)); // Set the string to represent the key just pressed.
						    }
						  var = 1;
						  break;
						}
					      else if (select == 2) // If we want to adjust the controls of player 2.
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p2.getKeys().up = e.key.code;
						      UpKey.setString(Keys.at(p2.getKeys().up));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 3) // If we want to adjust the controls of player 3. 
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p3.getKeys().up = e.key.code;
						      UpKey.setString(Keys.at(p3.getKeys().up));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 4) // If we want to adjust the controls of player 4.
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p3.getKeys().up = e.key.code;
						      UpKey.setString(Keys.at(p4.getKeys().up));
						    }
						  var = 1;
						  break;
						}
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 &&
				       MousePosY >= Down.getPosition().y*1.03 && MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5) // If the user clicks on the Down-button.
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      if (select == 1)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p1.getKeys().down = e.key.code;
						      DownKey.setString(Keys.at(p1.getKeys().down));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p2.getKeys().down = e.key.code;
						      DownKey.setString(Keys.at(p2.getKeys().down));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p3.getKeys().down = e.key.code;
						      DownKey.setString(Keys.at(p3.getKeys().down));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p4.getKeys().down = e.key.code;
						      DownKey.setString(Keys.at(p4.getKeys().down));
						    }
						  var = 1;
						  break;
						}
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 &&
				       MousePosY >= Left.getPosition().y*1.03 && MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5) // If the user clicks on the Left-button.
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      if (select == 1)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p1.getKeys().left = e.key.code;
						      LeftKey.setString(Keys.at(p1.getKeys().left));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p2.getKeys().left = e.key.code;
						      LeftKey.setString(Keys.at(p2.getKeys().left));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p3.getKeys().left = e.key.code;
						      LeftKey.setString(Keys.at(p3.getKeys().left));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p4.getKeys().left = e.key.code;
						      LeftKey.setString(Keys.at(p4.getKeys().left));
						    }
						  var = 1;
						  break;
						}
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 &&
				       MousePosY >= Right.getPosition().y*1.03 && MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5) // If the user clicks on the Right-button.
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      if (select == 1)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p1.getKeys().right = e.key.code;
						      RightKey.setString(Keys.at(p1.getKeys().right));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p2.getKeys().right = e.key.code;
						      RightKey.setString(Keys.at(p2.getKeys().right));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p3.getKeys().right = e.key.code;
						      RightKey.setString(Keys.at(p3.getKeys().right));
						    }
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  if (Keys.count(e.key.code) != 0)
						    {
						      p4.getKeys().right = e.key.code;
						      RightKey.setString(Keys.at(p4.getKeys().right));
						    }
						  var = 1;
						  break;
						}
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}
			    default:
			      break;
			    }
			}
		      w.clear(sf::Color::White);
		      w.draw(Return);
		      w.draw(ExitButton);
		      w.draw(Up);
		      w.draw(UpKey);
		      w.draw(DownKey);
		      w.draw(LeftKey);
		      w.draw(RightKey);
		      w.draw(Down);
		      w.draw(Left);
		      w.draw(Right);
		      w.draw(Controls);
		      w.display();
		      if (var == 1)
			{
			  break;
			}
		    }
		}
	    default:
	      break;
	    }
	  if (var == 1)
	    {
	      return 0;
	    }
	}
      w.clear(sf::Color::White);
      w.draw(ReturnButton);
      w.draw(ExitButton);
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
  
  //The width and height in 10x10 tiles
  int x = WIDTH/boxwidth;
  int y = HEIGHT/boxwidth;
  
  int A[y][x]; //If 1000x1000 pixels and 100x100 tiles
  
  //Creating an empty level, x tiles wide, y tiles high
  sf::RectangleShape tiles[y][x];
  for(int i = 0; i < y; i++)
    {
      for(int j = 0; j < x; j++)
	{
	  sf::RectangleShape rectangle(sf::Vector2f(boxwidth, boxwidth));	
	  rectangle.setPosition((j)*boxwidth, i*boxwidth);
	  rectangle.setFillColor(sf::Color::Green);
	  tiles[i][j] = rectangle;
	}
    }
    
    //Initialize matrix as ones
    for(int i = 0; i < y; i++)
      {
	for(int j = 0; j < x; j++)
	  {
	    A[i][j] = 1;
	    tiles[i][j].setFillColor(sf::Color::Green);
	  }
      }    
    
    b2Vec2 gravity(0.f, 0.0f); // Define gravity, in this case it will be zero.
    b2World world(gravity); // Define world.
    
    //Writing the matrix to file level1.txt
    std::ofstream f("./Level/level1.txt");
    
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
			    w.draw(tiles[i][j]);
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
	  
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	    {
	      tiles[y2][x2].setFillColor(sf::Color::Black);
	      tiles[y2][x2].setRotation(0);
	      A[y2][x2] = 0;
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
	    tiles[y2][x2].setFillColor(sf::Color::Green);
	    tiles[y2][x2].setRotation(0);
	    A[y2][x2] = 1;
	  }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	    {
	      tiles[y2][x2].setFillColor(sf::Color::White);
	      tiles[y2][x2].setRotation(0);			
	      A[y2][x2] = 2;	  
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	    {
	      tiles[y2][x2].setFillColor(sf::Color::Blue);
	      tiles[y2][x2].setRotation(0);
	      A[y2][x2] = 3;	  
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	    {
	      tiles[y2][x2].setFillColor(sf::Color(200,200,200,200));
	      tiles[y2][x2].setRotation(0);
	      A[y2][x2] = 10;  
	    }
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	    {
	      tiles[y2][x2].setFillColor(sf::Color::Yellow);
	      tiles[y2][x2].setRotation(0);
	      A[y2][x2] = 100;  
	    }
	}
	
        // Clear previously displayed window, draw the new positions
	
	w.clear();
        
       	for(int i = 0; i < y; i++)
	  {
	    for(int j = 0; j < x; j++)
	      {
		w.draw(tiles[i][j]);
	      }
	  }
        
        w.display();
    }
    return 0;
}
