#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 16.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 29; //224
	this->maxSize.y = 32; //248
	this->layers = 3;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector < std::vector<Tile>>());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, 0));
			}
		}
	}
	
}

TileMap::~TileMap()
{

}

void TileMap::loadMapFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		throw "ERROR::TILE_MAP::COULD_NOT_LOAD_MAP_TXT";
	}
	std::string line;
	int y = 0;
	while (std::getline(file, line))
	{
		for (int x = 0; x < line.size(); ++x)
		{
			bool isWall = (line[x] == '1') ? true : false;
			this->map[x][y][0] = Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, isWall);
	/*		if (line[x] == '1')
			{
				this->map[x][y][0] = Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, value);
			}*/
		}
		++y;
	}

	file.close();

}



void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}

//Functions