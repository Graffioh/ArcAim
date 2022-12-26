#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Global.hpp"
#include "Button.hpp"

class Menu
{
private:
	// Using a map to store button objects who will be created
	std::map<std::string, Button*> m_buttons;

	sf::Font m_font;

	sf::Text m_difficulty0Txt;
	sf::Text m_crossStyle0Txt;
	sf::Text m_gameModes0Txt;
	sf::Text m_infoTxt;

	sf::Texture m_crossStyle1Img;
	sf::Sprite m_crossStyle1SpriteImg;
	sf::Texture m_crossStyle2Img;
	sf::Sprite m_crossStyle2SpriteImg;
	sf::Texture m_crossStyle3Img;
	sf::Sprite m_crossStyle3SpriteImg;

	sf::SoundBuffer m_btnSoundBuffer;
	sf::Sound m_btnSound;

	bool m_mouseHeld;
	
	float m_btnOutlineWhenClicked;

	float m_yDownUpValue;

	sf::View m_view;

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

	void updateBtn(sf::Vector2f mousePos);

	void displayInfo(sf::RenderWindow& window);

	// Mechanism for buttons
	char activateStartBtn(sf::Vector2f mousePos);
	char activateOptionBtn(sf::Vector2f mousePos);

	void playBtnSound();

	// Display the menu by using window from main
	void displayMenu(sf::RenderTarget* target, sf::RenderWindow& window, bool isOptions);

	sf::View getView();
};

