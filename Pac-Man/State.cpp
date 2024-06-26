#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: window(window), quit(false), supportedKeys(supportedKeys), states(states)
{
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;

}

void State::endState()
{
	this->quit = true;
}

//bool& State::getLoginStatus() 
//{
//	return this->logedIn;
//}
//
//void State::setLoginStatus(bool login)
//{
//	this->logedIn = login;
//}
//
//void State::setUsername(std::string username)
//{
//	this->userName = username;
//}
//
//std::string State::getUsername()
//{
//	return this->userName;
//}

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::handleEvent(sf::Event event)
{
}





