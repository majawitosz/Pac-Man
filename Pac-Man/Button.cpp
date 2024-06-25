#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
	font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	this->buttonState = BTN_IDLE;

	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->button.setFillColor(this->idleColor);


	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	//set text position int the middle
	this->text.setPosition(
		(int)this->button.getPosition().x + (this->button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		(int)this->button.getPosition().y + (this->button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}



void Button::update(const sf::Vector2f mousePos)
{
	// Updates the booleans for hover and pressed

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->button.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->button.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->button.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->button.setFillColor(this->activeColor);
		break;
	default:
		this->button.setFillColor(sf::Color::Red);
		break;
	}

}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->button);
	target.draw(this->text);
}

