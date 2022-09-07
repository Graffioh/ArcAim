#pragma once
#include <iostream>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Global.hpp"
#include "TargetC.hpp"
#include "TimeManager.hpp"

class TargetsManager
{
private:
	TargetC m_target;
	std::vector<TargetC> m_targets;

	sf::Sprite m_targetSprite;

	float m_playerHealth;
	unsigned short m_points;
	char m_spawnType;
	bool m_mouseHeld;
	bool m_deleted;
	float m_targetSpawnTime;
	float m_timer;
	float m_yFallingVel;

	sf::Texture m_missTexture;
	sf::Sprite m_missSprite;
	std::vector<sf::Sprite> m_missSprites;
	bool m_isMissSpriteActive;

	sf::SoundBuffer m_missSoundBuffer;
	sf::Sound m_missSound;

	// RNG system (Better than srand)
	std::random_device m_rd;
	std::mt19937 m_rng;
	// For position
	std::uniform_int_distribution<int> m_xDist;
	std::uniform_int_distribution<int> m_yDist;

	bool isHit;

public:
	// Initializers
	void initMissSprite();
	void initMissSound();

	// Constructor
	TargetsManager();

	// Normal spawn
	void spawn();

	// Reflex mechanism
	void reflexEnemies();

	// Precision spawn
	//void precisionEnemies();

	// Falling mechanism
	void fallingEnemies();

	// Update and drawTarget
	void updateSpawn();
	void drawTarget(sf::RenderWindow& window);

	// If click on enemy, then erase it
	void eraseOnClick(sf::Vector2f mousePos);
	void eraseAllEnemiesAndCo();

	// Reset func for game restart
	void reset(float health, unsigned short points);

	// Create an hole when you miss
	void createMissSprite(sf::Vector2f mousePos);
	// Delete one hole every 4 holes spawned
	void deleteMissSprite();
	// Draw the hole and delete when needed
	void drawMissSprite(sf::RenderWindow& window);

	void playMissSound();

	// Getters
	unsigned short getPoints();
	float getPlayerHealth();

	// Setters
	void setSpawnType(char spawnType);
	void setSpawnTimer(float spawn_timer);
	void setHealth(float health);
	void setPoints(unsigned short points);
	void setMissActivation(bool holeActive);
	void setYFallingVel(float yFallingVel);
};

