#pragma once
#include "Entity.h"
#include "TileMap.h"

class Player :
    public Entity
{
private:
    //Variables

    //Initializaer functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();
    //Functions
   
    virtual void update(const float& dt);

};

