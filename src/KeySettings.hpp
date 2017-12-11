#ifndef KEYSETTINGS_HPP
#define KEYSETTINGS_HPP

#include <SFML/Window.hpp>

struct KeySettings { // Structure that contains the keys of a player.
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
};

#endif
