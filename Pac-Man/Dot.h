#pragma once
class Dot
{
private:
	sf::CircleShape dot;
	bool isSmallDot;
	bool isBigDot;

	void initVariables();
public:
	Dot();
	Dot(float x, float y,  bool is_small_dot, bool is_big_dot);
	virtual ~Dot();

	void render(sf::RenderTarget& target);
};

