#include "stdafx.h"
#include "Tile.h"

Tile::Tile() : isWall(false), isTunnel(false), isPath(false), col(0), row(0), path(0)
{
}

Tile::Tile(float x, float y, float gridSizeF, bool isWall, bool isTunnel, int row, int col): isWall(isWall), isTunnel(isTunnel), isPath(false), row(row), col(col), path(0)
{
	
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));

	if (this->isWall)
		this->shape.setFillColor(sf::Color::Blue);
	else if (this->isTunnel)
		this->shape.setFillColor(sf::Color::Cyan);
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

bool Tile::getIsTunnel() const
{
	return this->isTunnel;
}

bool Tile::getIsPath() const
{
	return this->isPath;
}

std::pair<int, int> Tile::getCoordinates() const
{
	std::pair<int, int> cor;
	cor.first = this->row;
	cor.second = this->col;
	return cor;
}



int Tile::getPath() const
{
	return this->path;
}

void Tile::setPath(int path)
{
	this->isPath = true;
	this->path = path;
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
