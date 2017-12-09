#include <string>
#include <fstream>
#include "Level.hpp"
#include "Constants.hpp"
#include <algorithm>

/* The level constructor. The levels are saved to text files as numbers, where each number represents a tile type
 * or a physical obstacle. The constructor reads a number from the file and creates the corresponding
 * tile or physical obstacle.
 */
Level::Level(std::string levelFileName, b2World& world, Settings& s) : s(s) {
    size_t x = static_cast<int>(s.worldWidth);
    size_t y = static_cast<int>(s.worldHeight);
    std::ifstream levelFile(levelFileName);
    //std::ifstream levelFile("./Level/level1.txt");
    if (!levelFile)
      throw std::invalid_argument("Could not open the level: " + levelFileName );
    for (size_t j = 0; j < y; j++) {
        for (size_t i = 0; i < x; i++) {
            int tileNum;
            if(!(levelFile >> tileNum))
				throw std::invalid_argument("Error reading from the file " + levelFileName + "." );
            // Default body and fixture definition settings for all static obstacles
            b2BodyDef bd;
            bd.position.Set(i, s.worldHeight - j);
            b2FixtureDef fd;
            fd.friction = 0.3;
            switch (tileNum) {
                case 0: // Grass tile
                    tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 1: // Road tile
                    tiles.push_back(Tile::createRoadTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 2: // Ice tile
                    tiles.push_back(Tile::createIceTile(s, s.tileWidth*i, s.tileHeight*j));
                    break;
                case 10: // A small brown static rock obstacle.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(0.0, -1.5),
                            std::make_pair(-1.0, -1.3),
                            std::make_pair(-2.0, -0.0),
                            std::make_pair(-1.4, 0.5),
                            std::make_pair(-0.4, 1.1),
                            std::make_pair(1.0, 1.5),
                            std::make_pair(2.0, 0.9),
                            std::make_pair(1.0, -0.7)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
                    }
                    break;
                case 11: // Another small brown static rock obstacle.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(1.0, -2.0),
                            std::make_pair(0.0, -1.5),
                            std::make_pair(-1.0, -0.7),
                            std::make_pair(-2.0, 0.0),
                            std::make_pair(-2.0, 0.5),
                            std::make_pair(-1.0, 1.0),
                            std::make_pair(0.5, 2.2),
                            std::make_pair(2.0, -0.5)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
                    }
                    break;
                case 12: // A larger version of case 10 rock.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(0.0, -3.0),
                            std::make_pair(-2.0, -2.6),
                            std::make_pair(-4.0, -0.0),
                            std::make_pair(-2.8, 1.0),
                            std::make_pair(-0.8, 2.2),
                            std::make_pair(2.0, 3.0),
                            std::make_pair(4.0, 1.8),
                            std::make_pair(2.0, -1.4)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
                    }
                    break;
                case 13: // A larger version of case 11 rock.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(2.0, -4.0),
                            std::make_pair(0.0, -3.0),
                            std::make_pair(-2.0, -1.4),
                            std::make_pair(-4.0, 0.0),
                            std::make_pair(-4.0, 1.0),
                            std::make_pair(-2.0, 2.0),
                            std::make_pair(1.0, 4.4),
                            std::make_pair(4.0, -1.0)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));

                    }
                    break;
                case 20: // A horizontal rail.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));

                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255)));
                    }
                    break;
                case 21: // A vertical rail.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(1, 20), bd, fd, sf::Color(160,160,160,255)));
                    }
                    break;
                case 22: // A diagonal rail from bottom right to top left.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
                        physObjPtr->getBody()->SetTransform(b2Vec2(i, s.worldHeight-j), -45.0 * DEGTORAD);
                        obstacles.push_back(physObjPtr);
                    }
                    break;
                case 23: // A diagonal rail from bottom left to top right.
                    {
                        tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
                        auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
                        physObjPtr->getBody()->SetTransform(b2Vec2(i, s.worldHeight-j), 45.0 * DEGTORAD);
                        obstacles.push_back(physObjPtr);
                    }
                    break;
        	case 3: // Oil tile
        	    {
                	tiles.push_back(Tile::createOilTile(s, s.tileWidth*i, s.tileHeight*j));
    	      	    }
    	            break;
    	        case 100 ... 200: // A checkpoint with order of 0-100.
    	       	   {
    		        tiles.push_back(Tile::createCheckpointTile(s, s.tileWidth*i, s.tileHeight*j));
    		        b2Vec2 checkPointlocation(((i+0.5)*s.tileWidth)*s.pixelsToMeters, (s.screenHeight - (j+0.5)*s.tileHeight)*s.pixelsToMeters);
    		        checkpointVector.push_back(std::make_pair(tileNum, checkPointlocation));
    	       	   }
    	            break;
                default:
                   	throw std::invalid_argument("Error reading the level-file: unrecognized tilenumber encountered." );
              	 	// tiles.push_back(Tile::createGrassTile(s, s.tileWidth*i, s.tileHeight*j));
            }
        }
    }
    //std::sort(checkpointVector.begin(), checkpointVector.end());
    std::sort(checkpointVector.begin(), checkpointVector.end(), [](std::pair<unsigned int, b2Vec2> &left, std::pair<unsigned int, b2Vec2> &right) {
    return left.first < right.first;
});
}

// Create borders to the level to stop physics objects from traveling outside the screen.
void Level::createScreenBorders(b2World& world) {
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

void Level::drawTo(sf::RenderWindow& window) {
    // Set background color to grass color, as grass tiles are not drawn individually to
    // improve performance.
    window.clear(sf::Color(0, 123, 12, 255));
    for (auto it : tiles) it->drawTo(window);
    for (auto it : obstacles) it->drawTo(window);
    for (auto it : cars) it->drawTo(window);
}

void Level::checkpointChecker() {
  for(auto it : checkpointVector){
    for(auto ite : cars){
      if(b2Distance(ite->getPosition(), it.second) < 10.0){
	ite->addCheckpoint(std::find(checkpointVector.begin(), checkpointVector.end(), it) - checkpointVector.begin(), checkpointVector.size());
      }
    }
  }
}

void Level::sortCars() {
  std::sort(this->cars.begin(), this->cars.end(), [](std::shared_ptr<Car> &left, std::shared_ptr<Car> &right) {
      if (left->getLap() > right->getLap()){
	return true;
      }
      if (left->getLap() < right->getLap()){
	return false;
      }
      if (left->getLap() == right->getLap() && left->checkpointVecSize() > right->checkpointVecSize()){
	return true;
      }
      if (left->getLap() == right->getLap() && left->checkpointVecSize() < right->checkpointVecSize()){
	return false;
      }
    });
}

int Level::getLevelLap() {
  return this->cars.at(0)->getLap();
}

std::shared_ptr<Car> Level::getCar()
{
  return this->cars.at(0);
}
