/* Class for different road tile types. */

#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "Settings.hpp"

class Tile {
    public:
        Tile(const int tileNum, Settings& s, size_t xCoord, size_t yCoord, const float frictionMultiplier = 1.0);
        void drawTo(sf::RenderWindow& window) const;
        float getFrictionMultiplier() const;
        static std::shared_ptr<Tile> createGrassTile(Settings& s, size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createRoadTile(Settings& s, size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createIceTile(Settings& s, size_t xCoord, size_t yCoord);
  static std::shared_ptr<Tile> createCheckpointTile(Settings& s, size_t xCoord, size_t yCoord);
  //unsigned int getCheckpointNum() {return checkpointNum;}
    private:
        sf::RectangleShape shape;
        const int tileNum;
        const float frictionMultiplier;
  //static unsigned int count;
  //unsigned int checkpointNum;
};

#endif

