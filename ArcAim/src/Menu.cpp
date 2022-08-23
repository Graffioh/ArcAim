#include "../headers/Menu.hpp"

void Menu::setupButton(sf::RectangleShape& button, sf::Color color, float width, float height, sf::Vector2f vec2)
{
	button.setFillColor(color);
	button.setPosition(width, height);
	button.setSize(vec2);
}

void Menu::initButton()
{

	setupButton(m_resumeButton, sf::Color(255, 165, 0, 255), WIN_WIDTH / 3, WIN_HEIGHT / 2.5, sf::Vector2f(280, 60));

	setupButton(m_menuButton1, sf::Color::Red, WIN_WIDTH / 3, 160, sf::Vector2f(260, 60));

	setupButton(m_menuButton2, sf::Color::Red, WIN_WIDTH / 3, 300, sf::Vector2f(260, 60));

	setupButton(m_menuButton3, sf::Color::Red, WIN_WIDTH / 3, 440, sf::Vector2f(260, 60));

}

void Menu::formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float width, float height)
{
	txt.setFont(font);
	txt.setCharacterSize(size);
	txt.setFillColor(color);
	txt.setString("NONE");
	txt.setPosition(width, height);
}

void Menu::initText()
{
	if (!m_font.loadFromFile("res/Fonts/Minecraft.ttf"))
	{
		std::cout << "FONTS: Load Error!" << std::endl;
	}

	// old start screen text
	formatTxt(m_startScreenTxt, m_font, 69, sf::Color::Green, 25, WIN_HEIGHT / 3.5);

	// Pause Screen Text
	formatTxt(m_pauseScreenTxt, m_font, 30, sf::Color::White, WIN_WIDTH / 2.7f, WIN_HEIGHT / 2.4);

	// 1st menu button text
	formatTxt(m_menuTxt1, m_font, 30, sf::Color::White, WIN_WIDTH / 2.65f, 170);

	// 2nd menu button text
	formatTxt(m_menuTxt2, m_font, 30, sf::Color::White, WIN_WIDTH / 2.5f, 310);

	// 3rd menu button text
	formatTxt(m_menuTxt3, m_font, 30, sf::Color::White, WIN_WIDTH / 2.6f, 450);

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
	std::stringstream ss2;
	std::stringstream ss3;
	
	if (isPause)
	{
		ss << "RESUME GAME" << std::endl;

		m_pauseScreenTxt.setString(ss.str());
	}
	/*else
	{
		ss << "\t  PRESS ENTER"  << std::endl;
		ss << "TO START THE GAME" << std::endl;

		m_startScreenTxt.setString(ss.str());
	}*/
	else
	{
		ss << "START GAME" << std::endl;
		ss2 << "OPTIONS" << std::endl;
		ss3 << "Go Fck Yrslf" << std::endl;
		
		m_menuTxt1.setString(ss.str());
		m_menuTxt2.setString(ss2.str());
		m_menuTxt3.setString(ss3.str());
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
		//window.draw(m_startScreenTxt);

		window.draw(m_menuTxt1);
		window.draw(m_menuTxt2);
		window.draw(m_menuTxt3);
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
			if (m_resumeButton.getGlobalBounds().contains(mousePos))
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

bool Menu::startGame(sf::Vector2f mousePos)
{
	// Adjusting offset
	mousePos.x = mousePos.x + 8;
	mousePos.y = mousePos.y + 8;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;
			if (m_menuButton1.getGlobalBounds().contains(mousePos))
			{
				return true;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return true;
	}
	else
	{
		m_mouseHeld = false;
	}
	
	return false;
}

bool Menu::exitGame(sf::Vector2f mousePos)
{
	// Adjusting offset
	mousePos.x = mousePos.x + 8;
	mousePos.y = mousePos.y + 8;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;
			if (m_menuButton3.getGlobalBounds().contains(mousePos))
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

char Menu::gameStatus(sf::Vector2f mousePos)
{
	// Adjusting offset
	mousePos.x = mousePos.x;
	mousePos.y = mousePos.y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			if (m_menuButton1.getGlobalBounds().contains(mousePos))
			{
				return '1';
			}
			if (m_menuButton2.getGlobalBounds().contains(mousePos))
			{
				return '2';
			}
			if (m_menuButton3.getGlobalBounds().contains(mousePos))
			{
				return '3';
			}
			if (m_resumeButton.getGlobalBounds().contains(mousePos))
			{
				return '4';
			}
			m_mouseHeld = true;
		}
	}
	else
	{
		m_mouseHeld = false;
	}

	return '0';
}

void Menu::displayMenu(sf::RenderWindow& window, bool isPause)
{
	window.clear(sf::Color(9, 9, 9, 255));

	if (isPause)
	{
		window.draw(m_resumeButton);
	}
	else
	{
		window.draw(m_menuButton1);
		window.draw(m_menuButton2);
		window.draw(m_menuButton3);
	}
}

