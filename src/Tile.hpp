/* Class for different road tile types. */

#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <SFML/Graphics.hpp>
class Tile {
    public:
        Tile(size_t xCoord, size_t yCoord, const float frictionMultiplier = 1.0);
        void drawTo(sf::RenderWindow& window) const;
        static std::shared_ptr<Tile> createGrassTile(size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createRoadTile(size_t xCoord, size_t yCoord);
        static std::shared_ptr<Tile> createIceTile(size_t xCoord, size_t yCoord);
    private:
        sf::RectangleShape shape;
        const float frictionMultiplier;
};

#endif
