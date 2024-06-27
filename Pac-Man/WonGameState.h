#pragma once

#include "State.h"

class WonGameState : public State
{
private:
	sf::Texture texture;
	sf::RectangleShape background;
public:
	WonGameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~WonGameState();
	void initBackground();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};
