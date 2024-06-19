#pragma once
#include "State.h"
#include "TileMap.h"
#include "Ghosts.h"



class GameState : public State
{
private:
	Player* player;
	TileMap map;
	Ghosts* ghost;
	sf::Sprite mapImage;
	sf::Font font;
	int direction; // 0 - left, 1 - right, 2 - up, 3 - down
	bool isWall = false;
	
	//Initializer functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initMapBackground();
	void initMap();
	void initFonts();

	
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	sf::FloatRect getGhostPosition();
	bool checkMapPlayerIntersect();
	void collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	bool teleportLeft();
	bool teleportRight();

	bool checkMoveLeft();
	bool checkMoveRight();
	bool checkMoveUp();
	bool checkMoveDown();
	
	void updateInput(const float& dt) override;
	void movementManager(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	
};

