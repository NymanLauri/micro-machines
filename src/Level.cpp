#include <fstream>
#include "Level.hpp"

Level::Level(std::string levelFileName, Settings& s) {
    size_t x = static_cast<int>(s.worldWidth);
    size_t y = static_cast<int>(s.worldHeight);
    std::ifstream levelFile(levelFileName);
    // TODO Handle errors when opening the file
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            int tileNum;
            levelFile >> tileNum;
            switch (tileNum) {
                case 1:
                    tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                default:
                    //TODO throw error if the level file contains invalid tile numbers
                    tiles.push_back(Tile::createRoadTile(s, s.tileWidth*i, s.tileHeight*j));
            }
        }
    }
}

void Level::drawTo(sf::RenderWindow& window, Settings& s) {
    for (auto it : tiles) it->drawTo(window);
    for (auto it : obstacles) it->drawTo(window, s);
    for (auto it : cars) it->drawTo(window, s);
}

void Level::addCar(std::shared_ptr<Car> car) {
    cars.push_back(car);
}

void Level::addObstacle(std::shared_ptr<PhysicsObject> obstacle) {
    obstacles.push_back(obstacle);
}
