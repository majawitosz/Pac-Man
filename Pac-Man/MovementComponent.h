#pragma once




enum movementStates { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializaer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity,
		float acceleration, float decerelation);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;


	//Functions
	void setVelocityOnStart();

	const bool getMovingState(const short unsigned state) const;

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

