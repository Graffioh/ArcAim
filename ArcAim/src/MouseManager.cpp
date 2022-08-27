#include "../headers/MouseManager.hpp"

MouseManager::MouseManager()
{
	// Crosshair selection
	//m_cursorTexture.loadFromFile("res/Images/RedReticle.png");
	//m_cursorTexture.loadFromFile("res/Images/GreenReticle.png");
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


