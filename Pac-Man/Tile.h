#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool isWall;
	bool isTunnel;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, bool isWall, bool isTunnel);
	virtual ~Tile();

	//Function
	bool getIsWall() const;
	bool getIsTunnel() const;
	sf::FloatRect getGlobalBounds() const;
	void update();
	void render(sf::RenderTarget& target);
};

