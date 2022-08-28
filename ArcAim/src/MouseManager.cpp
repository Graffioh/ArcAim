#include "../headers/MouseManager.hpp"

MouseManager::MouseManager()
{
	m_cursorTexture.loadFromFile("res/Images/GreenReticleOutline.png");

	m_cursorSprite.setTexture(m_cursorTexture);
}

void MouseManager::updateMousePos(sf::RenderWindow& window)
{
	m_mousePosWindow = sf::Mouse::getPosition(window);
	m_mousePosView = window.mapPixelToCoords(m_mousePosWindow);
}

sf::Vector2f MouseManager::getMousePos()
{
	return m_mousePosView;
}

void MouseManager::syncPositionWithSprite(sf::RenderWindow& window)
{
	m_cursorSprite.setPosition(static_cast<sf::Vector2f>(m_mousePosView));
}

void MouseManager::draw(sf::RenderWindow& window)
{
	window.draw(m_cursorSprite);
}

void MouseManager::setCrossStyle(char style)
{
	if (style == CROSS_STYLE1)
	{
		m_cursorTexture.loadFromFile("res/Images/GreenReticleOutline.png");
	}

	if (style == CROSS_STYLE2)
	{
		m_cursorTexture.loadFromFile("res/Images/CyanReticle.png");
	}

	if (style == CROSS_STYLE3)
	{
		m_cursorTexture.loadFromFile("res/Images/RedReticle.png");
	}

	m_cursorSprite.setTexture(m_cursorTexture);
}


