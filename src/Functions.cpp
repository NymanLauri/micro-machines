#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "KeySettings.hpp"


// This loop controls the window in which the user chooses map etc. befor starting the game.
int StartWindow(sf::Event e, sf::RenderWindow &w, sf::Font f)
{
  w.setFramerateLimit(60);
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  // Create some texts.
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
      if (MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main menu"-button.
	{
	  ReturnButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ReturnButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 && MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the mouse is on top of the Start-button.
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
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
		{
		  var = 1;
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= StartButton.getPosition().x && MousePosX <= StartButton.getPosition().x+StartButton.getLocalBounds().width*1.3 && MousePosY >= StartButton.getPosition().y*1.03 && MousePosY <= StartButton.getPosition().y+StartButton.getLocalBounds().height*1.5) // If the user clicks on the start-button.
		{
		  return 1; // This return value tells the menu()-function to start the game.
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

// We will enter this function when the user clicks on the Options-button in the first menu-screen.
int OptionsWindow(sf::Event e, sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4)
{
  w.setFramerateLimit(60);
  int select = -1; // This variable is used to control whose controls are being changed.
  int var = 0;
  int MousePosX = 0;
  int MousePosY = 0;
  // Create some texts.
  sf::Text ReturnButton("Main Menu", f, 100);
  sf::Text ExitButton("Exit", f, 100);
  sf::Text Player1Opts("Player 1", f, 80);
  sf::Text Player2Opts("Player 2", f, 80);
  ReturnButton.setColor(sf::Color::Black);
  ExitButton.setColor(sf::Color::Black);
  Player1Opts.setColor(sf::Color::Black);
  Player2Opts.setColor(sf::Color::Black);
  ReturnButton.setPosition(w.getSize().x/6-ReturnButton.getLocalBounds().width/2, w.getSize().y-ReturnButton.getLocalBounds().height*2.5);
  ExitButton.setPosition(w.getSize().x/1.15-ExitButton.getLocalBounds().width/2, w.getSize().y-ExitButton.getLocalBounds().height*2.5);
  Player1Opts.setPosition(w.getSize().x/7.5-Player1Opts.getLocalBounds().width/2, w.getSize().y-Player1Opts.getLocalBounds().height*13);
  Player2Opts.setPosition(w.getSize().x/7.5-Player2Opts.getLocalBounds().width/2, w.getSize().y-Player2Opts.getLocalBounds().height*11);

  while (w.isOpen())
    {
      MousePosX = sf::Mouse::getPosition(w).x;
      MousePosY = sf::Mouse::getPosition(w).y;
      if (MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the mouse is on top of the "Main menu"-button.
	{
	  ReturnButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ReturnButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of the Exit-button.
	{
	  ExitButton.setColor(sf::Color::Blue);
	}
      else
	{
	  ExitButton.setColor(sf::Color::Black);
	}

      if (MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 && MousePosY >= Player1Opts.getPosition().y*1.03 && MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 1"-button.
	{
	  Player1Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player1Opts.setColor(sf::Color::Black);
	}

      if (MousePosX >= Player2Opts.getPosition().x*1.01 && MousePosX <= Player2Opts.getPosition().x+Player2Opts.getLocalBounds().width*1.1 && MousePosY >= Player2Opts.getPosition().y*1.03 && MousePosY <= Player2Opts.getPosition().y+Player2Opts.getLocalBounds().height*1.5) // If the mouse is on top of the "player 2"-button.
	{
	  Player2Opts.setColor(sf::Color::Red);
	}
      else
	{
	  Player2Opts.setColor(sf::Color::Black);
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
	      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the "Main menu"-button.
		{
		  var = 1;
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
		{
		  w.close();
		  break;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player1Opts.getPosition().x*1.01 && MousePosX <= Player1Opts.getPosition().x+Player1Opts.getLocalBounds().width*1.1 && MousePosY >= Player1Opts.getPosition().y*1.03 && MousePosY <= Player1Opts.getPosition().y+Player1Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 1"-button.
		{
		  select = 1;
		}
	      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Player2Opts.getPosition().x*1.01 && MousePosX <= Player2Opts.getPosition().x+Player2Opts.getLocalBounds().width*1.1 && MousePosY >= Player2Opts.getPosition().y*1.03 && MousePosY <= Player2Opts.getPosition().y+Player2Opts.getLocalBounds().height*1.5) // If the user clicks on the "player 2"-button.
		{
		  select = 2;
		}
	      if (select != -1) // If the user had clicked on some "player i"-button. select 1 = player 1, select 2 = player 2, select 3 = player 3, select 4 = player 4.
		{
		  // Create some texts.
		  sf::Text Return("Return", f, 100);
		  sf::Text Up("Up", f, 80);
		  sf::Text Down("Down", f, 80);
		  sf::Text Left("Left", f, 80);
		  sf::Text Right("Right", f, 80);
		  sf::Text Controls("Controls", f, 80);
		  Up.setColor(sf::Color::Black);
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
		      if (MousePosX >= Return.getPosition().x*1.01 && MousePosX <= Return.getPosition().x+Return.getLocalBounds().width*1.1 && MousePosY >= Return.getPosition().y*1.03 && MousePosY <= Return.getPosition().y+Return.getLocalBounds().height*1.5) // If the mouse is on top of Return-button.
			{
			  Return.setColor(sf::Color::Blue);
			}
		      else
			{
			  Return.setColor(sf::Color::Black);
			}
		      
		      if (MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the mouse is on top of Exit-button.
			{
			  ExitButton.setColor(sf::Color::Blue);
			}
		      else
			{
			  ExitButton.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 && MousePosY >= Up.getPosition().y*1.03 && MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5) // If the mouse is on top of Up-button.
			{
			  Up.setColor(sf::Color::Blue);
			}
		      else
			{
			  Up.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 && MousePosY >= Down.getPosition().y*1.03 && MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5) // If the mouse is on top of the Down-button.
			{
			  Down.setColor(sf::Color::Blue);
			}
		      else
			{
			  Down.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 && MousePosY >= Left.getPosition().y*1.03 && MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5) // If the mouse is on top of the Left-button.
			{
			  Left.setColor(sf::Color::Blue);
			}
		      else
			{
			  Left.setColor(sf::Color::Black);
			}

		      if (MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 && MousePosY >= Right.getPosition().y*1.03 && MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5) // If the mouse is on top of the Right-button.
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
			      if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ReturnButton.getPosition().x*1.01 && MousePosX <= ReturnButton.getPosition().x+ReturnButton.getLocalBounds().width*1.1 && MousePosY >= ReturnButton.getPosition().y*1.03 && MousePosY <= ReturnButton.getPosition().y+ReturnButton.getLocalBounds().height*1.5) // If the user clicks on the Return-button.
				{
				  var = 1;
				  select = -1;
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= ExitButton.getPosition().x && MousePosX <= ExitButton.getPosition().x+ExitButton.getLocalBounds().width*1.3 && MousePosY >= ExitButton.getPosition().y*1.03 && MousePosY <= ExitButton.getPosition().y+ExitButton.getLocalBounds().height*1.5) // If the user clicks on the Exit-button.
				{
				  var = 1;
				  w.close();
				  break;
				}
			      
			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Up.getPosition().x && MousePosX <= Up.getPosition().x+Up.getLocalBounds().width*1.3 && MousePosY >= Up.getPosition().y*1.03 && MousePosY <= Up.getPosition().y+Up.getLocalBounds().height*1.5) // If the user clicks on the Up-button.
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
						  p1.getKeys().up = e.key.code; // Set up (throttle) to be the button that was just pressed on the keyboard.
						  var = 1;
						  break;
						}
					      else if (select == 2) // If we want to adjust the controls of player 2.
						{
						  p2.getKeys().up = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 3) // If we want to adjust the controls of player 3. 
						{
						  p3.getKeys().up = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 4) // If we want to adjust the controls of player 4.
						{
						  p3.getKeys().up = e.key.code;
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

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Down.getPosition().x && MousePosX <= Down.getPosition().x+Down.getLocalBounds().width*1.3 && MousePosY >= Down.getPosition().y*1.03 && MousePosY <= Down.getPosition().y+Down.getLocalBounds().height*1.5) // If the user clicks on the Down-button.
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
						  p1.getKeys().down = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  p2.getKeys().down = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  p3.getKeys().down = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  p4.getKeys().down = e.key.code;
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

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Left.getPosition().x && MousePosX <= Left.getPosition().x+Left.getLocalBounds().width*1.3 && MousePosY >= Left.getPosition().y*1.03 && MousePosY <= Left.getPosition().y+Left.getLocalBounds().height*1.5) // If the user clicks on the Left-button.
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
						  p1.getKeys().left = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  p2.getKeys().left = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  p3.getKeys().left = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  p4.getKeys().left = e.key.code;
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

			      else if (e.mouseButton.button == sf::Mouse::Left && MousePosX >= Right.getPosition().x && MousePosX <= Right.getPosition().x+Right.getLocalBounds().width*1.3 && MousePosY >= Right.getPosition().y*1.03 && MousePosY <= Right.getPosition().y+Right.getLocalBounds().height*1.5) // If the user clicks on the Right-button.
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
						  p1.getKeys().right = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 2)
						{
						  p2.getKeys().right = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 3)
						{
						  p3.getKeys().right = e.key.code;
						  var = 1;
						  break;
						}
					      else if (select == 4)
						{
						  p4.getKeys().right = e.key.code;
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
      w.display();
    }
  return 0;
}
