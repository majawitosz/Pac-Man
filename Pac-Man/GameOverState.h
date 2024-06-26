#pragma once

#include "State.h"

class GameOverState : public State
{
private:
	sf::Texture texture;
	sf::RectangleShape background;
public:
	GameOverState(sf::RenderWindow * window, std::stack<State*>*states);
	virtual ~GameOverState();
	void initBackground();
	void update(const float& dt) override;
	void render(sf::RenderTarget * target = nullptr) override;
};
