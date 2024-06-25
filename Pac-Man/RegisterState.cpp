#include "stdafx.h"
#include "RegisterState.h"



void RegisterState::initVariables()
{
}

void RegisterState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}

}

void RegisterState::initKeybinds()
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

void RegisterState::initButtons()
{

	this->buttons["EXIT_STATE"] = new Button(320, 440, 150, 50,
		&this->font, "BACK",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void RegisterState::initTextInput()
{
	this->textInputs["USERNAME"] = new TextInput(250, 200, 300, 30, 
		&this->font, "username", 
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->textInputs["PASSWORD"] = new TextInput(250, 280, 300, 30, 
		&this->font, "password", 
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

RegisterState::RegisterState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initTextInput();

}

RegisterState::~RegisterState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}



void RegisterState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void RegisterState::updateInput(const float& dt)
{
	//this->endStateUpdate();


}

void RegisterState::updateButtons()
{
	// Updates all the button in the state
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

void RegisterState::updateTextInputs()
{
	for (auto& it : this->textInputs)
	{
		it.second->update(this->mousePosView);
	}
}

void RegisterState::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed) {
		this->window->close();
	}
	if (this->textInputs["USERNAME"]->getIsActive()) {
		this->textInputs["USERNAME"]->handleEvent(event);
	}
	else if (this->textInputs["PASSWORD"]->getIsActive()) {
		this->textInputs["PASSWORD"]->handleEvent(event);
	}
}


void RegisterState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
	this->updateTextInputs();
}

void RegisterState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void RegisterState::renderTextInput(sf::RenderTarget& target)
{
	for (auto& it : this->textInputs) {
		it.second->render(target);
	}
	
}

void RegisterState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
	this->renderTextInput(*target);
}