#include <iostream>

#include "../headers/MouseManager.hpp"

MouseManager::MouseManager()
	:m_mouseHeld(false)
{
	m_cursorTexture.loadFromFile("res/Images/GreenReticleOutline.png");

	m_cursorSprite.setTextureRect(sf::IntRect(6, 6, 20, 20));
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

void MouseManager::drawTarget(sf::RenderWindow& window)
{
	window.draw(m_cursorSprite);
}

void MouseManager::setCrossStyle(char style)
{
	switch (style)
	{
	case CROSS_STYLE1:
		m_cursorTexture.loadFromFile("res/Images/GreenReticleOutline.png");
		break;
	case CROSS_STYLE2:
		m_cursorTexture.loadFromFile("res/Images/CyanReticle.png");
		break;
	case CROSS_STYLE3:
		m_cursorTexture.loadFromFile("res/Images/RedReticleOpen.png");
		break;
	default:
		// return so we don't set an invalid m_cursorTexture
		std::cout << "invalid CROSS_STYLE!\n";
		return;
	}

	m_cursorSprite.setTexture(m_cursorTexture);
}




