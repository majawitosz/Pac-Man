#pragma once
#include "State.h"
#include "TileMap.h"



class GameState : public State
{
private:
	Player* player;
	TileMap map;
	sf::Sprite mapImage;
	sf::Font font;
	int direction; // 0 - left, 1 - right, 2 - up, 3 - down
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	
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
	void checkMapPlayerIntersect(const float& dt);
	void collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds, const float& dt);
	void resetCollisions();
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	
};

