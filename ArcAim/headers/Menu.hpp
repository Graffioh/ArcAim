#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Button.hpp"

class Menu
{
private:
	sf::Font m_font;

	std::map<std::string, Button*> m_buttons;

	sf::Text m_difficulty0Txt;
	sf::Text m_crossStyle0Txt;
	sf::Text m_infoCapFpsTxt;

	sf::Texture m_crossStyle1Img;
	sf::Sprite m_crossStyle1SpriteImg;
	sf::Texture m_crossStyle2Img;
	sf::Sprite m_crossStyle2SpriteImg;
	sf::Texture m_crossStyle3Img;
	sf::Sprite m_crossStyle3SpriteImg;

	bool m_mouseHeld;

public:
	// Initializers
	void initFont();
	void initButton();
	void initCrossStyleImg();

	void formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float x, float y);
	void initText();

	// Constructor
	Menu();
	~Menu();

	// Start Menu text setup
	void updateText(bool isOptions);

	// Mechanism for buttons
	char activateStartBtn(sf::Vector2f mousePos);
	char activateOptionBtn(sf::Vector2f mousePos);

	// Display the menu by using window from main
	void displayMenu(sf::RenderTarget* target, sf::RenderWindow& window, bool isOptions);
};

