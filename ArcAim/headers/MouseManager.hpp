#pragma once

#include <SFML/Graphics.hpp>

class MouseManager
{
private:
	sf::Texture m_cursorTexture;
	sf::Sprite m_cursorSprite;

	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;

public:
	// Constructor
	MouseManager();

	// Update mouse pos every frame
	void updateMousePos(sf::RenderWindow& window);

	// Update mouse pos every frame
	sf::Vector2f getMousePos();

	// Sync the mouse position with the sprite
	void syncPosition(sf::RenderWindow& window);

	// Draw the sprite cursor on the screen
	void draw(sf::RenderWindow& window);
};

