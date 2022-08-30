#include "../headers/WindowManager.hpp"


void WindowManager::initWindow(sf::RenderWindow* window)
{
	m_window = window;
}

void WindowManager::initVars()
{

	if (!m_font.loadFromFile("res/Fonts/Minecraft.ttf"))
	{
		std::cout << "FONTS: Load Error!" << std::endl;
	}

	m_convert << m_countdown;
	m_countdownString = m_convert.str();
}

void WindowManager::initUIText()
{
	m_uiText.setFont(m_font);
	m_uiText.setCharacterSize(24);
	m_uiText.setFillColor(sf::Color::White);
	m_uiText.setString("NONE");
	m_uiText.setPosition(0, 0);

	/*this->m_healthText.setFont(this->m_font);
	this->m_healthText.setCharacterSize(24);
	this->m_healthText.setFillColor(sf::Color::Red);
	this->m_healthText.setString("NONE");
	this->m_healthText.setPosition(500, 0);*/
}

void WindowManager::initUIText(float x, float y, unsigned int size)
{
	m_uiText.setFont(m_font);
	m_uiText.setCharacterSize(size);
	m_uiText.setFillColor(sf::Color::White);
	m_uiText.setString("NONE");
	m_uiText.setPosition(x, y);
}

void WindowManager::initTimerText()
{
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(24);
	m_timerText.setFillColor(sf::Color::White);
	m_timerText.setString("NONE");
	m_timerText.setPosition(WIN_WIDTH / 2, 0);
}


WindowManager::WindowManager()
	:m_countdown(COUNTDOWN), m_timer(0)
{
	initVars();

	initUIText();

	initTimerText();
}

void WindowManager::displayWindow()
{
	m_window->display();
}

void WindowManager::updateClock()
{
	m_timer = TimeManager::clockCountdown.getElapsedTime().asSeconds();

	// Every seconds decrease the countdown
	//if (m_timer >= 1.f)
	if (m_timer >= 1.f)
	{
		m_countdown--;

		TimeManager::clockCountdown.restart();
	}
}

void WindowManager::updateText(short points, float health, bool endgame)
{
	std::stringstream ss;
	//std::stringstream ss2; Wanted to put health on up-right side colored red!!!!

	if (points == -1)
	{
		ss << "PAUSE" << std::endl;
	}
	else if(endgame)
	{
		ss << "GAME OVER\n\n" << "   Points: " << points << "\n\nR to Restart" << std::endl;
	}
	else
	{
		ss << "Points: " << points << std::endl;
		ss << "Health: " << health << std::endl;
	}

	m_uiText.setString(ss.str());
	//m_healthText.setString(ss2.str());
} 

void WindowManager::updateTimerText()
{
	std::stringstream ss2;

	ss2 << m_countdown << std::endl;
	m_timerText.setString(ss2.str());
}

void WindowManager::drawText()
{
	m_window->draw(m_uiText);
}

void WindowManager::drawTimerText()
{
	m_window->draw(m_timerText);
}

float WindowManager::getCountdown()
{
	return m_countdown;
}

void WindowManager::setCountdown(float countdown)
{
	m_countdown = countdown;
}
