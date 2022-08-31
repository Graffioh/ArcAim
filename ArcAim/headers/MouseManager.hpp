#pragma once

#include <SFML/Graphics.hpp>

#include "Global.hpp"

class MouseManager
{
private:
	sf::Texture m_cursorTexture;
	sf::Sprite m_cursorSprite;

	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;

	bool m_mouseHeld;

public:
	// Constructor
	MouseManager();

	// Update mouse pos every frame
	void updateMousePos(sf::RenderWindow& window);

	// Update mouse pos every frame
	sf::Vector2f getMousePos();

	// Sync the mouse position with the sprite
	void syncPositionWithSprite(sf::RenderWindow& window);

	// Draw the sprite cursor on the screen
	void draw(sf::RenderWindow& window);
	
	// Setters
	// set the crosshair texture
	void setCrossStyle(char style);
};

