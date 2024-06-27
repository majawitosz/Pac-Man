#pragma once

#include "State.h"
#include "Button.h"
#include "TextInput.h"
#include "AccountState.h"

class AccountState;
class MainMenuState;

class LoginState : public State
{
private:
	AccountState* accountState;
	MainMenuState* mainMenuState;
	sf::Event event;
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font font2;
	std::map<std::string, Button*> buttons;
	std::map<std::string, TextInput*> textInputs;
	std::vector< sf::Text> info;
	sf::Text serverInfo;
	std::string serverInformation;
	bool displayInfo = false;
	

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initTextInput();
public:
	LoginState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states, AccountState* accountState, MainMenuState* mainMenuState);
	virtual ~LoginState();

	//Functions
	void initBackground();
	void updateInput(const float& dt) override;
	void updateButtons();
	void updateTextInputs();
	
	void sendRequest();
	void handleResponse(const std::string& response, long httpCode, std::string username);


	void handleEvent(sf::Event event) override;

	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void renderTextInput(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr) override;

};

