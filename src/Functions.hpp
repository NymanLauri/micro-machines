#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <map>
#include <string>

int OptionsWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);
std::pair <int, int> StartWindow(sf::RenderWindow &w, sf::Font f, Player &p1, Player &p2, Player &p3, Player &p4);
int EditorWindow(sf::RenderWindow &w, sf::Font fo);
int WaitForKey(sf::RenderWindow &window, Player &p, int x, std::map<sf::Keyboard::Key, std::string> K);
int Game(sf::RenderWindow &window, sf::Font font, Player &player1, Player &player2, Player &player3, Player &player4, int retValue, int mapValue);
int menu(Player &player1, Player &player2, Player &player3, Player &player4);
int EndWindow(sf::RenderWindow &w, sf::Font f, int player_num);

#endif
