#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(0.f, 0.f)
{
	this->directionStack.push(IDLE);
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
void MovementComponent::stopVelocity()
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

std::stack<movementStates>* MovementComponent::getDirectionStack()
{
	if (!this->directionStack.empty()) {
		return &directionStack;
	}
	return nullptr;
}




std::string MovementComponent::getLastDirection() const
{

	std::string lastDirection;
	if (!this->directionStack.empty())
		switch (this->directionStack.top()) {
		case 1:
			lastDirection = "LEFT";
			break;
		case 2:
			lastDirection = "RIGHT";
			break;
		case 3:
			lastDirection = "UP";
			break;
		case 4:
			lastDirection = "DOWN";
		
		}
	return lastDirection;
	
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

void MovementComponent::addDirectionToStack(movementStates direction)
{
	this->directionStack.push(direction);
}




