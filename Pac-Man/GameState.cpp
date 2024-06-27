﻿#include "stdafx.h"
#include "GameState.h"

std::mutex gameMutex;

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

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Pac-Man/pm_sheet1.png"))
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
	if (!this->textures["PM_END"].loadFromFile("Resources/Images/Pac-Man/pm_end.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_END_TEXTURE";
	}
	if (!this->textures["PM_LIVES"].loadFromFile("Resources/Images/Pac-Man/pm_lives.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_LIVES_TEXTURE";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(220, 420, this->textures["PLAYER_SHEET"], this->textures["PM_END"]);
	this->blueGhost = new Ghosts(225, 270, this->textures["BLUE_GHOST"], this->map);
	this->redGhost = new Ghosts(225, 270, this->textures["RED_GHOST"], this->map);
	this->pinkGhost = new Ghosts(225, 270, this->textures["PINK_GHOST"], this->map);
	this->yellowGhost = new Ghosts(225, 270, this->textures["YELLOW_GHOST"], this->map);
	
}

void GameState::initMapBackground()
{

	this->mapImage.setTexture(this->textures["MAP"]);
	this->mapImage.setPosition(0.f, 48.f);
		
}

void GameState::initPacManLives()
{
	for (int i = 0; i < 3; ++i) {
		sf::Sprite sprite;
		sprite.setTexture(this->textures["PM_LIVES"]);
		//sprite.setScale(0.5f, 0.5f); // Scale the sprite if needed
		sprite.setPosition(20.f + i * 30.f, this->window->getSize().y - 40.f); // Adjust positions as needed
		this->pacManLivesSprites.push_back(sprite);
	}
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}

}

void GameState::initMap()
{
	map.loadMapFromFile("Resources/Map/map.txt");
	map.loadMapDotsFromFile("Resources/Map/dots.txt");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string userName)
	: State(window, supportedKeys, states), caughtPacMan(false)
{
	this->username = userName;
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->initMapBackground();
	this->initMap();
	this->initFonts();
	this->initPacManLives();
	
}

GameState::~GameState()
{
	delete this->player;
	delete this->blueGhost;
	delete this->redGhost;
	delete this->pinkGhost;
	delete this->yellowGhost;
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
					sf::FloatRect nextPosition;
					this->collisionManagement(playerBounds, wallBounds);
					

				/*	if (this->player->getMovementComponent()->getDirection() == MOVING_LEFT) {
						nextPosition.left = (wallBounds.left + wallBounds.width) - playerBounds.left;
						nextPosition.top = playerBounds.top;

						this->player->getMovementComponent()->stopVelocity();
						this->player->setPosition(nextPosition.left, nextPosition.top);
						isWall = true;
					}
					if (this->player->getMovementComponent()->getDirection() == MOVING_RIGHT) {
						nextPosition.left = wallBounds.left  - playerBounds.left;
						nextPosition.top = playerBounds.top;

						this->player->getMovementComponent()->stopVelocity();
						this->player->setPosition(nextPosition.left, nextPosition.top);
						isWall = true;
					}*/
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
		//isWall = true;
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
		//isWall = true;
	}

	// Up
	if (playerBounds.top > wallBounds.top - wallBounds.height && this->direction == 2)
	{
		int up = static_cast<int>(std::ceil(this->player->getPosition().top));
		up = roundToNearestMultipleOf16(up) + 3;
		float up1 = static_cast<float>(up);
		
		this->player->getMovementComponent()->stopVelocity();
		this->player->setPosition(this->player->getPosition().left, up1);
		//isWall = true;
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
		//isWall = true;
		//std::cout << "Down: " << down1 << std::endl;
	}
	//isWall = false;
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

void GameState::eatDots()
{
	sf::FloatRect playerBounds = this->player->getPosition();
	for (auto& x : this->map.getDots()) {
		for (auto& y : x) {
			for (auto& z : y) {
				if (!z.getIsEaten() && z.getGlobalBounds().intersects(playerBounds) && !z.getBigDot()) {
					z.setEaten(true);
					this->score += 10;
				}
				else if (z.getBigDot() && z.getGlobalBounds().intersects(playerBounds)) {
					z.setBigDot(false);
					z.setEaten(true);
					this->score += 50;
				}
			}
		}
	}
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
					ghost->setFirstCollision(true);
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
		ghost->setGhostDirection(0, 3, 1);
	}
	// Up
	if (ghostBounds.top > wallBounds.top - wallBounds.height && ghost->getMovementComponent()->getDirection() == MOVING_UP)
	{
		if (ghost->getFirstCollision()) {
			ghost->setGhostDirection(0, 1, 3);
			ghost->setFirstCollision(false);
		}
		else {
			int up = static_cast<int>(std::ceil(ghost->getPosition().top));
			up = roundToNearestMultipleOf16(up) + 3;
			float up1 = static_cast<float>(up);
			ghost->getMovementComponent()->stopVelocity();
			ghost->setPosition(ghost->getPosition().left, up1);
			/*if (!this->ghostFree) {
				ghost->setGhostDirection(0, 1, 3);
			}
			this->ghostFree = true;*/
			ghost->setGhostDirection(0, 3, 2);
		}
	}
	// Down
	if (ghostBounds.top + ghostBounds.height > wallBounds.top && ghost->getMovementComponent()->getDirection() == MOVING_DOWN)
	{
		int down = static_cast<int>(std::floor(ghost->getPosition().top));
		down = roundToNearestMultipleOf16(down) + 3;
		float down1 = static_cast<float>(down);
		ghost->getMovementComponent()->stopVelocity();
		ghost->setPosition(ghost->getPosition().left, down1);
		ghost->setGhostDirection(0, 3 ,3);
	}
}

void GameState::moveGhost(Ghosts* ghost, const float& dt)
{
	
	if (this->checkPacManGhostCollision(ghost)) {
		
		this->restartGame();
		
	}
	if (!checkIfGhostMoves(ghost)) {
		ghost->setGhostDirection(0, 3, 5);
		
	}
	if (!this->checkMapGhostIntersect(ghost)  && !caughtPacMan) {
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
}

bool GameState::checkPacManGhostCollision(Ghosts* ghost)
{
	sf::FloatRect playerPosition = this->player->getHitboxBounds();
	sf::FloatRect ghostPosition = ghost->getPosition();

	if (playerPosition.intersects(ghostPosition)) {
		this->caughtPacMan = true;
		return true;
	}

	return false;
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

void GameState::display()
{
	this->highScore.setPosition(150.f, 10.f);
	this->highScore.setFont(this->font);
	this->highScore.setCharacterSize(20);
	std::stringstream ss1;
	ss1 << "HIGH SCORE";
	this->highScore.setString(ss1.str());

	this->scoreText.setPosition(20.f, 16.f);
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(10);
	std::stringstream ss2;
	ss2 << "score";
	this->scoreText.setString(ss2.str());

	this->scoreTextPoints.setPosition(20.f, 32.f);
	this->scoreTextPoints.setFont(this->font);
	this->scoreTextPoints.setCharacterSize(12);
	std::stringstream ss3;
	ss3 << this->score;
	this->scoreTextPoints.setString(ss3.str());

	
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
		if (this->username == "") {
			this->sendRequest("anonymousUser", this->score);
		}
		else {
			this->sendRequest(username, this->score);
		}
		this->endState();
	}		
}

void GameState::movementManager(const float& dt)
{

	if (!this->checkMapPlayerIntersect()) {
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
		this->eatDots();
		if (!this->caughtPacMan) {
			this->startGhosts();
			this->moveGhost(this->blueGhost, dt);
			this->moveGhost(this->redGhost, dt);
			this->moveGhost(this->pinkGhost, dt);
			this->moveGhost(this->yellowGhost, dt);
			this->player->update(dt);
			this->blueGhost->update(dt);
			this->redGhost->update(dt);
			this->pinkGhost->update(dt);
			this->yellowGhost->update(dt);
		}
		this->display();	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->map.render(*target);
	
	target->draw(this->mapImage);
	
	this->map.renderDots(*target);

	this->player->render(*target);
	if (!caughtPacMan) {
		this->redGhost->render(*target);
		this->blueGhost->render(*target);
		this->pinkGhost->render(*target);
		this->yellowGhost->render(*target);
	}
	target->draw(this->scoreTextPoints);
	target->draw(this->scoreText);
	target->draw(this->highScore);
	
	for (const auto& sprite : this->pacManLivesSprites) {
		target->draw(sprite);
	}	
}

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

void GameState::sendRequest(const std::string& username, int score)
{
	CURL* curl;
	CURLcode res;
	std::string result;
	long httpCode = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		std::string url = "http://localhost:3000/addScore";
		std::string postFields = "username=" + username + "&score=" + std::to_string(score);

		// Set the URL
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Set POST request
		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		// Set POST fields
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

		// Set the write function callback
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);

		// Set the string to store the result
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

		// Optional: Set verbose mode to 1 (for debugging)
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		// Perform the request
		res = curl_easy_perform(curl);

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

		// Check for errors
		if (res != CURLE_OK) {
			std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			std::cout << "Response: " << result << std::endl;
			// handleResponse(result, httpCode); // Implement this function to handle the response
		}

		// Cleanup
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
}

void GameState::restartGame()
{

	this->player->getMovementComponent()->stopVelocity();
	this->blueGhost->getMovementComponent()->stopVelocity();
	this->redGhost->getMovementComponent()->stopVelocity();
	this->pinkGhost->getMovementComponent()->stopVelocity();
	this->yellowGhost->getMovementComponent()->stopVelocity();
	this->player->getMovementComponent()->setDirection(IDLE);
	sf::sleep(sf::milliseconds(500));
	
	
	if (!this->pacManLivesSprites.empty())
		this->pacManLivesSprites.pop_back();

	if (this->lives > 0) {
		this->lives -= 1;
		this->player->setPosition(220, 420);
		this->blueGhost->setPosition(225, 270);
		this->redGhost->setPosition(225, 270);
		this->pinkGhost->setPosition(225, 270);
		this->yellowGhost->setPosition(225, 270);
		this->caughtPacMan = false;
	}
	else if (this->lives == 0) {


		this->states->push(new GameOverState(this->window, this->states));
		this->endState();
	}
}

