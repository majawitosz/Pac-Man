#pragma once


class Tile
{
private:

protected:
	
	
	sf::RectangleShape shape;
	bool isWall;
	bool isTunnel;
	bool isPath;
	int col;
	int row;
	int path;


public:
	
	Tile();
	Tile(float x, float y, float gridSizeF, bool isWall, bool isTunnel, int row, int col);
	virtual ~Tile();

	//Function
	
	bool getIsWall() const;
	bool getIsTunnel() const;
	bool getIsPath() const;
	std::pair<int, int> getCoordinates() const;
	
	int getPath() const;
	void setPath(int path);
	sf::FloatRect getGlobalBounds() const;
	
	void update();
	void render(sf::RenderTarget& target);
};

