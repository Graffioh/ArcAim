#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Global.hpp"


class Menu
{
private:
	sf::RectangleShape m_button;

	sf::Font m_font;

	sf::Text m_startScreenTxt;
	sf::Text m_pauseScreenTxt;

	bool m_mouseHeld;

public:
	// Initializers
	void initButton();
	void initText();

	// Constructor
	Menu();

	// Start Menu text setup
	void updateText(bool isPause);
	void renderText(sf::RenderWindow& window, bool isPause);

	// If left click on the rectangle return true
	bool resumeGame(sf::Vector2f mousePos);

	// If Enter then return true
	bool startGame();

	// Display the menu by using window from main
	void displayMenu(sf::RenderWindow& window, bool isPause);
};

