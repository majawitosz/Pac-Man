#pragma once
#include "Player.h"


class State
{
protected:

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::stack<State*>* states;
	bool quit;
	//bool logedIn;
	//std::string userName;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	virtual void endState();
	//virtual bool& getLoginStatus();
	//virtual void setLoginStatus(bool login);
	//virtual void setUsername(std::string username);
	//virtual std::string getUsername();
	//	virtual void endStateUpdate() = 0;

	virtual void updateMousePosition();

	virtual void handleEvent(sf::Event event);
	virtual void updateInput(const float& dt) = 0;



	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

};


