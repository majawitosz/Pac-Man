#include "stdafx.h"
#include "Ghosts.h"

void Ghosts::initVariables()
{
}

Ghosts::Ghosts(float x, float y, sf::Texture& texture)
{
	
	this->initVariables();
	this->setPosition(x, y);
	this->sprite.setScale(0.75f, 0.75f);

	//this->createhitboxComponent(this->circle, 2.8f, 2.8f, 20.f, 20.f);
	this->createMovementComponent(80.f, 5.f, 3.f);
	this->movementComponent->stopVelocity();


	this->createAnimationComponent(texture);
	//this->animationComponent->addAnimation("RIGHT", 20.f, 3, 3, 6, 3, 32, 32);
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 0, 0, 32, 32);
	//this->animationComponent->addAnimation("LEFT", 20.f, 3, 3, 0, 3, 32, 32);
	//this->animationComponent->addAnimation("UP", 20.f, 3, 3, 3, 0, 32, 32);
	//this->animationComponent->addAnimation("DOWN", 20.f, 3, 3, 3, 6, 32, 32);
	//this->animationComponent->play("IDLE", 0);
}

Ghosts::~Ghosts()
{
}

const sf::FloatRect Ghosts::getBounds() 
{
	return this->sprite.getGlobalBounds();
}



//Functions
void Ghosts::update(const float& dt)
{
	this->movementComponent->update(dt);


	if (this->movementComponent->getMovingState(MOVING_RIGHT))
		this->animationComponent->play("RIGHT", dt);
	else if (this->movementComponent->getMovingState(MOVING_LEFT))
		this->animationComponent->play("LEFT", dt);
	else if (this->movementComponent->getMovingState(MOVING_DOWN))
		this->animationComponent->play("DOWN", dt);
	else if (this->movementComponent->getMovingState(MOVING_UP))
		this->animationComponent->play("UP", dt);


	this->hitboxComponent->update();
}

void Ghosts::moveGhost(const float& dt, TileMap& map)
{
	sf::FloatRect ghostPosition = this->getBounds();
	
	for (auto& x : map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				//if (z.getGlobalBounds().intersects(ghostPosition))

			}
		}
	}
}

//void Ghosts::render(sf::RenderTarget& target)
//{
//	target.draw(this->circle);
//
//	if (this->hitboxComponent)
//		this->hitboxComponent->render(target);
//}