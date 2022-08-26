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

	unsigned short m_playerHealth;
	unsigned short m_points;
	char m_spawnType;
	bool m_mouseHeld;
	bool m_deleted;
	float m_targetSpawnTime;
	float m_timer;

	// RNG system (Better than srand)
	std::random_device m_rd;
	std::mt19937 m_rng;
	std::uniform_int_distribution<int> m_xDist;
	std::uniform_int_distribution<int> m_yDist;

public:
	// Constructor
	TargetsManager();

	// Normal spawn
	void spawn();

	// Reflex spawn
	void reflexEnemies();

	// Falling enemies
	void fallingEnemies();

	// Update and draw
	void update();

	void draw(sf::RenderWindow& window);

	// If click on enemy, then erase it
	void eraseOnClick(sf::Vector2f mousePos);

	// Getters
	unsigned short getPoints();

	unsigned short getPlayerHealth();

	// Setters
	// Spawn type: 1 for reflex, 2 for falling targets
	void setSpawnType(char spawnType);

	void setSpawnTimer(float spawn_timer);

	void setHealth(unsigned short health);

	void setPoints(unsigned short points);
};

