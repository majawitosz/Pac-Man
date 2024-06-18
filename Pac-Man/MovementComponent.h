#pragma once




enum movementStates { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
//enum nextDirection { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;
	
	float maxVelocity;
	float acceleration;
	float deceleration;
	
	std::stack<movementStates> directionStack;


	sf::Vector2f velocity;

	//Initializaer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity,
		float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;
	std::string getLastDirection() const;
	const bool getMovingState(const short unsigned state) const;
	std::stack<movementStates>* getDirectionStack();


	//Functions
	void stopVelocity();

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
	void addDirectionToStack(movementStates direction);

	
	
};

