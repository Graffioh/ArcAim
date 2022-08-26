#include "../headers/TargetsManager.hpp"

TargetsManager::TargetsManager()
	:m_timer(0), m_mouseHeld(false), m_points(0), m_deleted(false), m_spawnType('0'), m_playerHealth(PLAYER_HEALTH), m_targetSpawnTime(TARGET_SPAWN_TIMER), m_rng(m_rd()), m_xDist(0, WIN_WIDTH - 50), m_yDist(0, WIN_HEIGHT - 50)
{
}

void TargetsManager::setSpawnType(char spawnType)
{
	m_spawnType = spawnType;
}

void TargetsManager::spawn()
{
	switch (m_spawnType)
	{
	case '1':
		//m_target.setTargetPos(static_cast<float>(rand() % static_cast<int>(WIN_WIDTH - 50)), static_cast<float>(rand() % static_cast<int>(WIN_HEIGHT - 50))); // BAD SYSTEM

		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), static_cast<float>(m_yDist(m_rng)));
		break;

	case '2':
		//m_target.setTargetPos(static_cast<float>(rand() % static_cast<int>(WIN_WIDTH - 50)), 0); // BAD SYSTEM

		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), 0);
		break;

	default:
		std::cout << "Spawn type not allowed\n";
		break;
	}

	m_targets.push_back(m_target);
}

void TargetsManager::reflexEnemies()
{
	m_timer = TimeManager::clockTargets.getElapsedTime().asSeconds();

	if (m_targets.size() > 0 && m_timer > m_targetSpawnTime - 0.01f)
	{
		for (size_t i = 0; i < m_targets.size(); i++)
		{
			std::cout << "no" << std::endl;
			m_targets.erase(m_targets.begin() + i);
			m_playerHealth -= 10;
		}
	}
}

void TargetsManager::fallingEnemies()
{ 
	for (size_t i = 0; i < m_targets.size(); i++)
	{
		// If out of bounds delete, else move the target down
		if (m_targets[i].getSprite().getPosition().y > WIN_WIDTH)
		{
			std::cout << "no" << std::endl;
			m_targets.erase(m_targets.begin() + i);
			m_playerHealth -= 10;
		}
		else
		{
			m_targets[i].moveDown(0.f, 2.5f);
		}
	}	
}

void TargetsManager::update()
{
	m_timer = TimeManager::clockTargets.getElapsedTime().asSeconds();

	if (m_targets.size() < MAX_TARGETS)
	{
		// If TARGET_SPAWN_TIMER seconds are elapsed then spawn
		if (m_timer > m_targetSpawnTime + 0.01f)
		{
			spawn();

			TimeManager::clockTargets.restart();
		}
	}

	switch (m_spawnType)
	{
	case '1':
		reflexEnemies();
		break;
	case '2':
		fallingEnemies();
		break;
	default:
		std::cout << "Spawn type not allowed\n";
		break;
	}
}

void TargetsManager::draw(sf::RenderWindow& window)
{
	for (auto& target : m_targets)
	{
		window.draw(target.getSprite());
	}
}

void TargetsManager::eraseOnClick(sf::Vector2f mousePos)
{
	// Fix mouse pos offset but the detection on the borders is still shit
	mousePos.x = mousePos.x + 8;
	mousePos.y = mousePos.y + 8;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;
			m_deleted = false;
			for (size_t i = 0; i < m_targets.size() && !m_deleted; i++)
			{
				if (m_targets[i].getSprite().getGlobalBounds().contains(mousePos))
				{
					std::cout << "yes" << std::endl;
					m_deleted = true;

					m_targets.erase(this->m_targets.begin() + i);
					m_points++;

					m_target.playHitSound();
				}
				else
				{
					std::cout << "miss" << std::endl;
					m_playerHealth -= 10; // If target miss, decrease the health by 10
				}
			}
		}
	}
	else
	{
		m_mouseHeld = false;
	}
}

void TargetsManager::eraseAllEnemies()
{
	for (size_t i = 0; i < m_targets.size() && !m_deleted; i++)
	{
		m_targets.erase(this->m_targets.begin() + i);
	}
		
}

void TargetsManager::reset(unsigned short health, unsigned short points)
{
	m_playerHealth = health;
	m_points = points;
}

unsigned short TargetsManager::getPoints()
{
	return m_points;
}

unsigned short TargetsManager::getPlayerHealth()
{
	return m_playerHealth;
}

void TargetsManager::setSpawnTimer(float spawn_timer)
{
	m_targetSpawnTime = spawn_timer;
}


void TargetsManager::setHealth(unsigned short health)
{
	m_playerHealth = health;
}

void TargetsManager::setPoints(unsigned short points)
{
	m_points = points;
}