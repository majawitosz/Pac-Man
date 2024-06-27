#include "stdafx.h"
#include "GameOverState.h"


GameOverState::GameOverState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();
}

GameOverState::~GameOverState()
{
}


void GameOverState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->texture.loadFromFile("Resources/Images/Backgrounds/game_over.png"))
	{
		throw "ERRPR::GAME_OVER_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->texture);
}

void GameOverState::update(const float& dt)
{
	sf::sleep(sf::milliseconds(2000));
	this->endState();
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	
}