#pragma once

#include "State.h"
#include "AccountState.h"

class AccountState;

class ScoreState : public State
{
private:
	AccountState* accountState;
	sf::Event event;
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font font2;
	std::map<std::string, Button*> buttons;
	

	sf::Text serverInfo;
	std::string serverInformation;
	bool displayInfo = false;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	ScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states, AccountState* accountState);
	virtual ~ScoreState();

	//Functions
	void initBackground();
	void updateButtons();
	void sendRequest();
	void handleResponse(const std::string& response, long httpCode);

	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr) override;
	

};


