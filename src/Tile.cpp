#include "Tile.hpp"

Tile::Tile(Settings& s, size_t xCoord, size_t yCoord, const float fm) : frictionMultiplier(fm) {
    shape = sf::RectangleShape(sf::Vector2f(s.tileWidth, s.tileHeight));
    shape.setPosition(xCoord, yCoord);
}

void Tile::drawTo(sf::RenderWindow& window) const {
    window.draw(shape);
}

std::shared_ptr<Tile> Tile::createGrassTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(s, xCoord, yCoord, 2.0);
    tile->shape.setFillColor(sf::Color::Green);
    return tile;
}

std::shared_ptr<Tile> Tile::createRoadTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(s, xCoord, yCoord, 1.0);
    tile->shape.setFillColor(sf::Color::Red);
    return tile;
}

std::shared_ptr<Tile> Tile::createIceTile(Settings& s, size_t xCoord, size_t yCoord) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(s, xCoord, yCoord, 0.5);
    tile->shape.setFillColor(sf::Color::White);
    return tile;
}
