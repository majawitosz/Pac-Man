#pragma once

#include "State.h"
#include "Button.h"
#include "RegisterState.h"
#include "LoginState.h"

class AccountState : public State
{
private:
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	bool loggedIn = false;
	std::string username;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	AccountState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~AccountState();

	//Modifiers
	void setLogInStatus();
	

	//Functions
	void initBackground();
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr) override;
};

