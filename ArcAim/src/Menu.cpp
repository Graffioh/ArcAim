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
			std::cout << "FONTS: Load Error!\n";
		}
}

void Menu::initText()
{
	// Options description text
	formatTxt(m_difficulty0Txt, m_font, 25, sf::Color::White, 345, 55);

	formatTxt(m_crossStyle0Txt, m_font, 25, sf::Color::White, 345, 200);

	formatTxt(m_gameModes0Txt, m_font, 25, sf::Color::White, 365, 350);

	// Info for fps cap
	formatTxt(m_infoTxt, m_font, 25, sf::Color::White, 250, 150);
}

void Menu::initButton()
{
	m_buttons["GAME_START"] = new Button(sf::Color::Red, 210, 60, 270, 160, &m_font, "START GAME", sf::Color::White);
	m_buttons["GAME_OPTIONS"] = new Button(sf::Color::Red, 210, 60, 270, 300, &m_font, "OPTIONS", sf::Color::White);
	m_buttons["GAME_EXIT"] = new Button(sf::Color::Red, 210, 60, 270, 440, &m_font, "EXIT GAME", sf::Color::White);

	m_buttons["GAME_INFO"] = new Button(sf::Color::Red, 60, 210, 520, 230, &m_font, "\nI\nN\nF\nO", sf::Color::White);

	m_buttons["DIFFICULTY_EASY"] = new Button(sf::Color::Green, 150, 40, 100, 100, &m_font, "EASY", sf::Color::Black);
	m_buttons["DIFFICULTY_MEDIUM"] = new Button(sf::Color::Yellow, 150, 40, 330, 100, &m_font, "MEDIUM", sf::Color::Black);
	m_buttons["DIFFICULTY_HARD"] = new Button(sf::Color::Red, 150, 40, 550, 100, &m_font, "HARD", sf::Color::Black);

	m_buttons["CROSS_STYLE1"] = new Button(sf::Color::White, 150, 40, 100, 243, &m_font, "STYLE 1", sf::Color::Black);
	m_buttons["CROSS_STYLE2"] = new Button(sf::Color::White, 150, 40, 330, 243, &m_font, "STYLE 2", sf::Color::Black);
	m_buttons["CROSS_STYLE3"] = new Button(sf::Color::White, 150, 40, 550, 243, &m_font, "STYLE 3", sf::Color::Black);

	m_buttons["REFLEX_ENEMIES"] = new Button(sf::Color::White, 150, 40, 170, 390, &m_font, "REFLEX", sf::Color::Black);
	m_buttons["FALLING_ENEMIES"] = new Button(sf::Color::White, 150, 40, 490, 390, &m_font, "FALLING", sf::Color::Black);

	m_buttons["GAME_GOBACK"] = new Button(sf::Color::White, 150, 40, 330, 500, &m_font, "BACK", sf::Color::Black);
}

void Menu::initCrossStyleImg()
{
	// Cursor style img
	m_crossStyle1Img.loadFromFile("res/Images/GreenReticleOutline.png");
	m_crossStyle1SpriteImg.setTexture(m_crossStyle1Img);
	m_crossStyle1SpriteImg.setPosition(260, 255);

	m_crossStyle2Img.loadFromFile("res/Images/CyanReticle.png");
	m_crossStyle2SpriteImg.setTexture(m_crossStyle2Img);
	m_crossStyle2SpriteImg.setPosition(490, 255);

	m_crossStyle3Img.loadFromFile("res/Images/RedReticle.png");
	m_crossStyle3SpriteImg.setTexture(m_crossStyle3Img);
	m_crossStyle3SpriteImg.setPosition(710, 255);
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
	// Deleting map elements when destructor is called
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
	std::stringstream ss4;

	if (isOptions)
	{
		ss1 << "Difficulty\n";

		ss2 << "Crosshair\n";

		ss3 << "Modes\n";

		m_difficulty0Txt.setString(ss1.str());

		m_crossStyle0Txt.setString(ss2.str());

		m_gameModes0Txt.setString(ss3.str());
	}
}

void Menu::displayInfo(sf::RenderWindow& window)
{
	std::stringstream ss;

	ss << "[F1] VSync (ON/OFF)\n\n[F2] 60 FPS cap\n\n[F3] 144 FPS cap\n\n[F5] Red Cross miss (ON/OFF)\n\n[R] for fast Restart\n\n[ESC] for menu\n";

	m_infoTxt.setString(ss.str());

	window.draw(m_infoTxt);
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

			if (m_buttons["GAME_INFO"]->getBounds().contains(mousePos))
			{
				return GAME_INFO;
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

			if (m_buttons["REFLEX_ENEMIES"]->getBounds().contains(mousePos))
			{
				return REFLEX_ENEMIES;
			}

			if (m_buttons["FALLING_ENEMIES"]->getBounds().contains(mousePos))
			{
				return FALLING_ENEMIES;
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

		target->draw(m_gameModes0Txt);
		m_buttons["REFLEX_ENEMIES"]->draw(target);
		m_buttons["FALLING_ENEMIES"]->draw(target);

		m_buttons["GAME_GOBACK"]->draw(target);
	}
	else
	{
		//target->drawTarget(m_infoCapFpsTxt); Not working

		m_buttons["GAME_START"]->draw(target);
		m_buttons["GAME_OPTIONS"]->draw(target);
		m_buttons["GAME_EXIT"]->draw(target);

		m_buttons["GAME_INFO"]->draw(target);
	}
}

