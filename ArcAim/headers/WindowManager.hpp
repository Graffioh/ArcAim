#pragma once
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "TimeManager.hpp"



class WindowManager
{
private:
	sf::RenderWindow* m_window;

	float m_countdown;

	sf::Font m_font;

	//sf::Clock m_clock;
	float m_timer;

	sf::Text m_uiText;
	sf::Text m_healthText;
	sf::Text m_timerText;

	std::string m_countdownString;
	std::ostringstream m_convert;

public:

	// Initializers
	void initWindow(sf::RenderWindow *window);

	void initVars();

	void initUIText();

	// Override for death screen
	void initUIText(float x, float y, unsigned int size);

	void initTimerText();

	// Constructor
	WindowManager();

	// Display the window
	void displayWindow();

	void updateClock();

	// Text funcs
	void updateText(short points, unsigned short health, bool endgame);

	void updateTimerText();

	void drawText();

	void drawTimerText();

	// Getters
	float getCountdown();

	// Setters
	void setCountdown(float countdown);
};

