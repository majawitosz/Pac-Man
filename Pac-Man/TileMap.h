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

	//Functions
	void loadMapFromFile(const std::string& filePath);
	
	void update();
	void render(sf::RenderTarget& target);

};

