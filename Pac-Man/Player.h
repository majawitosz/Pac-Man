#pragma once
#include "Entity.h"
#include "TileMap.h"

class Player :
    public Entity
{
private:
    //Variables
    AnimationComponent* endAnimationComponent;
    bool endGame;
    //Initializaer functions
    void initVariables();
    bool finishedAnimation = false;
   

public:
    Player(float x, float y, sf::Texture& texture, sf::Texture& endTexture);
    virtual ~Player();

    //Accessors
    void setEndGame(bool ifEndGame);


    //Functions
    virtual void update(const float& dt);

};

