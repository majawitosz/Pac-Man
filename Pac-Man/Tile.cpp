#include "stdafx.h"
#include "Tile.h"

Tile::Tile() : isWall(false)
{
}

Tile::Tile(float x, float y, float gridSizeF, bool isWall): isWall(isWall)
{
	
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));

	if (this->isWall)
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


bool Tile::getIsWall() const
{
	return this->isWall;
}

sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
