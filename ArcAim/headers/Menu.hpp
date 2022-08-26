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

	sf::RectangleShape m_difficultyBtn1;
	sf::RectangleShape m_difficultyBtn2;
	sf::RectangleShape m_difficultyBtn3;
	sf::RectangleShape m_returnToMenuBtn;

	sf::Font m_font;

	sf::Text m_startScreenTxt;
	sf::Text m_pauseScreenTxt;
	
	sf::Text m_infoCapFpsTxt;
	sf::Text m_menuTxt1;
	sf::Text m_menuTxt2;
	sf::Text m_menuTxt3;

	sf::Text m_difficultyTxt1;
	sf::Text m_difficultyTxt2;
	sf::Text m_difficultyTxt3;
	sf::Text m_returnToMenuTxt;

	bool m_mouseHeld;
	bool m;

public:
	// Initializers
	void setupButton(sf::RectangleShape& button, sf::Color color, float width, float height, sf::Vector2f vec2);
	void initButton();
	void initStartBtn();
	void initOptionsBtn();

	void formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float width, float height);
	void initText();

	// Constructor
	Menu();

	// Start Menu text setup
	void updateText(bool isPause, bool isOptions);

	// Mechanism for buttons
	char activateStartBtn(sf::Vector2f mousePos);
	char activateOptionBtn(sf::Vector2f mousePos);

	// Display the menu by using window from main
	void displayMenu(sf::RenderWindow& window, bool isPause, bool isOptions);
};

