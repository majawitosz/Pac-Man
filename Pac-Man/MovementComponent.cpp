#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float decerelation)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions
void MovementComponent::setVelocityOnStart()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}


const bool MovementComponent::getMovingState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;

	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;
		break;

	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;
		break;

	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}


void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration

	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;


}


void MovementComponent::update(const float& dt)
{
	//Deceleration


	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity
}
