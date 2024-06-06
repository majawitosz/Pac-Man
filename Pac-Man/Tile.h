#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool isWall;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, bool isWall);
	virtual ~Tile();

	//Function
	bool getIsWall() const;
	sf::FloatRect getGlobalBounds() const;
	void update();
	void render(sf::RenderTarget& target);
};

