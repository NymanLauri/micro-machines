#include "Tile.hpp"

Tile::Tile(const int tileNum, Settings& s, size_t xCoord, size_t yCoord, const float fm) : tileNum(tileNum), frictionMultiplier(fm) {
    shape = sf::RectangleShape(sf::Vector2f(s.tileWidth, s.tileHeight));
    shape.setPosition(xCoord, yCoord);
}

void Tile::drawTo(sf::RenderWindow& window) const {
    // Don't draw grass tiles to improve performance.
    if (tileNum != 0) window.draw(shape);
}

float Tile::getFrictionMultiplier() const {
    return frictionMultiplier;
}

std::shared_ptr<Tile> Tile::createGrassTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(0, s, xCoord, yCoord, 5.0);
    tile->shape.setFillColor(sf::Color(0, 123, 12, 255));
    return tile;
}

std::shared_ptr<Tile> Tile::createRoadTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(1, s, xCoord, yCoord, 1.0);
    tile->shape.setFillColor(sf::Color(128, 128, 128, 255));
    return tile;
}

std::shared_ptr<Tile> Tile::createIceTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(2, s, xCoord, yCoord, 0.5);
    tile->shape.setFillColor(sf::Color::White);
    return tile;
}

std::shared_ptr<Tile> Tile::createCheckpointTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(100, s, xCoord, yCoord, 5.0);
    tile->shape.setFillColor(sf::Color::Yellow);
    //count++;
    //tile->checkpointNum = count;
    return tile;
}

//unsigned int Tile::count = 0;
