#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Car.hpp"
#include "PhysicsObject.hpp"
#include "Tile.hpp"

class Level {
    public:
        Level(std::string, Settings& s);
        void drawTo(sf::RenderWindow& window, Settings& s);
        void addCar(std::shared_ptr<Car>);
        void addObstacle(std::shared_ptr<PhysicsObject>);
        //TODO: void saveTo(std::string outFileName);
    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Car>> cars;
        std::vector<std::shared_ptr<PhysicsObject>> obstacles;
};

#endif
