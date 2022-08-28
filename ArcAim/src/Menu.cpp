#include "../headers/Menu.hpp"

void Menu::setupButton(sf::RectangleShape& button, sf::Color color, sf::Vector2f vec2, float x, float y)
{
	button.setFillColor(color);
	button.setPosition(x, y);
	button.setSize(vec2);
}

void Menu::initButton()
{
	setupButton(m_resumeButton, sf::Color(255, 165, 0, 255), sf::Vector2f(280, 60), WIN_WIDTH / 3, WIN_HEIGHT / 2.5);

	// Cursor style img
	m_crossStyle1Img.loadFromFile("res/Images/GreenReticleOutline.png");
	m_crossStyle1SpriteImg.setTexture(m_crossStyle1Img);
	m_crossStyle1SpriteImg.setPosition(240, 262);

	m_crossStyle2Img.loadFromFile("res/Images/CyanReticle.png");
	m_crossStyle2SpriteImg.setTexture(m_crossStyle2Img);
	m_crossStyle2SpriteImg.setPosition(470, 262);

	m_crossStyle3Img.loadFromFile("res/Images/RedReticle.png");
	m_crossStyle3SpriteImg.setTexture(m_crossStyle3Img);
	m_crossStyle3SpriteImg.setPosition(690, 262);
}

void Menu::formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float x, float y)
{
	txt.setFont(font);
	txt.setCharacterSize(size);
	txt.setFillColor(color);
	txt.setString("NONE");
	txt.setPosition(x, y);
}

void Menu::initText()
{
	// Loading the font
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
	formatTxt(m_difficulty0Txt, m_font, 25, sf::Color::White, 335, 50);

	formatTxt(m_difficulty1Txt, m_font, 25, sf::Color::White, 135, 105);
	formatTxt(m_difficulty2Txt, m_font, 25, sf::Color::White, 347, 105);
	formatTxt(m_difficulty3Txt, m_font, 25, sf::Color::White, 580, 105);

	// Crosshair style button text
	formatTxt(m_crossStyle0Txt, m_font, 25, sf::Color::White, 335, 200);

	formatTxt(m_crossStyle1Txt, m_font, 25, sf::Color::Black, 113, 255);
	formatTxt(m_crossStyle2Txt, m_font, 25, sf::Color::Black, 343, 255);
	formatTxt(m_crossStyle3Txt, m_font, 25, sf::Color::Black, 563, 255);

	// Back button text
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
	setupButton(m_menuButton1, sf::Color::Red, sf::Vector2f(260, 60), WIN_WIDTH / 3, 160);
	setupButton(m_menuButton2, sf::Color::Red, sf::Vector2f(260, 60), WIN_WIDTH / 3, 300);
	setupButton(m_menuButton3, sf::Color::Red, sf::Vector2f(260, 60), WIN_WIDTH / 3, 440);
}

void Menu::initOptionsBtn()
{
	setupButton(m_difficulty1Btn, sf::Color::Green, sf::Vector2f(130, 40), 100, 100);
	setupButton(m_difficulty2Btn, sf::Color::Blue, sf::Vector2f(130, 40), 330, 100);
	setupButton(m_difficulty3Btn, sf::Color::Red, sf::Vector2f(130, 40), 550, 100);

	setupButton(m_crossStyle1Btn, sf::Color::White, sf::Vector2f(130, 40), 100, 250);
	setupButton(m_crossStyle2Btn, sf::Color::White, sf::Vector2f(130, 40), 330, 250);
	setupButton(m_crossStyle3Btn, sf::Color::White, sf::Vector2f(130, 40), 550, 250);

	setupButton(m_returnToMenuBtn, sf::Color::Yellow, sf::Vector2f(130, 40), 330, 450);

	// try (moving the button)
	m_menuButton3 = m_menuButton2;
}


void Menu::updateText(bool isPause, bool isOptions)
{
	std::stringstream ss0;
	std::stringstream ss00;
	std::stringstream ss;
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;
	std::stringstream ss4;
	std::stringstream ss5;
	std::stringstream ss6;
	std::stringstream ss7;

	if (isPause)
	{
		ss << "RESUME GAME" << std::endl;

		m_pauseScreenTxt.setString(ss.str());
	}
	else if(isOptions)
	{
		ss0 << "Difficulty" << std::endl;
		ss << "EASY" << std::endl;
		ss1 << "MEDIUM" << std::endl;
		ss2 << "HARD" << std::endl;

		ss00 << "Crosshair" << std::endl;
		ss4 << "STYLE 1" << std::endl;
		ss5 << "STYLE 2" << std::endl;
		ss6 << "STYLE 3" << std::endl;

		ss7 << "Back" << std::endl;

		m_difficulty0Txt.setString(ss0.str());
		m_difficulty1Txt.setString(ss.str());
		m_difficulty2Txt.setString(ss1.str());
		m_difficulty3Txt.setString(ss2.str());

		m_crossStyle0Txt.setString(ss00.str());
		m_crossStyle1Txt.setString(ss4.str());
		m_crossStyle2Txt.setString(ss5.str());
		m_crossStyle3Txt.setString(ss6.str());

		m_returnToMenuTxt.setString(ss7.str());
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

			if (m_difficulty1Btn.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_EASY;
			}

			if (m_difficulty2Btn.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_MEDIUM;
			}

			if (m_difficulty3Btn.getGlobalBounds().contains(mousePos))
			{
				return DIFFICULTY_HARD;
			}

			if (m_crossStyle1Btn.getGlobalBounds().contains(mousePos))
			{
				return CROSS_STYLE1;
			}

			if (m_crossStyle2Btn.getGlobalBounds().contains(mousePos))
			{
				return CROSS_STYLE2;
			}

			if (m_crossStyle3Btn.getGlobalBounds().contains(mousePos))
			{
				return CROSS_STYLE3;
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
		// Drawing buttons
		window.draw(m_difficulty1Btn);
		window.draw(m_difficulty2Btn);
		window.draw(m_difficulty3Btn);

		window.draw(m_crossStyle1Btn);
		window.draw(m_crossStyle2Btn);
		window.draw(m_crossStyle3Btn);

		window.draw(m_crossStyle1SpriteImg);
		window.draw(m_crossStyle2SpriteImg);
		window.draw(m_crossStyle3SpriteImg);

		window.draw(m_returnToMenuBtn);

		// Drawin button text
		window.draw(m_difficulty0Txt);
		window.draw(m_difficulty1Txt);
		window.draw(m_difficulty2Txt);
		window.draw(m_difficulty3Txt);

		window.draw(m_crossStyle0Txt);
		window.draw(m_crossStyle1Txt);
		window.draw(m_crossStyle2Txt);
		window.draw(m_crossStyle3Txt);

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

