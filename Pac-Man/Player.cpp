#include "Player.h"


//Initializaer functions
void Player::initVariables()
{

}

void Player::initComponents()
{


}

Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createhitboxComponent(this->sprite, 0.f, 0.f, 32.f, 32.f);
	this->createMovementComponent(100.f, 5.f, 3.f);
	this->movementComponent->setVelocityOnStart();
	this->createAnimationComponent(texture);
	this->animationComponent->addAnimation("RIGHT", 20.f, 3, 0, 4, 0, 32, 32);
	this->animationComponent->addAnimation("IDLE", 20.f, 3, 0, 3, 0, 32, 32);
	this->animationComponent->addAnimation("LEFT", 20.f, 3, 0, -4, 0, 32, 32);

}

Player::~Player()
{
}

//Functions
void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	if (this->movementComponent->getMovingState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getMovingState(MOVING_RIGHT))
		this->animationComponent->play("RIGHT", dt);
	else if (this->movementComponent->getMovingState(MOVING_LEFT))
		this->animationComponent->play("LEFT", dt);
	else if (this->movementComponent->getMovingState(MOVING_DOWN))
		this->animationComponent->play("DOWN", dt);
	else if (this->movementComponent->getMovingState(MOVING_UP))
		this->animationComponent->play("UP", dt);

	//this->hitboxComponent->update();
}

