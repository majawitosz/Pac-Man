#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;
	

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createhitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,
		float width, float height);

	// Accessors
	virtual sf::FloatRect getHitboxBounds() const;
	virtual  MovementComponent* getMovementComponent();


	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual sf::FloatRect getPosition();
	
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

};

