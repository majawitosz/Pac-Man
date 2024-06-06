#pragma once
#include "State.h"
#include "TileMap.h"



class GameState : public State
{
private:
	Player* player;
	TileMap map;
	sf::Sprite mapImage;
	//Initializer functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initMapBackground();
	void initMap();

	
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void checkMapPlayerIntersect();
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

