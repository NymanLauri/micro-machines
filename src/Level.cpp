#include <fstream>
#include "Level.hpp"

Level::Level(std::string levelFileName, b2World& world, Settings& s) : s(s) {
    size_t x = static_cast<int>(s.worldWidth);
    size_t y = static_cast<int>(s.worldHeight);
    std::ifstream levelFile(levelFileName);
    // TODO Handle errors when opening the file
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            int tileNum;
            levelFile >> tileNum;
            switch (tileNum) {
                case 0:
                    tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 1:
                    tiles.push_back(Tile::createRoadTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 2:
                    tiles.push_back(Tile::createIceTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 10:
                    {
                    // TEMPORARY TEST FOR ADDING PHYSICS OBJECTS
                    tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                    b2BodyDef bd;
                    bd.position.Set(i, j);
                    b2FixtureDef fd;
                    fd.friction = 0.3;
                    obstacles.push_back(std::make_shared<PhysicsObject>(world, s, 2.0, bd, fd, sf::Color::Blue));
                    }
                    break;
                default:
                    //TODO throw error if the level file contains invalid numbers
                    tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
            }
        }
    }
}

void Level::createScreenBorders(b2World& world, Settings& s) {
    b2BodyDef borderDef;
    b2Body* borderBody = world.CreateBody(&borderDef);
    b2Vec2 vertices[4];
    vertices[0].Set(0.0, 0.0);
    vertices[1].Set(0.0, s.worldHeight);
    vertices[2].Set(s.worldWidth, s.worldHeight);
    vertices[3].Set(s.worldWidth, 0.0);
    b2ChainShape screenBorders;
    screenBorders.CreateLoop(vertices, 4);
    borderBody->CreateFixture(&screenBorders, 1.0);
}

void Level::addCar(std::shared_ptr<Car> car) {
    cars.push_back(car);
}

void Level::addObstacle(std::shared_ptr<PhysicsObject> obstacle) {
    obstacles.push_back(obstacle);
}

float Level::getFrictionMultiplier(b2Vec2 coordinates) const {
    int x = static_cast<int>(coordinates.x);
    int y = static_cast<int>(coordinates.y);
    int xWidth = static_cast<int>(s.worldWidth);
    int yWidth = static_cast<int>(s.worldHeight);
    // Since the matrix is indexed starting from top left and the world coordinate origin is at the bottom left
    // corner of the screen, the correct "row" of the tiles vector is the (yWidth-y-1):th row.
    if (x >= 0 && x < xWidth && y >= 0 && y < yWidth) return (tiles.at((yWidth-y-1)*xWidth + x))->getFrictionMultiplier();
    else return 1.0;
}

void Level::drawTo(sf::RenderWindow& window, Settings& s) {
    // Set background color to grass color, as grass tiles are not drawn individually to
    // improve performance.
    window.clear(sf::Color(0, 123, 12, 255));
    for (auto it : tiles) it->drawTo(window);
    for (auto it : obstacles) it->drawTo(window, s);
    for (auto it : cars) it->drawTo(window, s);
}

