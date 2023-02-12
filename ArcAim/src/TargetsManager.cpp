#include "../headers/TargetsManager.hpp"

void TargetsManager::initMissSprite()
{
	m_missTexture.loadFromFile("res/Images/misscross.png");

	m_missSprite.setTexture(m_missTexture);
	m_missSprite.setScale(1.f, 1.f);
}

void TargetsManager::initMissSound()
{
	m_missSoundBuffer.loadFromFile("res/Sounds/Nope.wav");
	m_missSound.setBuffer(m_missSoundBuffer);
	m_missSound.setVolume(6);
}


TargetsManager::TargetsManager()
	:m_timer(0), m_mouseHeld(false), m_points(0), m_deleted(false), m_spawnType('0'), m_playerHealth(PLAYER_HEALTH), 
	m_targetSpawnTime(TARGET_SPAWN_TIMER), m_yFallingVel(Y_FALLING_VELOCITY), m_rng(m_rd()), m_xDist(45, WIN_WIDTH - 50), m_yDist(40, WIN_HEIGHT - 50), 
	isHit(false), m_tmpTargetPosX(WIN_WIDTH / 2), m_tmpTargetPosY(WIN_HEIGHT / 2), m_tmpTargetPosX2(0), m_tmpTargetPosY2(0)
{
	initMissSprite();
	initMissSound();
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

	case PRECISION_ENEMIES:
		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), static_cast<float>(m_yDist(m_rng)));
		break;

	case FALLING_ENEMIES:
		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), 0);
		break;

	case ONE_LINE:
		m_target.setTargetPos(static_cast<float>(m_xDist(m_rng)), static_cast<float>(m_yDist(m_rng)));
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

	//if (m_targets.size() > 0 && m_timer > m_targetSpawnTime - 0.01f) // This fucker was the problem...
	if (m_targets.size() > 1)
	{
		for (size_t i = 0; i < m_targets.size(); i++)
		{
			m_targets.erase(m_targets.begin() + i);
			m_playerHealth -= 10.f;
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
			m_targets[i].moveDown(0.f, m_yFallingVel);
		}
	}	
}

void TargetsManager::updateSpawn()
{
	m_timer = TimeManager::clockTargets.getElapsedTime().asSeconds();

	switch (m_spawnType)
	{
	case REFLEX_ENEMIES:
		reflexEnemies();

		m_LineVertices.clear();

		if (m_targets.size() < MAX_TARGETS)
		{
			// If TARGET_SPAWN_TIMER seconds are elapsed then spawn
			if (m_timer > m_targetSpawnTime + 0.01f)
			{
				spawn();

				TimeManager::clockTargets.restart();
			}
		}
		break;
	case PRECISION_ENEMIES:

		m_LineVertices.clear();

		if (m_targets.size() < MAX_TARGETS)
		{
			spawn();
		}
		break;
	case FALLING_ENEMIES:
		fallingEnemies();

		m_LineVertices.clear();

		if (m_targets.size() < MAX_TARGETS)
		{
			// If TARGET_SPAWN_TIMER seconds are elapsed then spawn
			if (m_timer > m_targetSpawnTime + 0.01f)
			{
				spawn();

				TimeManager::clockTargets.restart();
			}
		}
		break;
	case ONE_LINE:

		if (m_targets.size() < 1)
		{
			spawn();

			m_tmpTargetPosX2 = m_target.getTargetPos().x + m_target.getSprite().getGlobalBounds().width / 2;
			m_tmpTargetPosY2 = m_target.getTargetPos().y + m_target.getSprite().getGlobalBounds().height / 2;

			m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX, m_tmpTargetPosY - 5), sf::Color::Red);
			m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX, m_tmpTargetPosY + 5), sf::Color::Red);
			m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX2, m_tmpTargetPosY2 + 5), sf::Color::Red);
			m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX2, m_tmpTargetPosY2 - 5), sf::Color::Red);

			if (m_LineVertices.size() > 4) 
			{	
				m_LineVertices.erase(m_LineVertices.begin() + 0);
				m_LineVertices.erase(m_LineVertices.begin() + 0);
				
				m_LineVertices.erase(m_LineVertices.begin() + 2);
				m_LineVertices.erase(m_LineVertices.begin() + 2);
				
			}

			/*m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX, m_tmpTargetPosY), sf::Color::Red);
			m_LineVertices.emplace_back(sf::Vector2f(m_tmpTargetPosX2, m_tmpTargetPosY2), sf::Color::Red);

			if (m_LineVertices.size() > 2)
			{
				for (size_t i = 0; i < 2; i++)
				{
					m_LineVertices.erase(m_LineVertices.begin() + i);
				}
			}*/
			

		}
		break;
	default:
		std::cout << "Spawn type not allowed(update)\n";
		break;
	}
}

void TargetsManager::drawTarget(sf::RenderWindow& window)
{
	for (auto& target : m_targets)
	{
		window.draw(target.getSprite());
	}

	//if (m_LineVertices.size() > 1)
	//	window.draw(m_LineVertices.data(), m_LineVertices.size(), sf::LinesStrip);
	if (m_LineVertices.size() > 3)
		window.draw(m_LineVertices.data(), m_LineVertices.size(), sf::TriangleStrip);

}

void TargetsManager::eraseOnClick(sf::Vector2f mousePos)
{
	// Fix mouse pos offset
	mousePos.x = mousePos.x + 9;
	mousePos.y = mousePos.y + 9;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;
			m_deleted = false;

			for (size_t i = 0; i < m_targets.size() && !m_deleted; i++)
			{
				if (m_targets[i].getSprite().getGlobalBounds().contains(mousePos) && m_playerHealth != 0.f)
				{
					m_deleted = true;
					m_targets.erase(this->m_targets.begin() + i);

					m_points++;

					m_target.playHitSound();

					isHit = true;
				}
				else
				{
					isHit = false;
				}
			}

			if (!isHit)
			{

				m_playerHealth -= 10.f;

				if (m_isMissSpriteActive)
				{
					createMissSprite(mousePos);
				}

				playMissSound();
			}
		}
	}
	else
	{
		m_mouseHeld = false;
	}
}

void TargetsManager::eraseAllEnemiesAndCo()
{
	// Erase targets
	for (size_t i = 0; i < m_targets.size(); i++)
	{
		m_targets.erase(m_targets.begin() + i);
	}

	// Erase red crosses
	m_missSprites.clear();
}

void TargetsManager::reset(float health, unsigned short points)
{
	m_playerHealth = health;
	m_points = points;
}

void TargetsManager::createMissSprite(sf::Vector2f mousePos)
{
	m_missSprites.reserve(3); // for optimization

	m_missSprite.setPosition(mousePos.x - 3.f, mousePos.y - 3.f);
	m_missSprites.push_back(m_missSprite);
}

void TargetsManager::deleteMissSprite()
{
	for (size_t i = 0; i < 1; i++)
	{
		if(m_missSprites.size() > 3)
			m_missSprites.erase(m_missSprites.begin() + i);
	}
}

void TargetsManager::drawMissSprite(sf::RenderWindow& window)
{
	for (auto& hole : m_missSprites)
	{
		window.draw(hole);
	}

	deleteMissSprite();
}

void TargetsManager::playMissSound()
{
	m_missSound.play();
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

void TargetsManager::setMissActivation(bool missSpriteActive)
{
	m_isMissSpriteActive = missSpriteActive;
}

void TargetsManager::setYFallingVel(float yFallingVel)
{
	m_yFallingVel = yFallingVel;
}

void TargetsManager::setTargetsScale(float x, float y)
{
	m_target.setScale(x, y);
}


