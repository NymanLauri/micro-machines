#include "Tile.hpp"

Tile::Tile(const int tileNum, Settings& s, size_t xCoord, size_t yCoord, const float fm) : tileNum(tileNum), frictionMultiplier(fm) { // The tile constructor.
    shape = sf::RectangleShape(sf::Vector2f(s.tileWidth, s.tileHeight));
    shape.setPosition(xCoord, yCoord);
}

void Tile::drawTo(sf::RenderWindow& window) const {
    // Don't draw grass tiles to improve performance; handle grass tiles
    // by setting the background color of the screen to be the grass color.
    // (This is done in the level class.)
    if (tileNum != 0) window.draw(shape);
}

// Return a tile's friction multiplier.
float Tile::getFrictionMultiplier() const {
    return frictionMultiplier;
}

// Create a grass tile.
std::shared_ptr<Tile> Tile::createGrassTile(Settings& s, size_t xCoord, size_t yCoord) { // This creates a tile for grass.
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(0, s, xCoord, yCoord, 5.0);
    tile->shape.setFillColor(sf::Color(0, 123, 12, 255));
    return tile;
}

// Create a road tile.
std::shared_ptr<Tile> Tile::createRoadTile(Settings& s, size_t xCoord, size_t yCoord, int col) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(1, s, xCoord, yCoord, 1.0);
    if (col == 0)
      tile->shape.setFillColor(sf::Color(128, 128, 128, 255));
    else if (col == 1)
      tile->shape.setFillColor(sf::Color::Red);
    return tile;
}

// Create an ice tile.
std::shared_ptr<Tile> Tile::createIceTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(2, s, xCoord, yCoord, 0.5);
    tile->shape.setFillColor(sf::Color::White);
    return tile;
}

// Create a checkpoint tile.
std::shared_ptr<Tile> Tile::createCheckpointTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(100, s, xCoord, yCoord, 1.0);
    tile->shape.setFillColor(sf::Color::Yellow);
    return tile;
}

// Create an oil tile.
std::shared_ptr<Tile> Tile::createOilTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(3, s, xCoord, yCoord, 125.0);
    tile->shape.setFillColor(sf::Color::Black);
    return tile;
}

