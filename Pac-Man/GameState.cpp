#include "stdafx.h"
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
}

void GameState::initPlayers()
{
	this->player = new Player(225, 370, this->textures["PLAYER_SHEET"]);
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

void GameState::collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds)
{
	
	// Left
	if (playerBounds.left < wallBounds.left + wallBounds.width && this->direction == 0)
	{
		int left = static_cast<int>(std::ceil(this->player->getPosition().left));
		float left1 = static_cast<float>(left);
	
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(left1, this->player->getPosition().top);
		
		isWall = true;
	}
	// Right
	if ((playerBounds.left + playerBounds.width) > wallBounds.left && this->direction == 1)
	{
		int right = static_cast<int>(std::floor(this->player->getPosition().left ));
		float right1 = static_cast<float>(right);
	
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(right1, this->player->getPosition().top);
	
		isWall = true;
	}

	// Up
	if (playerBounds.top > wallBounds.top - wallBounds.height && this->direction == 2)
	{
		int up = static_cast<int>(std::ceil(this->player->getPosition().top));
		float up1 = static_cast<float>(up);
		
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(this->player->getPosition().left, up1);
		isWall = true;
	}
	// Down
	if (playerBounds.top + playerBounds.height > wallBounds.top && this->direction == 3)
	{
		int down = static_cast<int>(std::floor(this->player->getPosition().top));
		float down1 = static_cast<float>(down);
		
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(this->player->getPosition().left, down1);
		isWall = true;
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


bool GameState::checkMoveLeft()
{
	
	sf::FloatRect nextPosition = this->player->getPosition();
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
bool GameState::checkMoveRight()
{
	sf::FloatRect nextPosition = this->player->getPosition();
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
bool GameState::checkMoveUp()
{
	sf::FloatRect nextPosition = this->player->getPosition();
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
bool GameState::checkMoveDown()
{
	sf::FloatRect nextPosition = this->player->getPosition();
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
			if (this->checkMoveLeft()) {
				this->teleportLeft();
				this->player->move(-1.f, 0.f, dt);
			}
			break;
		case 2:
			if (this->checkMoveRight()) {
				this->teleportRight();
				this->player->move(1.f, 0.f, dt);
			}
			break;
		case 3:
			if (this->checkMoveUp()) {
				this->player->move(0.f, -1.f, dt);
			}
			break;
		case 4:
			if (this->checkMoveDown()) {
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
	
	
	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->map.render(*target);
	
	target->draw(this->mapImage);

	this->player->render(*target);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);

	sf::FloatRect playerBounds = this->player->getHitboxBounds();
	sf::Text playerPosition;
	playerPosition.setPosition(190.f, 240.f);
	playerPosition.setFont(this->font);
	playerPosition.setCharacterSize(12);
	std::stringstream str;
	str << playerBounds.left << "  " << playerBounds.top;
	playerPosition.setString(str.str());

	target->draw(playerPosition);
	

}

