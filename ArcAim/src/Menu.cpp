#include "../headers/Menu.hpp"

void Menu::initButton()
{
	m_button.setFillColor(sf::Color::Blue);
	m_button.setPosition(WIN_WIDTH / 3, WIN_HEIGHT / 2.5);
	m_button.setSize(sf::Vector2f(280, 60));
}

void Menu::initText()
{
	if (!m_font.loadFromFile("res/Fonts/Minecraft.ttf"))
	{
		std::cout << "FONTS: Load Error!" << std::endl;
	}

	m_startScreenTxt.setFont(m_font);
	m_startScreenTxt.setCharacterSize(69);
	m_startScreenTxt.setFillColor(sf::Color::Green);
	m_startScreenTxt.setString("NONE");
	m_startScreenTxt.setPosition(25, WIN_HEIGHT / 3);

	m_pauseScreenTxt.setFont(m_font);
	m_pauseScreenTxt.setCharacterSize(30);
	m_pauseScreenTxt.setFillColor(sf::Color::White);
	m_pauseScreenTxt.setString("NONE");
	m_pauseScreenTxt.setPosition(WIN_WIDTH / 2.7f, WIN_HEIGHT / 2.4f);
}

Menu::Menu()
	:m_mouseHeld(false)
{
	initButton();
	initText();
}

void Menu::updateText(bool isPause)
{
	std::stringstream ss;
	
	if (isPause)
	{
		ss << "RESUME GAME" << std::endl;

		m_pauseScreenTxt.setString(ss.str());
	}
	else
	{
		ss << "\t  PRESS ENTER"  << std::endl;
		ss << "TO START THE GAME" << std::endl;

		m_startScreenTxt.setString(ss.str());
	}
}

void Menu::renderText(sf::RenderWindow& window, bool isPause)
{
	if (isPause)
	{
		window.draw(m_pauseScreenTxt);
	}
	else
	{
		window.draw(m_startScreenTxt);
	}
}

bool Menu::resumeGame(sf::Vector2f mousePos)
{
	// Adjusting offset
	mousePos.x = mousePos.x + 8;
	mousePos.y = mousePos.y + 8;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;
			if (m_button.getGlobalBounds().contains(mousePos))
			{
				return true;
			}
		}
	}
	else
	{
		m_mouseHeld = false;
	}
		return false;
}

bool Menu::startGame()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	return true;

	return false;
}

void Menu::displayMenu(sf::RenderWindow& window, bool isPause)
{
	window.clear(sf::Color(60, 60, 60, 255));

	if (isPause)
	{
		window.draw(m_button);
	}
}

