#include <fstream>
#include "Level.hpp"

#define WIDTH 1800
#define HEIGHT 1000
Level::Level(std::string levelFileName) {
    size_t x = WIDTH/20;
    size_t y = HEIGHT/20;
    std::ifstream levelFile(levelFileName);
    // TODO Handle errors when opening the file
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            int tileNum;
            levelFile >> tileNum;
            switch (tileNum) {
                case 1:
                    tiles.push_back(Tile::createGrassTile(20*i, 20*j));
                    break;
                default:
                    //TODO throw error if the level file contains invalid tile numbers
                    tiles.push_back(Tile::createGrassTile(20*i, 20*j));
            }
        }
    }
}

void Level::drawTo(sf::RenderWindow& window) {
    for (auto it : tiles) it->drawTo(window);
    for (auto it : obstacles) it->drawTo(window);
    for (auto it : cars) it->drawTo(window);
}

void Level::addCar(std::shared_ptr<Car> car) {
    cars.push_back(car);
}

void Level::addObstacle(std::shared_ptr<PhysicsObject> obstacle) {
    obstacles.push_back(obstacle);
}
