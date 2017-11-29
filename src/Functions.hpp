#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include "Player.hpp"

int OptionsWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);
int StartWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);
int EditorWindow(sf::RenderWindow &w, sf::Font fo);
int Game(sf::RenderWindow &window, sf::Font font, Player &player1, Player &player2, Player &player3, Player &player4);
int menu(Player &player1, Player &player2, Player &player3, Player &player4);

#endif
