#include "KeySettings.hpp"

class Player {
    public:
        Player() : keys(KeySettings{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D}) { };
        Player(KeySettings k) : keys(k) { };
        KeySettings& getKeys() { return keys; }
    private:
        KeySettings keys;
};
