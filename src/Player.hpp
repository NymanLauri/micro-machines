/* A class for the players of the game. Used to handle the key settings of the players */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "KeySettings.hpp"

class Player {
    public:
        Player() : keys(KeySettings{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right}) { };
        Player(KeySettings k) : keys(k) { };
        void setKeys(KeySettings s) { keys = s; }
        KeySettings& getKeys() { return keys; }
    private:
        KeySettings keys;
};

#endif
