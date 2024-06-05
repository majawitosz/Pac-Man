#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
	
public:
	Tile();
	Tile(float x, float y, float gridSizeF, int value);
	virtual ~Tile();

	//Function
	void update();
	void render(sf::RenderTarget& target);
};

