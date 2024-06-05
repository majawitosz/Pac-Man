#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, int value)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));

	if (value == 1)
		this->shape.setFillColor(sf::Color::Blue);
	else
		this->shape.setFillColor(sf::Color::Transparent);

	//this->shape.setFillColor(sf::Color::Blue);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Cyan);
	this->shape.setPosition(x, y);
	
}

Tile::~Tile()
{

}

//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
