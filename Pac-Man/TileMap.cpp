#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 16.f; //16.f
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 29; //224
	this->maxSize.y = 32; //248
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	this->dots.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector < std::vector<Tile>>());
		this->dots.push_back(std::vector < std::vector<Dot>>());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile>());
			this->dots[x].resize(this->maxSize.y);
			this->dots[x].push_back(std::vector<Dot>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, 0, 0, x, y));
				this->dots[x][y].resize(this->layers);
				this->dots[x][y].push_back(Dot(x * this->gridSizeF, y * this->gridSizeF, 0, 0));
				
			}
		}
	}
	
}

TileMap::~TileMap()
{

}

const std::vector<std::vector<std::vector<Tile>>>& TileMap::getMap() const
{
	return this->map;
}

const float TileMap::getWidth() const
{
	return this->gridSizeF * this->maxSize.x;
}

const float TileMap::getHeight() const
{
	return this->gridSizeF * this->maxSize.y;
}

const float TileMap::getGridSizeF() const
{
	return this->gridSizeF;
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
			bool isWall = (line[x] == '1');
			bool isTunnel = (line[x] == '2');
			this->map[x][y][0] = Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, isWall, isTunnel, x, y);
			//std::cout << x << " " << y << std::endl;
		}
		++y;
	}

	file.close();

}

void TileMap::loadMapDotsFromFile(const std::string& filePath)
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
			bool isSmallDot = (line[x] == '3');
			bool isBigDot = (line[x] == '4');
			this->dots[x][y][0] = Dot(x * this->gridSizeF, y * this->gridSizeF, isSmallDot, isBigDot);
		
		}
		++y;
	}

	file.close();

}

Tile* TileMap::getTileByCoor(std::pair<int, int> coor)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z.getCoordinates() == coor) {
					return &z;
				}

			}
		}
	}
	//return &Tile();
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

void TileMap::renderDots(sf::RenderTarget& target)
{
	for (auto& x : this->dots)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}

std::set<std::pair<int, int>> convertToSet(const std::vector<std::pair<int, int>>& steps) {
	return std::set<std::pair<int, int>>(steps.begin(), steps.end());
}

bool getCoor(std::vector<std::pair<int, int>> steps, std::pair<int, int> step) {

	for (int i = 0; i < steps.size(); i++)
	{
		if (steps[i] == step) {
			return true;
		}
	}
	return false;
}


void TileMap::printMap(sf::FloatRect playerPosition, sf::FloatRect ghostPosition, std::vector<std::pair<int, int>> steps) {
	std::set<std::pair<int, int>> stepSet = convertToSet(steps);
	
	for (size_t y = 0; y < this->maxSize.y; y++) {
		for (size_t x = 0; x < this->maxSize.x; x++) {
			// Assuming there's only one layer (z = 0)
			std::pair<int, int> currentCoordinates = this->map[x][y][0].getCoordinates();
			
			if (this->map[x][y][0].getIsWall()) {
				std::cout << std::setw(4) << "* ";
			}
			else if (this->map[x][y][0].getGlobalBounds().intersects(playerPosition) )
			{
				std::cout << std::setw(3) << "P ";
			}
			else if (this->map[x][y][0].getGlobalBounds().intersects(ghostPosition) )
			{
				std::cout << std::setw(3) << "G ";
			}
			else if (getCoor(steps, this->map[x][y][0].getCoordinates())) {
				std::cout << std::setw(3) << "A ";
			}
			else {
				std::cout << std::setw(3) << this->map[x][y][0].getPath() << " ";
			}
		}
		std::cout << std::endl;
	}
}

void TileMap::clearPath()
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.setPath(0);
			}
		}
	}

}

//Functions