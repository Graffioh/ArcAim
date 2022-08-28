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

	sf::RectangleShape m_difficulty1Btn;
	sf::RectangleShape m_difficulty2Btn;
	sf::RectangleShape m_difficulty3Btn;

	sf::RectangleShape m_crossStyle1Btn;
	sf::RectangleShape m_crossStyle2Btn;
	sf::RectangleShape m_crossStyle3Btn;
	
	sf::RectangleShape m_returnToMenuBtn;

	sf::Font m_font;

	sf::Text m_startScreenTxt;
	sf::Text m_pauseScreenTxt;
	
	sf::Text m_infoCapFpsTxt;
	sf::Text m_menuTxt1;
	sf::Text m_menuTxt2;
	sf::Text m_menuTxt3;

	sf::Text m_difficulty0Txt;
	sf::Text m_difficulty1Txt;
	sf::Text m_difficulty2Txt;
	sf::Text m_difficulty3Txt;
	
	sf::Text m_crossStyle0Txt;
	sf::Text m_crossStyle1Txt;
	sf::Text m_crossStyle2Txt;
	sf::Text m_crossStyle3Txt;

	sf::Texture m_crossStyle1Img;
	sf::Sprite m_crossStyle1SpriteImg;
	sf::Texture m_crossStyle2Img;
	sf::Sprite m_crossStyle2SpriteImg;
	sf::Texture m_crossStyle3Img;
	sf::Sprite m_crossStyle3SpriteImg;
	
	sf::Text m_returnToMenuTxt;

	bool m_mouseHeld;
	bool m;

public:
	// Initializers
	void setupButton(sf::RectangleShape& button, sf::Color color, sf::Vector2f vec2, float x, float y);
	void initButton();
	void initStartBtn();
	void initOptionsBtn();

	void formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float x, float y);
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

