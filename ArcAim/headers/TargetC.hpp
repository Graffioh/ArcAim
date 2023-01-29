#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Global.hpp"

class TargetC
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::SoundBuffer m_hitSoundBuffer;
	sf::Sound m_sound;

public:
	// Initializers
	
	// Setup sprite+texture
	void initSprite();

	// Init hitsound
	void initHitSound();

	// Constructor
	TargetC();

	// Funcs to operate on the sprite
	void setTargetPos(float x, float y);
	void setScale(float x, float y);
	void moveDown(float x, float y);
	void playHitSound();

	// Getters
	sf::Sprite getSprite();
	sf::Vector2f getTargetPos();
};







