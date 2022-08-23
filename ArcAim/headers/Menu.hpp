#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Global.hpp"

class Menu
{
private:
	sf::RectangleShape m_resumeButton;
	sf::RectangleShape m_menuButton1;
	sf::RectangleShape m_menuButton2;
	sf::RectangleShape m_menuButton3;

	sf::Font m_font;

	sf::Text m_startScreenTxt;
	sf::Text m_pauseScreenTxt;
	sf::Text m_menuTxt1;
	sf::Text m_menuTxt2;
	sf::Text m_menuTxt3;

	bool m_mouseHeld;

	bool resultBool;

	sf::Event event;

public:
	// Initializers
	void setupButton(sf::RectangleShape& button, sf::Color color, float width, float height, sf::Vector2f vec2);
	void initButton();

	void formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float width, float height);
	void initText();

	// Constructor
	Menu();

	// Start Menu text setup
	void updateText(bool isPause);
	void renderText(sf::RenderWindow& window, bool isPause);

	// If left click on the rectangle return true
	bool resumeGame(sf::Vector2f mousePos);

	// If Enter then return true
	bool startGame(sf::Vector2f mousePos);

	bool exitGame(sf::Vector2f mousePos);

	char gameStatus(sf::Vector2f mousePos);

	// Display the menu by using window from main
	void displayMenu(sf::RenderWindow& window, bool isPause);
};

