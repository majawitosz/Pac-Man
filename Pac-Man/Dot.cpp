#include "stdafx.h"
#include "Dot.h"


void Dot::initVariables()
{
	this->isSmallDot = false;
	this->isBigDot = false;
	this->isEaten = false;
}

Dot::Dot() {
	this->initVariables();
}

Dot::Dot(float x, float y, bool is_small_dot, bool is_big_dot) : isSmallDot(is_small_dot), isBigDot(is_big_dot)
{
	this->isEaten = false;
	this->dot.setRadius(2.f);
	//this->dot.setFillColor(sf::Color::White);
	

	if (this->isSmallDot) {
		this->dot.setPosition(x + 15.f, y + 15.f);
		this->dot.setRadius(2.f);
		this->dot.setFillColor(sf::Color::White);
	}
	else if (this->isBigDot) {
		this->dot.setPosition(x + 12.f, y + 13.f);
		this->dot.setRadius(5.f);
		this->dot.setFillColor(sf::Color::White);
	}
	else
		this->dot.setFillColor(sf::Color::Transparent);
}

Dot::~Dot()
{
}

bool Dot::getSmallDot() const
{
	return this->isSmallDot;
}

bool Dot::getBigDot() const
{
	return this->isBigDot;
}

bool Dot::getIsEaten() const
{
	return this->isEaten;
}

sf::FloatRect Dot::getGlobalBounds() const
{
	return this->dot.getGlobalBounds();
}

void Dot::setSmallDot(bool set)
{
	this->isSmallDot = set;
}

void Dot::setBigDot(bool set)
{
	this->isBigDot = set;
}

void Dot::setEaten(bool eaten)
{
	this->isEaten = eaten;
}

void Dot::render(sf::RenderTarget& target)
{
	if (!this->isEaten) {  
		target.draw(this->dot);
	}
}
