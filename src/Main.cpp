#include <SFML/Graphics.hpp>
#include <iostream>
#include "Functions.h"
// How to compile: g++ -g -Wall -o game Main.cpp Functions.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

int main()
{
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Micro Machines", sf::Style::Fullscreen);
  sf::Event event;
  window.setFramerateLimit(80);
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Font font;
  font.loadFromFile("Ubuntu-B.ttf");
  
  sf::Text ExitButton("Exit", font, 100);
  sf::Text OptionsButton("Options", font, 100);
  sf::Text StartButton("Start Game", font, 100);
  sf::Text Title("Game name here", font, 150);
  ExitButton.setColor(sf::Color::Black);
  ExitButton.setPosition(window.getSize().x/2-ExitButton.getLocalBounds().width/2, window.getSize().y-ExitButton.getLocalBounds().height*2);
  OptionsButton.setColor(sf::Color::Black);
  OptionsButton.setPosition(window.getSize().x/2-OptionsButton.getLocalBounds().width/2, window.getSize().y-OptionsButton.getLocalBounds().height*3.5);
  StartButton.setColor(sf::Color::Black);
  StartButton.setPosition(window.getSize().x/2-StartButton.getLocalBounds().width/2, window.getSize().y-StartButton.getLocalBounds().height*7);
  Title.setColor(sf::Color::Red);
  Title.setPosition(window.getSize().x/2-Title.getLocalBounds().width/2, window.getSize().y-Title.getLocalBounds().height*7.5);
  
  while (window.isOpen())
    {
      MousePosX = sf::Mouse::getPosition(window).x;
      MousePosY = sf::Mouse::getPosition(window).y;
      if (MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}
      if (MousePosX >= OptionsButton.getPosition().x*1.01 && MousePosX <= OptionsButton.getPosition().x+OptionsButton.getLocalBounds().width*1.1 && MousePosY >= OptionsButton.getPosition().y*1.03 && MousePosY <= OptionsButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
	{
	  OptionsButton.setColor(sf::Color::Blue);
	}
      else
	{
	  OptionsButton.setColor(sf::Color::Black);
	}
      if (MousePosX >= StartButton.getPosition().x*1.01 && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.1 && MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5)
	{
	  StartButton.setColor(sf::Color::Blue);
	}
      else
	{
	  StartButton.setColor(sf::Color::Black);
	}
      while (window.pollEvent(event))
	{ 
	  switch (event.type)
	    {
	    case sf::Event::Closed:
	      window.close();
	      break;

	    case sf::Event::KeyPressed:
	      switch(event.key.code)
		{
		case sf::Keyboard::Escape:
		  window.close();
		  break;

		default:
		  break;
		}
	    case sf::Event::MouseButtonPressed:
	      if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
		{
		  window.close();
		  break;
		}
	      else if (event.mouseButton.button == sf::Mouse::Left && MousePosX >= OptionsButton.getPosition().x*1.01 && MousePosX <= OptionsButton.getPosition().x+OptionsButton.getLocalBounds().width*1.1 && MousePosY >= OptionsButton.getPosition().y*1.03 && OptionsButton.getPosition().y+OptionsButton.getLocalBounds().height*1.5)
		{
		  OptionsWindow(event, &window, font);
		}
	    default:
	      break;
	    }
	}
      window.clear(sf::Color::White);
      window.draw(ExitButton);
      window.draw(OptionsButton);
      window.draw(StartButton);
      window.draw(Title);
      window.display();
    }
  return 0;
}
