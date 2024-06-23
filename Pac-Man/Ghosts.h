#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"

//enum direction { GHOST_IDLE = 0, GHOST_MOVING_LEFT, GHOST_MOVING_RIGHT, GHOST_MOVING_UP, GHOST_MOVING_DOWN };

class Ghosts : public Entity
{
private:
    void initVariables();
 
    std::vector<std::pair<int, int>> steps;
    std::vector<sf::Vector2f> convertedSteps;
   // direction directions;
    TileMap& map;
    sf::Vector2f targetPosition;
public:
    Ghosts(float x, float y, sf::Texture& texture, TileMap& map);
    virtual ~Ghosts();
    //Accesors
    const sf::FloatRect getBounds();

    //Functions
    bool findPath( TileMap& map, sf::FloatRect playerPosition);
    void convertSteps();
    void setRedGhostDirection();
    bool hasReachedTarget(const float& dt);
    void setGhostDirection(int low, int high, int wallIntersect);
  

  
    virtual void update(const float& dt);

};

