#pragma once
#include "State.h"
#include "TileMap.h"



class GameState : public State
{
private:
	Player* player;

	//Initializer functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

	TileMap map;
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

