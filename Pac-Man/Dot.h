#pragma once
class Dot
{
private:
	sf::CircleShape dot;
	bool isSmallDot;
	bool isBigDot;
	bool isEaten;

	void initVariables();
public:
	Dot();
	Dot(float x, float y,  bool is_small_dot, bool is_big_dot);
	virtual ~Dot();

	//Accessors
	bool getSmallDot() const;
	bool getBigDot() const;
	bool getIsEaten() const;
	sf::FloatRect getGlobalBounds() const;

	// Modifiers
	void setSmallDot(bool set);
	void setBigDot(bool set);
	void setEaten(bool eaten);

	void render(sf::RenderTarget& target);
};

