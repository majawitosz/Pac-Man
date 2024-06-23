﻿#include "stdafx.h"
#include "GameState.h"


//Initializer functions
void GameState::initKeybinds()
{
	std::ifstream file("Config/gamestate_keybinds.ini");

	if (file.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (file >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file.close();

}

void GameState::initTextures()
{

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Pac-Man/pm_sheet.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["MAP"].loadFromFile("Resources/Images/Backgrounds/map.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAP_TEXTURE";
	}
	if (!this->textures["RED_GHOST"].loadFromFile("Resources/Images/Ghosts/red_ghost.png")) 
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_GHOST_TEXTURE";
	}
	if (!this->textures["BLUE_GHOST"].loadFromFile("Resources/Images/Ghosts/blue_ghost.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_GHOST_TEXTURE";
	}
	if (!this->textures["PINK_GHOST"].loadFromFile("Resources/Images/Ghosts/pink_ghost.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_GHOST_TEXTURE";
	}
	if (!this->textures["YELLOW_GHOST"].loadFromFile("Resources/Images/Ghosts/yellow_ghost.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_GHOST_TEXTURE";
	}


}

void GameState::initPlayers()
{
	this->player = new Player(225, 370, this->textures["PLAYER_SHEET"]);
	this->blueGhost = new Ghosts(220, 220, this->textures["BLUE_GHOST"], this->map);
	this->redGhost = new Ghosts(220, 220, this->textures["RED_GHOST"], this->map);
	this->pinkGhost = new Ghosts(220, 220, this->textures["PINK_GHOST"], this->map);
	this->yellowGhost = new Ghosts(220, 220, this->textures["YELLOW_GHOST"], this->map);
	
}

void GameState::initMapBackground()
{
	this->mapImage.setTexture(this->textures["MAP"]);

		
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Minecraft.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}

}

void GameState::initMap()
{
	map.loadMapFromFile("Resources/Map/map.txt");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->initMapBackground();
	this->initMap();
	this->initFonts();
}

GameState::~GameState()
{
	delete this->player;
}

bool GameState::checkMapPlayerIntersect()
{
	sf::FloatRect playerBounds = this->player->getPosition();

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(playerBounds))
				{
					sf::FloatRect wallBounds = z.getGlobalBounds();
					this->collisionManagement(playerBounds, wallBounds);
					return true;
				
				}
			}
		}
	}
	return false;
}

int roundToNearestMultipleOf16(int num) {
	int lowerMultiple = (num / 16) * 16;
	int upperMultiple = ((num + 15) / 16) * 16;

	// Sprawdzenie, która z wielokrotności jest bliżej
	if (std::abs(num - lowerMultiple) <= std::abs(num - upperMultiple)) {
		return lowerMultiple;
	}
	else {
		return upperMultiple;
	}
}

void GameState::collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	
	// Left
	if (playerBounds.left < wallBounds.left + wallBounds.width && this->player->getMovementComponent()->getDirection() == MOVING_LEFT)
	{
		int left = static_cast<int>(std::ceil(this->player->getPosition().left));
		left = roundToNearestMultipleOf16(left) + 3;
		
		float left1 = static_cast<float>(left);
	
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(left1, this->player->getPosition().top);
		//std::cout << "Left: " << left1 << std::endl;
		isWall = true;
		//if (this->ghost->findPath(map, this->player->getPosition()))
		//	this->foundPath = true;
		
	}
	// Right
	if ((playerBounds.left + playerBounds.width) > wallBounds.left && this->direction == 1)
	{
		int right = static_cast<int>(std::floor(this->player->getPosition().left));
		right = roundToNearestMultipleOf16(right) + 3;
		float right1 = static_cast<float>(right);
	
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(right1, this->player->getPosition().top);
		//std::cout << "Right: " << right1 << std::endl;
		isWall = true;
	}

	// Up
	if (playerBounds.top > wallBounds.top - wallBounds.height && this->direction == 2)
	{
		int up = static_cast<int>(std::ceil(this->player->getPosition().top));
		up = roundToNearestMultipleOf16(up) + 3;
		float up1 = static_cast<float>(up);
		
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(this->player->getPosition().left, up1);
		isWall = true;
		//std::cout << "Up: " << up1 << std::endl;
	}
	// Down
	if (playerBounds.top + playerBounds.height > wallBounds.top && this->direction == 3)
	{
		int down = static_cast<int>(std::floor(this->player->getPosition().top));
		down = roundToNearestMultipleOf16(down) + 3;
		float down1 = static_cast<float>(down);
		
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(this->player->getPosition().left, down1);
		isWall = true;
		//std::cout << "Down: " << down1 << std::endl;
	}
	isWall = false;
}

bool GameState::teleportLeft()
{
	sf::FloatRect playerBounds = this->player->getPosition();
	sf::FloatRect nextPosition = this->player->getPosition();
	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsTunnel() && z.getGlobalBounds().intersects(playerBounds))
				{
					if(z.getGlobalBounds().left < playerBounds.left)
						nextPosition.left = this->map.getWidth() - playerBounds.left - 1;
						this->player->setPosition(nextPosition.left, nextPosition.top);
					return true;
				}
				
			}
		}
	}
	
	return false;
}

bool GameState::teleportRight()
{
	sf::FloatRect playerBounds = this->player->getPosition();
	sf::FloatRect nextPosition = this->player->getPosition();
	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsTunnel() && z.getGlobalBounds().intersects(playerBounds))
				{
					if (z.getGlobalBounds().left > playerBounds.left)
						nextPosition.left = 1;
					this->player->setPosition(nextPosition.left, nextPosition.top);
					return true;
				}

			}
		}
	}

	return false;
}

void GameState::moveRedGhost(const float& dt)
{

	
	//wszytsko w if Ghost found Player jak tak to wyowalnie funkcji
	if (!this->redGhost->hasReachedTarget(dt)) {
		switch (this->redGhost->getMovementComponent()->getDirection())
		{
		case 1:
			this->redGhost->move(-1.f, 0.f, dt);
			break;
		default:
			//this->ghost->getMovementComponent()->stopVelocity();
			break;
		}
	}
	

}

void GameState::updateRedGhost()
{
	/*switch (this->ghost->setRedGhostDirection()) {
	case 1:
		this->ghost->getMovementComponent()->setDirection(MOVING_LEFT);
		break;
	case 2:
		this->ghost->getMovementComponent()->setDirection(MOVING_RIGHT);
		break;
	case 3: 
		this->ghost->getMovementComponent()->setDirection(MOVING_UP);
		break;
	case 4:
		this->ghost->getMovementComponent()->setDirection(MOVING_DOWN);
		break;
	default:
		break;
	}*/
	
	
}

void GameState::startGhosts()
{
	if (!this->startedGhost) {
		this->redGhost->getMovementComponent()->setDirection(MOVING_UP);
		this->blueGhost->getMovementComponent()->setDirection(MOVING_UP);
		this->pinkGhost->getMovementComponent()->setDirection(MOVING_UP);
		this->yellowGhost->getMovementComponent()->setDirection(MOVING_UP);
	}
	this->startedGhost = true;
}

bool GameState::checkMapGhostIntersect(Ghosts* ghost)
{

	sf::FloatRect ghostBounds = ghost->getPosition();

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(ghostBounds))
				{
					//std::cout << "sciana";
					sf::FloatRect wallBounds = z.getGlobalBounds();
					this->ghostCollisionManagement(ghostBounds, wallBounds, ghost);
					return true;

				}
			}
		}
	}
	return false;
}

void GameState::ghostCollisionManagement(sf::FloatRect ghostBounds, sf::FloatRect wallBounds, Ghosts* ghost)
{
	
	if (ghostBounds.left < wallBounds.left + wallBounds.width && ghost->getMovementComponent()->getDirection() == MOVING_LEFT)
	{
		int left = static_cast<int>(std::ceil(ghost->getPosition().left));
		left = roundToNearestMultipleOf16(left) + 3;

		float left1 = static_cast<float>(left);

		ghost->getMovementComponent()->stopVelocity();
		ghost->setPosition(left1, ghost->getPosition().top);
		std::cout << "Left: " << left1 << std::endl;
		isWall = true;
		//if (this->ghost->findPath(map, this->player->getPosition()))
		//	this->foundPath = true;


		ghost->setGhostDirection(0, 3,0);
	}
	// Right
	if ((ghostBounds.left + ghostBounds.width) > wallBounds.left && ghost->getMovementComponent()->getDirection() == MOVING_RIGHT)
	{
		int right = static_cast<int>(std::floor(ghost->getPosition().left));
		right = roundToNearestMultipleOf16(right) + 3;
		float right1 = static_cast<float>(right);

		ghost->getMovementComponent()->stopVelocity();
		ghost->setPosition(right1, ghost->getPosition().top);
		std::cout << "Right: " << right1 << std::endl;
		isWall = true;
		ghost->setGhostDirection(0, 3, 1);
	}

	// Up
	if (ghostBounds.top > wallBounds.top - wallBounds.height && ghost->getMovementComponent()->getDirection() == MOVING_UP)
	{
		int up = static_cast<int>(std::ceil(ghost->getPosition().top));
		up = roundToNearestMultipleOf16(up) + 3;
		float up1 = static_cast<float>(up);

		ghost->getMovementComponent()->stopVelocity();
		ghost->setPosition(ghost->getPosition().left, up1);
		isWall = true;
		std::cout << "Up: " << up1 << std::endl;
		if (!this->ghostFree) {
			ghost->setGhostDirection(0, 1, 3);
		}
		this->ghostFree = true;
		ghost->setGhostDirection(0, 3, 2);
	}
	// Down
	if (ghostBounds.top + ghostBounds.height > wallBounds.top && ghost->getMovementComponent()->getDirection() == MOVING_DOWN)
	{
		int down = static_cast<int>(std::floor(ghost->getPosition().top));
		down = roundToNearestMultipleOf16(down) + 3;
		float down1 = static_cast<float>(down);

		ghost->getMovementComponent()->stopVelocity();
		ghost->setPosition(ghost->getPosition().left, down1);
		isWall = true;
		std::cout << "Down: " << down1 << std::endl;
		ghost->setGhostDirection(0, 3 ,3);
	}
	isWall = false;
	
}

void GameState::moveGhost(Ghosts* ghost, const float& dt)
{
	if (!checkIfGhostMoves(ghost)) {
		ghost->setGhostDirection(0, 3, 5);
	}
	if (!this->checkMapGhostIntersect(ghost) && !isWall) {
		//this->updateGhost(dt);

		switch (ghost->getMovementComponent()->getDirection())
		{
		case 1:
			if (this->checkMoveLeft(ghost)) {
				//this->teleportLeft();
				ghost->move(-1.f, 0.f, dt);
			}
			break;
		case 2:
			if (this->checkMoveRight(ghost)) {
				//this->teleportRight();
				ghost->move(1.f, 0.f, dt);
			}
			break;
		case 3:
			if (this->checkMoveUp(ghost)) {
				ghost->move(0.f, -1.f, dt);
			}
			break;
		case 4:
			if (this->checkMoveDown(ghost)) {
				ghost->move(0.f, 1.f, dt);
			}
			break;
		default:
			
			break;
		}

	}
	//else {
	//	this->blueGhost->setGhostDirection(0, 3);
	//}

}


bool GameState::checkMoveLeft(Entity *entity)
{
	
	sf::FloatRect nextPosition = entity->getPosition();
	nextPosition.left -= nextPosition.width;

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(nextPosition))
				{	
					return false;
				}
			}
		}
	}
	
	return true;
}
bool GameState::checkMoveRight(Entity* entity)
{
	sf::FloatRect nextPosition = entity->getPosition();
	nextPosition.left += nextPosition.width;

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(nextPosition))
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool GameState::checkMoveUp(Entity* entity)
{
	sf::FloatRect nextPosition = entity->getPosition();
	nextPosition.top -= nextPosition.height;
	

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(nextPosition))
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool GameState::checkMoveDown(Entity* entity)
{
	sf::FloatRect nextPosition = entity->getPosition();
	nextPosition.top += nextPosition.width;

	for (auto& x : this->map.getMap())
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getIsWall() && z.getGlobalBounds().intersects(nextPosition))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool GameState::checkIfGhostMoves(Ghosts* ghost)
{
	if (ghost->getMovementComponent()->getVelocity().x == 0.f && ghost->getMovementComponent()->getVelocity().y == 0.f) {
		return false;
	}
	return true;
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->direction = 0;
		this->player->getMovementComponent()->setDirection(MOVING_LEFT);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->direction = 1;
		this->player->getMovementComponent()->setDirection(MOVING_RIGHT);
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->direction = 2;
		this->player->getMovementComponent()->setDirection(MOVING_UP);
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->direction = 3;
		this->player->getMovementComponent()->setDirection(MOVING_DOWN);
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->endState();
	}		
}

void GameState::movementManager(const float& dt)
{
	if (!this->checkMapPlayerIntersect() && !isWall ) {
		switch (this->player->getMovementComponent()->getDirection())
		{
		case 1:
			if (this->checkMoveLeft(this->player)) {
				this->teleportLeft();
				this->player->move(-1.f, 0.f, dt);
			}
			break;
		case 2:
			if (this->checkMoveRight(this->player)) {
				this->teleportRight();
				this->player->move(1.f, 0.f, dt);
			}
			break;
		case 3:
			if (this->checkMoveUp(this->player)) {
				this->player->move(0.f, -1.f, dt);
			}
			break;
		case 4:
			if (this->checkMoveDown(this->player)) {
				this->player->move(0.f, 1.f, dt);
			}
			break;
		default:
			break;
		}
	}
		
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->movementManager(dt);
	this->updateInput(dt);
	
	//this->moveRedGhost(dt);
	//this->updateRedGhost();
	// 
	//this->updateGhost(dt);
	this->startGhosts();
	this->moveGhost(this->blueGhost, dt);
	this->moveGhost(this->redGhost, dt);
	this->moveGhost(this->pinkGhost, dt);
	this->moveGhost(this->yellowGhost, dt);
	
	this->blueGhost->update(dt);
	this->redGhost->update(dt);
	this->pinkGhost->update(dt);
	this->yellowGhost->update(dt);
	
	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->map.render(*target);
	
	target->draw(this->mapImage);

	this->player->render(*target);
	this->redGhost->render(*target);
	this->blueGhost->render(*target);
	this->pinkGhost->render(*target);
	this->yellowGhost->render(*target);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
	
}

