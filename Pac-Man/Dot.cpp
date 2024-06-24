#include "stdafx.h"
#include "Dot.h"


void Dot::initVariables()
{
	this->isSmallDot = false;
	this->isBigDot = false;
}

Dot::Dot() {
	this->initVariables();
}

Dot::Dot(float x, float y, bool is_small_dot, bool is_big_dot) : isSmallDot(is_small_dot), isBigDot(is_big_dot)
{

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

void Dot::render(sf::RenderTarget& target)
{
	target.draw(this->dot);
}
