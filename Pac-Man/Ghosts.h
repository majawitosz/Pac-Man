#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"
class Ghosts : public Entity
{
private:
    void initVariables();
    void initComponents();
   

public:
    Ghosts(float x, float y, sf::Texture& texture);
    virtual ~Ghosts();
    //Accesors
    const sf::FloatRect getBounds();

    //Functions
    void moveGhost(const float& dt, TileMap& map);
  
    virtual void update(const float& dt);

};

