#include <SFML/Graphics.hpp>

// We will enter this function when the user clicks on the Options-button in the first menu-screen. This function works almost exactly same way than the code that maintains the firs menu window.
int OptionsWindow(sf::Event e, sf::RenderWindow *w, sf::Font f)
{
  w->setFramerateLimit(80);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  ReturnButton.setPosition(w->getSize().x/6-ReturnButton.getLocalBounds().width/2, w->getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w->getSize().x/1.15-ExitButton.getLocalBounds().width/2, w->getSize().y-ExitButton.getLocalBounds().height*2.5);

  while (w->isOpen())
    {
      MousePosX = sf::Mouse::getPosition(*w).x;
      MousePosY = sf::Mouse::getPosition(*w).y;
      if (MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5)
	{
	  ReturnButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ReturnButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
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
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5)
		{
		  var = 1;
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
		{
		  w->close();
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
      w->draw(ReturnButton);
      w->draw(ExitButton);
      w->display();
    }
  return 0;
}
