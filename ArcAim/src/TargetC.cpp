#include "../headers/TargetC.hpp"

void TargetC::initSprite()
{
	// 32x32
	//m_texture.loadFromFile("res/Images/TargetMDA.png");
	//m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	//m_sprite.setScale(1.f, 1.f);							

	// 16x16
	m_texture.loadFromFile("res/Images/TargetMDAs.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_sprite.setColor(sf::Color(255, 255, 255, 255));
	m_sprite.setScale(2.f, 2.f);
}

void TargetC::initHitSound()
{
	m_hitSoundBuffer.loadFromFile("res/Sounds/pophitsound.wav");
	m_sound.setBuffer(m_hitSoundBuffer);
	m_sound.setVolume(15);
}

TargetC::TargetC()
{
	initSprite();
	initHitSound();
}

sf::Sprite TargetC::getSprite()
{
	return m_sprite;
}

sf::Vector2f TargetC::getTargetPos()
{
	return m_sprite.getPosition();
}

void TargetC::setTargetPos(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void TargetC::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

void TargetC::moveDown(float x, float y)
{
	m_sprite.move(x, y);
}

void TargetC::playHitSound()
{
	m_sound.play();
}




