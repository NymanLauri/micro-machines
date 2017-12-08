/* The class for the levels of the game. The levels consist of square tiles which form the
 * terrain, and physical obstacles which are handled by separate PhysicsObjects.
 * The Level constructor takes a string for the name of the file from which the level is loaded (see
 * the constructor comments in Level.cpp), the b2World where the physical obstacles will be created,
 * and the settings for coordinate conversions.
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Car.hpp"
#include "PhysicsObject.hpp"
#include "Tile.hpp"

class Car;
class Tire;
class Level {
    public:
        Level(std::string, b2World& world, Settings& s);
        void createScreenBorders(b2World& world);
        void addCar(std::shared_ptr<Car>);
        void addObstacle(std::shared_ptr<PhysicsObject>);
        float getFrictionMultiplier(b2Vec2 coordinates) const;
        void drawTo(sf::RenderWindow& window);
        void checkpointChecker();
    private:
        unsigned int currentLap;
  std::vector<std::pair<unsigned int, b2Vec2>> checkpointVector;
        std::vector<std::shared_ptr<Tile>> tiles;
  std::vector<std::shared_ptr<Car>> cars;
        std::vector<std::shared_ptr<PhysicsObject>> obstacles;
        const Settings& s;
};

#endif
