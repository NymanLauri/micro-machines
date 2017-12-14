/* Class for different road tile types. The levels consist of square shaped tiles; this class stores
 * the properties of the each such tile: the color/texture of the tile and the friction multiplier.*/

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
        static std::shared_ptr<Tile> createRoadTile(Settings& s, size_t xCoord, size_t yCoordf, int col);
        static std::shared_ptr<Tile> createIceTile(Settings& s, size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createCheckpointTile(Settings& s, size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createOilTile(Settings& s, size_t xCoord, size_t yCoord);  
    private:
        sf::RectangleShape shape;
        const int tileNum;
        const float frictionMultiplier;
};

#endif

