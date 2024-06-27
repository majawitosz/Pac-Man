#include "stdafx.h"
#include "WonGameState.h"



WonGameState::WonGameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();
}

WonGameState::~WonGameState()
{
}


void WonGameState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->texture.loadFromFile("Resources/Images/Backgrounds/won_state.png"))
	{
		throw "ERRPR::WON_GAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->texture);
}

void WonGameState::update(const float& dt)
{
	sf::sleep(sf::milliseconds(2000));
	this->endState();
}

void WonGameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

}