#pragma once

#include "GameState.h"
#include "Button.h"
#include "AccountState.h"

class MainMenuState : public State
{
private:

	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;
	sf::Text loginStatus;
	
	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();



	//Functions

	void initBackground();
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr) override;
};

