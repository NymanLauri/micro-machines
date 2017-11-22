#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "KeySettings.hpp"

int StartWindow(sf::Event e, sf::RenderWindow &w, sf::Font f)
{
  //w->setFramerateLimit(80);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text StartButton("Start", f, 100);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  StartButton.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  StartButton.setPosition(w.getSize().x/2-StartButton.getLocalBounds().width/2, w.getSize().y/2-StartButton.getLocalBounds().height/2);

  while (w.isOpen())
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
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

      if (MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 && MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5)
	{
	  StartButton.setColor(sf::Color::Blue);
	}
      else
	{
	  StartButton.setColor(sf::Color::Black);
	}
      
      while (w.pollEvent(e))
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
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5)
		{
		  var = 1;
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 && MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5)
		{
		  return 1;
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
      w.draw(StartButton);
      w.display();
    }
  return 0;
}

// We will enter this function when the user clicks on the Options-button in the first menu-screen. This function works almost exactly same way than the code that maintains the firs menu window.
int OptionsWindow(sf::Event e, sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  //w->setFramerateLimit(80);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text Player1Opts("Player 1", f, 80);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  Player1Opts.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  Player1Opts.setPosition(w.getSize().x/7.5-Player1Opts.getLocalBounds().width/2, w.getSize().y-Player1Opts.getLocalBounds().height*13);

  while (w.isOpen())
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
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

      if (MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 && MousePosY >= Player1Opts.getPosition().y*1.03 && MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5)
	{
	  Player1Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player1Opts.setColor(sf::Color::Black);
	}
      
      while (w.pollEvent(e))
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
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5)
		{
		  var = 1;
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 && MousePosY >= Player1Opts.getPosition().y*1.03 && MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5)
		{
		  sf::Text Up("Up", f, 80);
		  sf::Text Down("Down", f, 80);
		  sf::Text Left("Left", f, 80);
		  sf::Text Right("Right", f, 80);
		  Up.setColor(sf::Color::Black);
		  Down.setColor(sf::Color::Black);
		  Left.setColor(sf::Color::Black);
		  Right.setColor(sf::Color::Black);
		  Up.setPosition(w.getSize().x/2-Up.getLocalBounds().width/2, w.getSize().y/2-Up.getLocalBounds().height*5);
		  Down.setPosition(w.getSize().x/2-Down.getLocalBounds().width/2, w.getSize().y/2-Down.getLocalBounds().height*4);
		  Left.setPosition(w.getSize().x/2-Left.getLocalBounds().width/2, w.getSize().y/2-Left.getLocalBounds().height*1.5);
		  Right.setPosition(w.getSize().x/2-Right.getLocalBounds().width/2, w.getSize().y/1.5-Right.getLocalBounds().height);
		  int var = 0;
		  while(1)
		    {
		      MousePosX = sf::Mouse::getPosition(w).x;
		      MousePosY = sf::Mouse::getPosition(w).y;
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

		      if (MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 && MousePosY >= Up.getPosition().y*1.03 && MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5)
			{
			  Up.setColor(sf::Color::Blue);
			}
		      else
			{
			  Up.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 && MousePosY >= Down.getPosition().y*1.03 && MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5)
			{
			  Down.setColor(sf::Color::Blue);
			}
		      else
			{
			  Down.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 && MousePosY >= Left.getPosition().y*1.03 && MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5)
			{
			  Left.setColor(sf::Color::Blue);
			}
		      else
			{
			  Left.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 && MousePosY >= Right.getPosition().y*1.03 && MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5)
			{
			  Right.setColor(sf::Color::Blue);
			}
		      else
			{
			  Right.setColor(sf::Color::Black);
			}

		      while (w.pollEvent(e))
			{
			  switch(e.type)
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
			      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5)
				{
				  var = 1;
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5)
				{
				  var = 1;
				  w.close();
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 && MousePosY >= Up.getPosition().y*1.03 && MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5)
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      p1.getKeys().up = e.key.code;
					      var = 1;
					      break;
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 && MousePosY >= Down.getPosition().y*1.03 && MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5)
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      p1.getKeys().down = e.key.code;
					      var = 1;
					      break;
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 && MousePosY >= Left.getPosition().y*1.03 && MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5)
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      p1.getKeys().left = e.key.code;
					      var = 1;
					      break;
					    }
					}
				      if (var == 1)
					{
					  break;
					}
				    }
				}

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 && MousePosY >= Right.getPosition().y*1.03 && MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5)
				{
				  int var = 0;
				  while(1)
				    {
				      while (w.pollEvent(e))
					{
					  if (e.type == sf::Event::KeyPressed)
					    {
					      p1.getKeys().right = e.key.code;
					      var = 1;
					      break;
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
		      w.draw(ReturnButton);
		      w.draw(ExitButton);
		      w.draw(Up);
		      w.draw(Down);
		      w.draw(Left);
		      w.draw(Right);
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
      w.display();
    }
  return 0;
}
