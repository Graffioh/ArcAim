#include "../headers/Menu.hpp"


void Menu::formatTxt(sf::Text& txt, sf::Font& font, unsigned int size, sf::Color color, float x, float y)
{
	txt.setFont(font);
	txt.setCharacterSize(size);
	txt.setFillColor(color);
	txt.setString("NONE");
	txt.setPosition(x, y);
}

void Menu::initFont()
{
	if (!m_font.loadFromFile("res/Fonts/Minecraft.ttf"))
		{
			std::cout << "FONTS: Load Error!" << std::endl;
		}
}

void Menu::initText()
{
	// Difficulty button text
	formatTxt(m_difficulty0Txt, m_font, 25, sf::Color::White, 345, 55);

	// Crosshair style button text
	formatTxt(m_crossStyle0Txt, m_font, 25, sf::Color::White, 345, 235);

	// Info for fps cap
	formatTxt(m_infoCapFpsTxt, m_font, 25, sf::Color::White, 150, 0);
}

void Menu::initButton()
{
	m_buttons["GAME_START"] = new Button(sf::Color::Red, 210, 60, 300, 160, &m_font, "START GAME", sf::Color::White);
	m_buttons["GAME_OPTIONS"] = new Button(sf::Color::Red, 210, 60, 300, 300, &m_font, "OPTIONS", sf::Color::White);
	m_buttons["GAME_EXIT"] = new Button(sf::Color::Red, 210, 60, 300, 440, &m_font, "EXIT GAME", sf::Color::White);

	m_buttons["DIFFICULTY_EASY"] = new Button(sf::Color::Green, 150, 40, 100, 100, &m_font, "EASY", sf::Color::Black);
	m_buttons["DIFFICULTY_MEDIUM"] = new Button(sf::Color::Yellow, 150, 40, 330, 100, &m_font, "MEDIUM", sf::Color::Black);
	m_buttons["DIFFICULTY_HARD"] = new Button(sf::Color::Red, 150, 40, 550, 100, &m_font, "HARD", sf::Color::Black);

	m_buttons["CROSS_STYLE1"] = new Button(sf::Color::White, 150, 40, 100, 280, &m_font, "STYLE 1", sf::Color::Black);
	m_buttons["CROSS_STYLE2"] = new Button(sf::Color::White, 150, 40, 330, 280, &m_font, "STYLE 2", sf::Color::Black);
	m_buttons["CROSS_STYLE3"] = new Button(sf::Color::White, 150, 40, 550, 280, &m_font, "STYLE 3", sf::Color::Black);

	m_buttons["GAME_GOBACK"] = new Button(sf::Color::White, 150, 40, 330, 450, &m_font, "BACK", sf::Color::Black);
}

void Menu::initCrossStyleImg()
{
	// Cursor style img
	m_crossStyle1Img.loadFromFile("res/Images/GreenReticleOutline.png");
	m_crossStyle1SpriteImg.setTexture(m_crossStyle1Img);
	m_crossStyle1SpriteImg.setPosition(260, 292);

	m_crossStyle2Img.loadFromFile("res/Images/CyanReticle.png");
	m_crossStyle2SpriteImg.setTexture(m_crossStyle2Img);
	m_crossStyle2SpriteImg.setPosition(490, 292);

	m_crossStyle3Img.loadFromFile("res/Images/RedReticle.png");
	m_crossStyle3SpriteImg.setTexture(m_crossStyle3Img);
	m_crossStyle3SpriteImg.setPosition(710, 292);
}

Menu::Menu()
	:m_mouseHeld(false)
{
	initFont();
	initText();
	initButton();
	initCrossStyleImg();
}

Menu::~Menu()
{
	// blackbox
	auto it = m_buttons.begin();

	for (it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		delete it->second;
	}
}

void Menu::updateText(bool isOptions)
{
	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;

	if (isOptions)
	{
		ss1 << "Difficulty" << std::endl;

		ss2 << "Crosshair" << std::endl;

		m_difficulty0Txt.setString(ss1.str());

		m_crossStyle0Txt.setString(ss2.str());
	}
	else
	{	
		m_infoCapFpsTxt.setString(ss3.str());

		ss3 << "F1 for VSync - F2 for 60 FPS cap - F3 for 144 FPS cap" << std::endl;
		ss3 << "\t\t\t\t\t\t   ESC for fast Restart" << std::endl;
	}
}

char Menu::activateStartBtn(sf::Vector2f mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_mouseHeld)
		{
			m_mouseHeld = true;

			if (m_buttons["GAME_START"]->getBounds().contains(mousePos))
			{
				return GAME_START;
			}

			if (m_buttons["GAME_OPTIONS"]->getBounds().contains(mousePos))
			{
				return GAME_OPTIONS;
			}

			if (m_buttons["GAME_EXIT"]->getBounds().contains(mousePos))
			{
				return GAME_EXIT;
			}
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
			m_mouseHeld = true;

			if (m_buttons["DIFFICULTY_EASY"]->getBounds().contains(mousePos))
			{
				return DIFFICULTY_EASY;
			}

			if (m_buttons["DIFFICULTY_MEDIUM"]->getBounds().contains(mousePos))
			{
				return DIFFICULTY_MEDIUM;
			}

			if (m_buttons["DIFFICULTY_HARD"]->getBounds().contains(mousePos))
			{
				return DIFFICULTY_HARD;
			}

			if (m_buttons["CROSS_STYLE1"]->getBounds().contains(mousePos))
			{
				return CROSS_STYLE1;
			}

			if (m_buttons["CROSS_STYLE2"]->getBounds().contains(mousePos))
			{
				return CROSS_STYLE2;
			}

			if (m_buttons["CROSS_STYLE3"]->getBounds().contains(mousePos))
			{
				return CROSS_STYLE3;
			}

			if (m_buttons["GAME_GOBACK"]->getBounds().contains(mousePos))
			{
				return GAME_GOBACK;
			}
		}
	}
	else
	{
		m_mouseHeld = false;
	}

	return '0';
}


void Menu::displayMenu(sf::RenderTarget* target, sf::RenderWindow& window, bool isOptions)
{
	if (!target)
	{
		target = &window;
	}

	window.clear(sf::Color(9, 9, 9, 255));

	if (isOptions)
	{
		target->draw(m_difficulty0Txt);
		m_buttons["DIFFICULTY_EASY"]->draw(target);
		m_buttons["DIFFICULTY_MEDIUM"]->draw(target);
		m_buttons["DIFFICULTY_HARD"]->draw(target);

		target->draw(m_crossStyle0Txt);
		m_buttons["CROSS_STYLE1"]->draw(target);
		target->draw(m_crossStyle1SpriteImg);

		m_buttons["CROSS_STYLE2"]->draw(target);
		target->draw(m_crossStyle2SpriteImg);
		
		m_buttons["CROSS_STYLE3"]->draw(target);
		target->draw(m_crossStyle3SpriteImg);

		m_buttons["GAME_GOBACK"]->draw(target);
	}
	else
	{
		//target->draw(m_infoCapFpsTxt); Not working

		m_buttons["GAME_START"]->draw(target);
		m_buttons["GAME_OPTIONS"]->draw(target);
		m_buttons["GAME_EXIT"]->draw(target);
	}
}

