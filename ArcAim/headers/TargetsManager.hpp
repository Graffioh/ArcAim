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

	sf::Texture m_holeTexture;
	sf::Sprite m_holeSprite;
	std::vector<sf::Sprite> m_holes;
	bool m_isHoleActive;

	// RNG system (Better than srand)
	std::random_device m_rd;
	std::mt19937 m_rng;
	std::uniform_int_distribution<int> m_xDist;
	std::uniform_int_distribution<int> m_yDist;

public:
	void initHole();

	// Constructor
	TargetsManager();

	// Normal spawn
	void spawn();

	// Reflex spawn
	void reflexEnemies();

	// Falling enemies
	void fallingEnemies();

	// Update and drawTarget
	void update();

	void drawTarget(sf::RenderWindow& window);

	// If click on enemy, then erase it
	void eraseOnClick(sf::Vector2f mousePos);
	void eraseAllEnemies();

	// Reset func for game restart
	void reset(float health, unsigned short points);

	// Create an hole when you miss
	void createHole(sf::Vector2f mousePos);
	// Delete one hole every 4 holes spawned
	void deleteHole();
	// Draw the hole and delete when needed
	void drawHole(sf::RenderWindow& window);

	// Getters
	unsigned short getPoints();
	float getPlayerHealth();

	// Setters
	// Spawn type: 1 for reflex, 2 for falling targets
	void setSpawnType(char spawnType);
	void setSpawnTimer(float spawn_timer);
	void setHealth(float health);
	void setPoints(unsigned short points);
	void setHole(bool holeActive);
};

