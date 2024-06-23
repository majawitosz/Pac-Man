#include "stdafx.h"
#include "Player.h"


//Initializaer functions
void Player::initVariables()
{
	this->endAnimationComponent = nullptr;
	this->endGame = false;
}



Player::Player(float x, float y, sf::Texture& texture, sf::Texture& endTexture)
{
	this->initVariables();

	this->setPosition(x, y);
	this->sprite.setScale(0.75f, 0.75f);
	
	this->createhitboxComponent(this->sprite, 10.f, 10.f, 4.f , 4.f);
	this->createMovementComponent(100.f, 5.f, 3.f);
	this->movementComponent->stopVelocity();
	
	this->createAnimationComponent(texture);
	
	
	//this->endAnimationComponent = new AnimationComponent(this->sprite, endTexture);

	//this->endAnimationComponent->addAnimation("END", 20.f, 0, 0, 11, 0, 32, 32);
	this->animationComponent->addAnimation("END", 20.f, 8, 3, 17, 4, 32, 32);
	

	this->animationComponent->addAnimation("RIGHT", 20.f, 3, 3, 6, 3, 32, 32);
	this->animationComponent->addAnimation("IDLE", 20.f, 3, 3, 3, 3, 32, 32);
	this->animationComponent->addAnimation("LEFT", 20.f, 3, 3, 0, 3, 32, 32);
	this->animationComponent->addAnimation("UP", 20.f, 3, 3, 3, 0, 32, 32);
	this->animationComponent->addAnimation("DOWN", 20.f, 3, 3, 3, 6, 32, 32);
	this->animationComponent->play("IDLE", 0);
}

Player::~Player()
{
	delete this->endAnimationComponent;
}

void Player::setEndGame(bool ifEndGame)
{
	this->endGame = ifEndGame;
}



//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	
	if (this->endGame) {
		this->animationComponent->play("END", dt);
		
	}
	if (this->movementComponent->getMovingState(MOVING_RIGHT)) {
		this->animationComponent->play("RIGHT", dt);
		
	}
	else if (this->movementComponent->getMovingState(MOVING_LEFT)) {
		this->animationComponent->play("LEFT", dt);
		
	}
	else if (this->movementComponent->getMovingState(MOVING_DOWN)) {
		this->animationComponent->play("DOWN", dt);
		
	}
	else if (this->movementComponent->getMovingState(MOVING_UP)) {
		this->animationComponent->play("UP", dt);
		
	}
			
	this->hitboxComponent->update();
}

