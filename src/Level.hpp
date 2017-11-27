#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Car.hpp"
#include "PhysicsObject.hpp"
#include "Tile.hpp"

class Level {
    public:
        Level(std::string);
        void drawTo(sf::RenderWindow& window);
        void addCar(std::shared_ptr<Car>);
        /*TODO
        void saveTo(std::string outFileName);
        void addObstacle(std::shared_ptr<PhysicsObject>);*/
    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Car>> cars;
        std::vector<std::shared_ptr<PhysicsObject>> obstacles;
};

#endif
