#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::Animation::Animation
(
	sf::Sprite& sprite, sf::Texture& texture_sheet,
	float animation_timer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height
) : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
{
	this->timer = 0.f;
	this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
	this->currentRect = this->startRect;
	this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

	this->sprite.setTexture(this->textureSheet, true);
	this->sprite.setTextureRect(this->startRect);

}
void AnimationComponent::Animation::playRight(const float& dt)
{
	//Update timer
	this->timer += 350.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;
		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.left += this->width;
		}
		else //Reset
		{
			this->currentRect.left = this->startRect.left;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
}

void AnimationComponent::Animation::playLeft(const float& dt)
{
	//Update timer
	this->timer += 350.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;
		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.left -= this->width;
		}
		else //Reset
		{
			this->currentRect.left = this->startRect.left;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
}

void AnimationComponent::Animation::playUp(const float& dt)
{
	//Update timer
	this->timer += 350.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;
		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.top -= this->height;
		}
		else //Reset
		{
			this->currentRect.top = this->startRect.top;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
}

void AnimationComponent::Animation::playDown(const float& dt)
{
	//Update timer
	this->timer += 350.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;
		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.top += this->height;
		}
		else //Reset
		{
			this->currentRect.top = this->startRect.top;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
}


void AnimationComponent::Animation::pause()
{
}

void AnimationComponent::Animation::reset()
{
	this->timer = 0.f;
	this->currentRect = this->startRect;

}


AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{
}

//Functions
AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y,
	int frames_x, int frames_y,
	int width, int height
)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height
	);
}

// PlayIdle

void AnimationComponent::play(const std::string key, const float& dt)
{
	if(key == "IDLE")
		this->animations[key]->playRight(dt);
	else if(key == "RIGHT")
		this->animations[key]->playRight(dt);
	else if (key == "LEFT")
		this->animations[key]->playLeft(dt);
	else if(key == "UP")
		this->animations[key]->playUp(dt);
	else if(key == "DOWN")
		this->animations[key]->playDown(dt);
}

