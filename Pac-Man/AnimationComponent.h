#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
			int start_x, int start_y, int frames_x, int frames_y, int width, int height);

		//Functions
		void playRight(const float& dt);
		void playLeft(const float& dt);
		void playUp(const float& dt);
		void playDown(const float& dt);
		
		void pause();
		void reset();
	};
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y,
		int width, int height);


	void play(const std::string key, const float& dt);

};

