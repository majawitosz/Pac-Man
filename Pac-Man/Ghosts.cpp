#include "stdafx.h"
#include "Ghosts.h"

void Ghosts::initVariables()
{
	this->firstCollision = true;
}

Ghosts::Ghosts(float x, float y, sf::Texture& texture, TileMap& map) : map(map)
{
	
	this->initVariables();
	this->setPosition(x, y);
	this->sprite.setScale(0.75f, 0.75f);
	

	//this->createhitboxComponent(this->circle, 2.8f, 2.8f, 20.f, 20.f);
	this->createMovementComponent(100.f, 5.f, 3.f);
	this->movementComponent->stopVelocity();
	

	this->createAnimationComponent(texture);
	this->animationComponent->addAnimation("RIGHT", 20.f, 3, 2, 4, 2, 32, 32);
	this->animationComponent->addAnimation("IDLE", 20.f, 2, 2, 2, 2, 32, 32);
	this->animationComponent->addAnimation("LEFT", 20.f, 2, 2, 0, 2, 32, 32);
	this->animationComponent->addAnimation("UP", 20.f, 2, 1, 2, 0, 32, 32);
	this->animationComponent->addAnimation("DOWN", 20.f, 2, 3, 2, 4, 32, 32);
	
	//this->animationComponent->play("UP", 0);
}

Ghosts::~Ghosts()
{
}

const sf::FloatRect Ghosts::getBounds() 
{
	return this->sprite.getGlobalBounds();
}

void Ghosts::setFirstCollision(bool first)
{
	this->firstCollision = first;
}

const bool Ghosts::getFirstCollision() const
{
	return this->firstCollision;
}



//Functions


bool Ghosts::findPath(TileMap& map, sf::FloatRect playerPosition)
{
	this->map = map;
	map.clearPath();
	sf::FloatRect ghostPosition = this->getBounds();  // start position
	std::vector<std::pair<int, int>> previousCoordinates = {}; //row col
	std::vector<std::pair<int, int>> checkedCoordinates = {}; //row col
	
	bool foundPlayer = false;
	int stepNumber = 1;
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	bool foundGhostTile = false;
	bool foundPlayerTile = false;
	std::pair<int, int> playerTileCor;

	for (auto& x : map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (!foundGhostTile) {
					if (z.getGlobalBounds().intersects(ghostPosition)) {
						previousCoordinates.push_back(z.getCoordinates());
						foundGhostTile = true;
					}
					
				}
				if (!foundPlayerTile) {
					if (z.getGlobalBounds().intersects(playerPosition)) {
						playerTileCor = z.getCoordinates();
						foundPlayerTile = true;
					}
				}
			
			}
		}
	}

	while (!foundPlayer) {
	//std::cout << stepNumber << std::endl;
		for (auto& coord : previousCoordinates) {
			//std::cout << "x" << std::endl;
			for (auto& dir : directions) {
				std::pair<int, int> checkingTile;
				checkingTile.first = coord.first + dir[0];
				checkingTile.second = coord.second + dir[1];
				
				
				if (checkingTile.first >= 0 && checkingTile.first < 29 && checkingTile.second >= 0 && checkingTile.second < 32) {
					if (map.getTileByCoor(checkingTile)->getGlobalBounds().intersects(playerPosition)) {
						foundPlayer = true;
						break;
					}
					else if (map.getTileByCoor(checkingTile)->getPath() ==0){
						if (!map.getTileByCoor(checkingTile)->getIsWall()) {
							map.getTileByCoor(checkingTile)->setPath(stepNumber);

							std::cout << map.getTileByCoor(checkingTile)->getPath() << std::endl;

							checkedCoordinates.push_back(checkingTile);
						}
					}
				}
				
			}
			if (foundPlayer)
			
				break;
		}
		if (foundPlayer) {
		
			break;
		}
			
		previousCoordinates = {}; 
		previousCoordinates = checkedCoordinates;
		checkedCoordinates = {};
		stepNumber += 1;
		if (previousCoordinates.empty())
			break;
	}
	
	int currentStep = stepNumber;
	int currentX = playerTileCor.first;
	int currentY = playerTileCor.second;
	std::vector<std::pair<int, int>> steps;

	while (currentStep > 0) {
		for (auto& dir : directions) {
			std::pair<int, int> previousPair;
			previousPair.first = currentX - dir[0];
			previousPair.second = currentY - dir[1];

			std::cout << map.getTileByCoor(previousPair)->getPath() << std::endl;
			if (playerTileCor.first >= 0 && playerTileCor.first < 29 
				&& playerTileCor.second >= 0 && playerTileCor.second < 32 
				&& map.getTileByCoor(previousPair)->getPath() == currentStep 
				&& !map.getTileByCoor(previousPair)->getIsWall()) {

				steps.push_back(previousPair);
				//mapWithPath[prevY][prevX] = "*";
				currentX = previousPair.first;
				currentY = previousPair.second;
				break;
			}
		}
		--currentStep;
	}
	this->steps = steps;
	this->convertSteps();
	map.printMap(playerPosition, ghostPosition, steps);
	return true;
}

void Ghosts::convertSteps()
{
	this->convertedSteps.clear();

	for (auto it = this->steps.rbegin(); it != this->steps.rend(); ++it)
	{
		int row = it->first;
		int col = it->second;

		Tile tile = this->map.getMap()[row][col][0]; // Assuming z = 0
		float targetX = tile.getGlobalBounds().left;
		float targetY = tile.getGlobalBounds().top;

		sf::Vector2f targetPos(targetX, targetY);
		this->convertedSteps.push_back(targetPos);
	}

}

void Ghosts::setRedGhostDirection()
{
	if (!this->convertedSteps.empty()) {

		sf::FloatRect ghostBounds = this->getBounds();
		sf::Vector2f ghostPosition(ghostBounds.left, ghostBounds.top);
		//this->convertedSteps.pop_back();
		sf::Vector2f targetPosition = this->convertedSteps.front();
		this->targetPosition = targetPosition;

		if (ghostPosition.x < targetPosition.x) {
			this->movementComponent->setDirection(MOVING_RIGHT);
		 // Move right
		}
		if (ghostPosition.x > targetPosition.x) {
			this->movementComponent->setDirection(MOVING_LEFT);
			 // Move left
		}
		if (ghostPosition.y < targetPosition.y) {
			this->movementComponent->setDirection(MOVING_DOWN);
			// Move down
		}
		if (ghostPosition.y > targetPosition.y) {
			this->movementComponent->setDirection(MOVING_UP);
			// Move up
		}
	}
}

bool Ghosts::hasReachedTarget(const float& dt)
{
	//this->update(dt);
	sf::FloatRect ghostBounds = this->getPosition();
	sf::Vector2f ghostPosition(ghostBounds.left, ghostBounds.top);

	float targetX = this->targetPosition.x;
	float targetY = this->targetPosition.y;
	

	if (ghostPosition.x == targetX || ghostPosition.y == targetY) {
		this->getMovementComponent()->stopVelocity();
		this->convertedSteps.erase(this->convertedSteps.begin());
		return true;
	}

	return false;
}

int rand_int(int low, int high)
{
	static std::default_random_engine re{ std::random_device{}() };
	using Dist = std::uniform_int_distribution<int>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}

void Ghosts::setGhostDirection(int low, int high, int wallIntersect)
{
	int direction = rand_int(low, high); // 0 - left, 1 - right, 2 - up, 3 - down


	while (direction == wallIntersect) {
		direction = rand_int(low, high);
	}

	switch (direction) {
	case 0:
		this->getMovementComponent()->setDirection(MOVING_LEFT);
		break;
	case 1:
		this->getMovementComponent()->setDirection(MOVING_RIGHT);
		break;
	case 2:
		this->getMovementComponent()->setDirection(MOVING_UP);
		break;
	case 3:
		this->getMovementComponent()->setDirection(MOVING_DOWN);
		break;
	}
	
}


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


	//this->hitboxComponent->update();
}