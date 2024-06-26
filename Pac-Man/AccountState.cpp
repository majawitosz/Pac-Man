#include "stdafx.h"
#include "AccountState.h"


void AccountState::initVariables()
{
}

void AccountState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}

}

void AccountState::initKeybinds()
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

void AccountState::initButtons()
{
	this->buttons["LOGIN_STATE"] = new Button(320, 200, 150, 50,
		&this->font, "LOG IN",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["REGISTER_STATE"] = new Button(320, 280, 150, 50,
		&this->font, "REGISTER",
		sf::Color::Transparent,  sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["SCORES_STATE"] = new Button(320, 360, 150, 50,
		&this->font, "SCORES",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(320, 440, 150, 50,
		&this->font, "BACK",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

AccountState::AccountState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, MainMenuState* mainmenustate)
	: State(window, supportedKeys, states), mainMenuState(mainmenustate)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

AccountState::~AccountState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}


void AccountState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void AccountState::updateInput(const float& dt)
{
	//this->endStateUpdate();


}

void AccountState::updateButtons()
{
	// Updates all the button in the state
	for (auto& button : this->buttons | std::views::values)
	{
		button->update(this->mousePosView);
	}


	if (this->buttons["REGISTER_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->states->push(new RegisterState(this->window, this->supportedKeys, this->states));
	}
	else if (this->buttons["LOGIN_STATE"]->isPressed()) {
		sf::sleep(sf::milliseconds(100));
		LoginState* loginState = new LoginState(this->window, this->supportedKeys, this->states, this, mainMenuState);
		this->states->push(loginState);
		//this->states->push(new LoginState(this->window, this->supportedKeys, this->states));
	}
	else if (this->buttons["SCORES_STATE"]->isPressed()) {
		sf::sleep(sf::milliseconds(100));
		this->states->push(new ScoreState(this->window, this->supportedKeys, this->states, this));

	}
	else if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

void AccountState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void AccountState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void AccountState::render(sf::RenderTarget* target)
{

	
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}