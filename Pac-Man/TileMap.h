#pragma once

#include "Tile.h"


class TileMap 
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile>>> map;
public:
	TileMap();
	virtual ~TileMap();

	// Accessor function
	const std::vector<std::vector<std::vector<Tile>>>& getMap() const;
	const float getWidth() const;
	const float getHeight() const;
	const float getGridSizeF() const;
	

	//Functions
	void loadMapFromFile(const std::string& filePath);
	Tile* getTileByCoor(std::pair<int, int> coor);
	void update();
	void render(sf::RenderTarget& target);
	void printMap(sf::FloatRect playerPosition, sf::FloatRect ghostPosition, std::vector<std::pair<int, int>> steps);
	void clearPath();

};

