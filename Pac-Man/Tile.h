#pragma once


class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool isWall;
	bool isTunnel;
	int col;
	int row;
	int path;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, bool isWall, bool isTunnel, int col, int row);
	virtual ~Tile();

	//Function
	bool getIsWall() const;
	bool getIsTunnel() const;
	sf::FloatRect getGlobalBounds() const;
	void update();
	void render(sf::RenderTarget& target);
};

