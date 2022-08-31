#include "../headers/TargetsManager.hpp"

void TargetsManager::initHole()
{
	m_circle.setFillColor(sf::Color(240, 240, 240, 255));
	m_circle.setRadius(2.f);
}

TargetsManager::TargetsManager()
	:m_timer(0), m_mouseHeld(false), m_points(0), m_deleted(false), m_spawnType('0'), m_playerHealth(PLAYER_HEALTH), m_targetSpawnTime(TARGET_SPAWN_TIMER), m_rng(m_rd()), m_xDist(0, WIN_WIDTH - 50), m_yDist(0, WIN_HEIGHT - 50)
{
	initHole();
}

void TargetsManager::setSpawnType(char spawnType)
{
	m_spawnType = spawnType;
}

void TargetsManager::spawn()
{
	switch (m_spawnType)
	{
	case REFLEX_ENEMIES:
		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), static_cast<float>(m_yDist(m_rng)));
		break;

	case FALLING_ENEMIES:
		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), 0);
		break;

	default:
		std::cout << "Spawn type not allowed(spawn)\n";
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
			m_targets.erase(m_targets.begin() + i);
			m_playerHealth -= 10.f;
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
	case REFLEX_ENEMIES:
		reflexEnemies();
		break;
	case FALLING_ENEMIES:
		fallingEnemies();
		break;
	default:
		std::cout << "Spawn type not allowed(update)\n";
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
	mousePos.x = mousePos.x + 6;
	mousePos.y = mousePos.y + 6;

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
					m_deleted = true;
					m_targets.erase(this->m_targets.begin() + i);

					m_points++;

					m_target.playHitSound();
				}
				else
				{
					// If target miss, decrease the health by 10 and create an hole on background
					if (m_playerHealth != 0.f)
					{
						m_playerHealth -= 10.f;
						if(m_isHoleActive)
							createHole(mousePos);
					}
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
	// Erase targets
	for (size_t i = 0; i < m_targets.size(); i++)
	{
		m_targets.erase(m_targets.begin() + i);
	}

	// Erase bullet hole
	for (size_t i = 0; i < m_holes.size(); i++)
	{
		m_holes.erase(m_holes.begin() + i);
	}
}

void TargetsManager::reset(float health, unsigned short points)
{
	m_playerHealth = health;
	m_points = points;
}

unsigned short TargetsManager::getPoints()
{
	return m_points;
}

float TargetsManager::getPlayerHealth()
{
	return m_playerHealth;
}

void TargetsManager::setSpawnTimer(float spawn_timer)
{
	m_targetSpawnTime = spawn_timer;
}

void TargetsManager::setHealth(float health)
{
	m_playerHealth = health;
}

void TargetsManager::setPoints(unsigned short points)
{
	m_points = points;
}

void TargetsManager::createHole(sf::Vector2f mousePos)
{
	m_circle.setPosition(mousePos.x, mousePos.y);

	m_holes.push_back(m_circle);
}

//void TargetsManager::deleteHole()
//{
//	for (size_t i = 0; i < m_holes.size(); i++)
//	{
//		m_holes.erase(m_holes.begin() + i);
//	}
//}

void TargetsManager::drawHole(sf::RenderWindow& window)
{
	for (auto& hole : m_holes)
	{
		window.draw(hole);
	}
}

void TargetsManager::setHole(bool holeActive)
{
	m_isHoleActive = holeActive;
}