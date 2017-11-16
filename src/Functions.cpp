#include <SFML/Graphics.hpp>

int OptionsWindow(sf::Event e, sf::RenderWindow *w, sf::Font f)
{
  w->setFramerateLimit(80);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Text ExitButton("Exit", f, 100);
  ExitButton.setColor(sf::Color::Black);
  ExitButton.setPosition(w->getSize().x/2-ExitButton.getLocalBounds().width/2, w->getSize().y-ExitButton.getLocalBounds().height*2);

  while (w->isOpen())
    {
      MousePosX = sf::Mouse::getPosition(*w).x;
      MousePosY = sf::Mouse::getPosition(*w).y;
      if (MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}
      while (w->pollEvent(e))
	{
	  switch (e.type)
	    {
	    case sf::Event::Closed:
	      w->close();
	      break;

	    case sf::Event::KeyPressed:
	      switch(e.key.code)
		{
		case sf::Keyboard::Escape:
		  w->close();
		  break;

		default:
		  break;
		}

	    case sf::Event::MouseButtonPressed:
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x*1.01 && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.2 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
		{
		  var = 1;
		  break;
		}
	    default:
	      break;
	    }
	  if (var == 1)
	    {
	      return 0;
	    }
	}
      w->clear(sf::Color::White);
      w->draw(ExitButton);
      w->display();
    }
  return 0;
}
