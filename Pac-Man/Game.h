#pragma once
#include "MainMenuState.h"

class Game
{
private:
	//Variables
	//Window
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event event;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	std::map<std::string, int> supportedKeys;

	//Time
	sf::Clock dtClock;
	float dt;

	//States
	std::stack<State*> states;

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

public:
	//Constructor and deconstructor
	Game();
	virtual ~Game();

	//Mofifiers
	void setDtclock();

	//Fucntions
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void endGame();
};

