#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include "Player.hpp"

int OptionsWindow(sf::Event e, sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);
int StartWindow(sf::Event e, sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);

#endif
