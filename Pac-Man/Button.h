#pragma once

#include <SFML/Graphics.hpp>

enum buttonStates {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
private:
	short unsigned buttonState;
	//bool pressed = false;

	sf::RectangleShape button;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

