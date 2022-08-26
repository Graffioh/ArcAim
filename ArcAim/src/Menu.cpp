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

	/*setupButton(m_menuButton1, sf::Color::Red, WIN_WIDTH / 3, 160, sf::Vector2f(260, 60));
	setupButton(m_menuButton2, sf::Color::Red, WIN_WIDTH / 3, 300, sf::Vector2f(260, 60));
	setupButton(m_menuButton3, sf::Color::Red, WIN_WIDTH / 3, 440, sf::Vector2f(260, 60));*/

	/*setupButton(m_difficultyBtn1, sf::Color::Green, 100 , 250, sf::Vector2f(130, 40));
	setupButton(m_difficultyBtn2, sf::Color::Blue, 330, 250, sf::Vector2f(130, 40));
	setupButton(m_difficultyBtn3, sf::Color::Red, 550, 250, sf::Vector2f(130, 40));*/

	//setupButton(m_returnToMenuBtn, sf::Color::Yellow, 330, 450, sf::Vector2f(130, 40));
	//setupButton(m_returnToMenuBtn, sf::Color::Yellow, 330, 500, sf::Vector2f(130, 40));

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

	// FPS cap infos text
	formatTxt(m_infoCapFpsTxt, m_font, 25, sf::Color::White, 50, 0);

	// 1st,2nd,3rd menu buttons text
	formatTxt(m_menuTxt1, m_font, 30, sf::Color::White, WIN_WIDTH / 2.65f, 170);
	formatTxt(m_menuTxt2, m_font, 30, sf::Color::White, WIN_WIDTH / 2.50f, 310);
	formatTxt(m_menuTxt3, m_font, 30, sf::Color::White, WIN_WIDTH / 2.60f, 450);

	// Difficulty button text
	formatTxt(m_difficultyTxt1, m_font, 25, sf::Color::White, 130, 255);
	formatTxt(m_difficultyTxt2, m_font, 25, sf::Color::White, 347, 255);
	formatTxt(m_difficultyTxt3, m_font, 25, sf::Color::White, 580, 255);

	formatTxt(m_returnToMenuTxt, m_font, 25, sf::Color::Black, 365, 455);
}

Menu::Menu()
	:m_mouseHeld(false)
{
	initButton();
	initText();
}

void Menu::initStartBtn()
{
	setupButton(m_menuButton1, sf::Color::Red, WIN_WIDTH / 3, 160, sf::Vector2f(260, 60));
	setupButton(m_menuButton2, sf::Color::Red, WIN_WIDTH / 3, 300, sf::Vector2f(260, 60));
	setupButton(m_menuButton3, sf::Color::Red, WIN_WIDTH / 3, 440, sf::Vector2f(260, 60));
}

void Menu::initOptionsBtn()
{
	setupButton(m_difficultyBtn1, sf::Color::Green, 100, 250, sf::Vector2f(130, 40));
	setupButton(m_difficultyBtn2, sf::Color::Blue, 330, 250, sf::Vector2f(130, 40));
	setupButton(m_difficultyBtn3, sf::Color::Red, 550, 250, sf::Vector2f(130, 40));

	setupButton(m_returnToMenuBtn, sf::Color::Yellow, 330, 450, sf::Vector2f(130, 40));

	// try (moving the button)
	m_menuButton3 = m_menuButton2;
}


void Menu::updateText(bool isPause, bool isOptions)
{
	std::stringstream ss;
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;
	std::stringstream ss4;
	std::stringstream ss5;
	std::stringstream ss6;

	if (isPause)
	{
		ss << "RESUME GAME" << std::endl;

		m_pauseScreenTxt.setString(ss.str());
	}
	else if(isOptions)
	{
		ss << "EASY" << std::endl;
		ss1 << "MEDIUM" << std::endl;
		ss2 << "HARD" << std::endl;

		ss3 << "Back" << std::endl;

		m_difficultyTxt1.setString(ss.str());
		m_difficultyTxt2.setString(ss1.str());
		m_difficultyTxt3.setString(ss2.str());

		m_returnToMenuTxt.setString(ss3.str());
	}
	else
	{
		ss << "F1 for VSync - F2 for 60 FPS cap - F3 for 144 FPS cap" << std::endl;
		ss << "\t\t\t\t\t\t   ESC for fast Restart" << std::endl;
		ss1 << "START GAME" << std::endl;
		ss2 << "OPTIONS" << std::endl;
		ss3 << "Go Fck Yrslf" << std::endl;
		
		m_infoCapFpsTxt.setString(ss.str());

		m_menuTxt1.setString(ss1.str());
		m_menuTxt2.setString(ss2.str());
		m_menuTxt3.setString(ss3.str());
	}
}

char Menu::activateStartBtn(sf::Vector2f mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			if (m_menuButton1.getGlobalBounds().contains(mousePos))
			{
				return GAME_START;
			}

			if (m_menuButton2.getGlobalBounds().contains(mousePos))
			{
				return GAME_OPTIONS;
			}

			if (m_menuButton3.getGlobalBounds().contains(mousePos))
			{
				return GAME_EXIT;
			}

			if (m_resumeButton.getGlobalBounds().contains(mousePos))
			{
				return GAME_RESUME;
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

char Menu::activateOptionBtn(sf::Vector2f mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			if (m_returnToMenuBtn.getGlobalBounds().contains(mousePos))
			{
				return GAME_GOBACK;
			}

			if (m_difficultyBtn1.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_EASY;
			}

			if (m_difficultyBtn2.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_MEDIUM;
			}

			if (m_difficultyBtn3.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_HARD;
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


void Menu::displayMenu(sf::RenderWindow& window, bool isPause, bool isOptions)
{
	window.clear(sf::Color(9, 9, 9, 255));

	if (isPause)
	{
		window.draw(m_resumeButton);
		window.draw(m_pauseScreenTxt);
	}
	else if (isOptions)
	{
		window.draw(m_difficultyBtn1);
		window.draw(m_difficultyBtn2);
		window.draw(m_difficultyBtn3);
		window.draw(m_returnToMenuBtn);

		window.draw(m_difficultyTxt1);
		window.draw(m_difficultyTxt2);
		window.draw(m_difficultyTxt3);
		window.draw(m_returnToMenuTxt);
	}
	else
	{
		window.draw(m_infoCapFpsTxt);

		window.draw(m_menuButton1);
		window.draw(m_menuButton2);
		window.draw(m_menuButton3);

		window.draw(m_menuTxt1);
		window.draw(m_menuTxt2);
		window.draw(m_menuTxt3);
	}	
}

