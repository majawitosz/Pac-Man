#include "stdafx.h"
#include "MainMenuState.h"


void MainMenuState::initVariables()
{
	
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}

}

void MainMenuState::initKeybinds()
{
	std::ifstream file("Config/mainmenustate_keybinds.ini");

	if (file.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (file >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(320, 200, 150, 50,
		&this->font, "PLAY",
		sf::Color(70, 70, 70, 200), sf::Color(10, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["ACCOUNT_STATE"] = new Button(320, 280, 150, 50,
		&this->font, "ACCOUNT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(320, 360, 150, 50,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}



void MainMenuState::updateLoginStatus()
{
	

	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void MainMenuState::updateInput(const float& dt)
{
	//this->endStateUpdate();


}

void MainMenuState::updateButtons()
{
	// Updates all the button in the state
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
	else if (this->buttons["ACCOUNT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->states->push(new AccountState(this->window, this->supportedKeys, this->states));
	}
	//Quit the game
	else if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
	

	if (getLoginStatus()) {
		this->loginStatus.setPosition(300.f, 150.f);
		this->loginStatus.setFont(this->font);
		this->loginStatus.setCharacterSize(12);
		std::string ss = "User: " + getUsername();
		this->loginStatus.setString(ss);
		target->draw(this->loginStatus);
	}

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}