#pragma once

#include "State.h"
#include "Button.h"
#include "RegisterState.h"
#include "LoginState.h"
#include "MainMenuState.h"

class MainMenuState;

class AccountState : public State
{
private:
	MainMenuState* mainMenuState;
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

	

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	AccountState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, MainMenuState* mainmenustate);
	virtual ~AccountState();

	
	//Functions
	void initBackground();
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr) override;
};

