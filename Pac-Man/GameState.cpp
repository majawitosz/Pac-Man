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
	this->player = new Player(230, 400, this->textures["PLAYER_SHEET"]);
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


void GameState::checkMapPlayerIntersect(const float& dt)
{

	//sf::FloatRect playerBounds = this->player->getHitboxBounds();
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
					this->collisionManagement(playerBounds, wallBounds, dt);
				

				}
			}
		}
	}
}

void GameState::collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds, const float& dt)
{

	// Left
	if (playerBounds.left < wallBounds.left + wallBounds.width && this->direction == 0)
	{
		this->player->setPosition(this->player->getPosition().left + 0.1f, this->player->getPosition().top);
		this->player->getMovementComponent()->stopVelocity();
		this->canMoveUp = true;
		this->canMoveDown = true;
		this->canMoveRight = true;
		this->canMoveLeft = false;
	}
	// Right
	else if ((playerBounds.left + playerBounds.width) > wallBounds.left && this->direction == 1)
	{
		this->player->setPosition(this->player->getPosition().left - 0.1f, this->player->getPosition().top);
		this->player->getMovementComponent()->stopVelocity();
		this->canMoveUp = true;
		this->canMoveDown = true;
		this->canMoveRight = false;
		this->canMoveLeft = true;
	}

	// Up
	if (playerBounds.top > wallBounds.top - wallBounds.height && this->direction == 2)
	{
		this->player->setPosition(this->player->getPosition().left, this->player->getPosition().top + 0.1f);
		this->player->getMovementComponent()->stopVelocity();
		this->canMoveUp = false;
		this->canMoveDown = true;
		this->canMoveRight = true;
		this->canMoveLeft = true;
	}
	// Down
	else if (playerBounds.top + playerBounds.height > wallBounds.top && this->direction == 3)
	{
		this->player->setPosition(this->player->getPosition().left, this->player->getPosition().top - 0.1f);
		this->player->getMovementComponent()->stopVelocity();
		this->canMoveUp = true;
		this->canMoveDown = false;
		this->canMoveRight = true;
		this->canMoveLeft = true;
	}
}

void GameState::resetCollisions()
{
	this->canMoveUp = true;
	this->canMoveDown = true;
	this->canMoveRight = true;
	this->canMoveLeft = true;
}

void GameState::updateInput(const float& dt)
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))) && this->canMoveLeft) {
		this->direction = 0;
		this->player->getMovementComponent()->addDirectionToStack(MOVING_LEFT);
		this->player->move(-1.f, 0.f, dt);
		this->resetCollisions();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))) && this->canMoveRight) {
		this->direction = 1;
		this->player->getMovementComponent()->addDirectionToStack(MOVING_RIGHT);
		this->player->move(1.f, 0.f, dt);
		this->resetCollisions();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) && this->canMoveUp) {
		this->direction = 2;
		this->player->getMovementComponent()->addDirectionToStack(MOVING_UP);
		this->player->move(0.f, -1.f, dt);
		this->resetCollisions();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))) && this->canMoveDown) {
		this->direction = 3;
		this->player->getMovementComponent()->addDirectionToStack(MOVING_DOWN);
		this->player->move(0.f, 1.f, dt);
		this->resetCollisions();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->endState();
	}
		
		
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->checkMapPlayerIntersect(dt);
	this->updateInput(dt);

	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->map.render(*target);
	
	//target->draw(this->mapImage);

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

