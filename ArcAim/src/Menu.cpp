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
	m_buttons["GAME_START"] = new Button(sf::Color::Red, sf::Color(150, 0, 0), 210, 60, 300, 160, &m_font, "START GAME", sf::Color::White);
	m_buttons["GAME_OPTIONS"] = new Button(sf::Color::Red, sf::Color(150, 0, 0), 210, 60, 300, 300, &m_font, "OPTIONS", sf::Color::White);
	m_buttons["GAME_EXIT"] = new Button(sf::Color::Red, sf::Color(150, 0, 0), 210,  60, 300, 440, &m_font, "EXIT GAME", sf::Color::White);

	m_buttons["GAME_INFO"] = new Button(sf::Color::Blue, sf::Color(0, 0, 130), 30, 30, 10, 10, &m_font, "i", sf::Color::White);

	m_buttons["DIFFICULTY_EASY"] = new Button(sf::Color::Green, sf::Color(0, 130, 0), 150, 40, 100, 100, &m_font, "EASY", sf::Color::Black);
	m_buttons["DIFFICULTY_MEDIUM"] = new Button(sf::Color::Yellow, sf::Color(215, 210, 0), 150, 40, 330, 100, &m_font, "MEDIUM", sf::Color::Black);
	m_buttons["DIFFICULTY_HARD"] = new Button(sf::Color::Red, sf::Color(150, 0, 0), 150, 40, 550, 100, &m_font, "HARD", sf::Color::Black);

	m_buttons["CROSS_STYLE1"] = new Button(sf::Color::White, sf::Color(190,190,190), 150, 40, 100, 243, &m_font, "STYLE 1", sf::Color::Black);
	m_buttons["CROSS_STYLE2"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 150, 40, 330, 243, &m_font, "STYLE 2", sf::Color::Black);
	m_buttons["CROSS_STYLE3"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 150, 40, 550, 243, &m_font, "STYLE 3", sf::Color::Black);

	m_buttons["REFLEX_ENEMIES"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 150, 40, 100, 390, &m_font, "REFLEX", sf::Color::Black);
	m_buttons["PRECISION_ENEMIES"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 150, 40, 330, 390, &m_font, "PRECISION", sf::Color::Black);
	m_buttons["FALLING_ENEMIES"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 150, 40, 550, 390, &m_font, "FALLING", sf::Color::Black);

	m_buttons["GAME_GOBACK"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 40, 30, 10, 10, "res/Images/backarrow_b.png", true);

	m_buttons["MENU_UP"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 30, 30, 740, 30, "res/Images/uparrow.png", false);
	m_buttons["MENU_DOWN"] = new Button(sf::Color::White, sf::Color(190, 190, 190), 30, 30, 740, 540, "res/Images/downarrow.png", false);

	m_btnSoundBuffer.loadFromFile("res/Sounds/buttonsound.wav");
	m_btnSound.setBuffer(m_btnSoundBuffer);
	m_btnSound.setVolume(9);
}

void Menu::initCrossStyleImg()
{
	// Cursor style img
	m_crossStyle1Img.loadFromFile("res/Images/GreenReticleOutline.png");
	m_crossStyle1SpriteImg.setTexture(m_crossStyle1Img);
	m_crossStyle1SpriteImg.setPosition(250, 247);

	m_crossStyle2Img.loadFromFile("res/Images/CyanReticle.png");
	m_crossStyle2SpriteImg.setTexture(m_crossStyle2Img);
	m_crossStyle2SpriteImg.setPosition(480, 247);

	m_crossStyle3Img.loadFromFile("res/Images/RedReticleOpen.png");
	m_crossStyle3SpriteImg.setTexture(m_crossStyle3Img);
	m_crossStyle3SpriteImg.setPosition(705, 247);
}

Menu::Menu()
	:m_mouseHeld(false), m_btnOutlineWhenClicked(3.5), m_yDownUpValue(0.f), m_limitUp(0.f)
{
	initFont();
	initText();
	initButton();
	initCrossStyleImg();

	m_view.reset(sf::FloatRect(0, 0, 800, 600));
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

void Menu::updateBtn(sf::Vector2f mousePos)
{
	for (auto& it : m_buttons)
	{
		it.second->updateBtnColorWhenHovered(mousePos);
	}
}

void Menu::displayInfo(sf::RenderWindow& window)
{
	std::stringstream ss;

	ss << "[F1] VSync (ON/OFF)\n\n[F2] 60 FPS cap\n\n[F3] 144 FPS cap\n\n[F5] Red Cross miss (ON/OFF)\n\n[R] for fast Restart\n\n[ESC] for menu\n";

	m_infoTxt.setString(ss.str());

	window.draw(m_infoTxt);
	m_buttons["GAME_GOBACK"]->drawBtn(&window);
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
				playBtnSound();
				return GAME_START;
			}

			if (m_buttons["GAME_OPTIONS"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				return GAME_OPTIONS;
			}

			if (m_buttons["GAME_EXIT"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				return GAME_EXIT;
			}

			if (m_buttons["GAME_INFO"]->getBounds().contains(mousePos))
			{
				playBtnSound();
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
				playBtnSound();
				m_buttons["DIFFICULTY_EASY"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["DIFFICULTY_MEDIUM"]->updateBtnOutlineWhenClicked(0);
				m_buttons["DIFFICULTY_HARD"]->updateBtnOutlineWhenClicked(0);
				return DIFFICULTY_EASY;
			}

			if (m_buttons["DIFFICULTY_MEDIUM"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["DIFFICULTY_EASY"]->updateBtnOutlineWhenClicked(0);
				m_buttons["DIFFICULTY_MEDIUM"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["DIFFICULTY_HARD"]->updateBtnOutlineWhenClicked(0);
				return DIFFICULTY_MEDIUM;
			}

			if (m_buttons["DIFFICULTY_HARD"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["DIFFICULTY_EASY"]->updateBtnOutlineWhenClicked(0);
				m_buttons["DIFFICULTY_MEDIUM"]->updateBtnOutlineWhenClicked(0);
				m_buttons["DIFFICULTY_HARD"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				return DIFFICULTY_HARD;
			}

			if (m_buttons["CROSS_STYLE1"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["CROSS_STYLE1"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["CROSS_STYLE2"]->updateBtnOutlineWhenClicked(0);
				m_buttons["CROSS_STYLE3"]->updateBtnOutlineWhenClicked(0);
				return CROSS_STYLE1;
			}

			if (m_buttons["CROSS_STYLE2"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["CROSS_STYLE1"]->updateBtnOutlineWhenClicked(0);
				m_buttons["CROSS_STYLE2"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["CROSS_STYLE3"]->updateBtnOutlineWhenClicked(0);
				return CROSS_STYLE2;
			}

			if (m_buttons["CROSS_STYLE3"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["CROSS_STYLE1"]->updateBtnOutlineWhenClicked(0);
				m_buttons["CROSS_STYLE2"]->updateBtnOutlineWhenClicked(0);
				m_buttons["CROSS_STYLE3"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				return CROSS_STYLE3;
			}

			if (m_buttons["REFLEX_ENEMIES"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["REFLEX_ENEMIES"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["PRECISION_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				m_buttons["FALLING_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				return REFLEX_ENEMIES;
			}

			if (m_buttons["PRECISION_ENEMIES"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["REFLEX_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				m_buttons["PRECISION_ENEMIES"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				m_buttons["FALLING_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				return PRECISION_ENEMIES;
			}

			if (m_buttons["FALLING_ENEMIES"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_buttons["REFLEX_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				m_buttons["PRECISION_ENEMIES"]->updateBtnOutlineWhenClicked(0);
				m_buttons["FALLING_ENEMIES"]->updateBtnOutlineWhenClicked(m_btnOutlineWhenClicked);
				return FALLING_ENEMIES;
			}

			if (m_buttons["GAME_GOBACK"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				return GAME_GOBACK;
			}

			if (m_buttons["MENU_UP"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_yDownUpValue = -30;
				m_limitUp += m_yDownUpValue;
				if (m_limitUp >= 0)
				{
					m_view.move(0.f, m_yDownUpValue);
					m_buttons["MENU_UP"]->setUpDownBtnYPos(m_yDownUpValue);
					m_buttons["MENU_DOWN"]->setUpDownBtnYPos(m_yDownUpValue);
					m_buttons["GAME_GOBACK"]->setUpDownBtnYPos(m_yDownUpValue);
				}
				else
				{
					m_limitUp = 0;
				}
			}

			if (m_buttons["MENU_DOWN"]->getBounds().contains(mousePos))
			{
				playBtnSound();
				m_yDownUpValue = 30;
				m_limitUp += m_yDownUpValue;
				m_view.move(0.f, m_yDownUpValue);
				m_buttons["MENU_UP"]->setUpDownBtnYPos(m_yDownUpValue);
				m_buttons["MENU_DOWN"]->setUpDownBtnYPos(m_yDownUpValue);
				m_buttons["GAME_GOBACK"]->setUpDownBtnYPos(m_yDownUpValue);
			}

		}
	}
	else
	{
		m_mouseHeld = false;
	}

	return '0';
}

void Menu::playBtnSound()
{
	m_btnSound.play();
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
		m_buttons["DIFFICULTY_EASY"]->drawBtn(target);
		m_buttons["DIFFICULTY_MEDIUM"]->drawBtn(target);
		m_buttons["DIFFICULTY_HARD"]->drawBtn(target);

		target->draw(m_crossStyle0Txt);
		m_buttons["CROSS_STYLE1"]->drawBtn(target);
		target->draw(m_crossStyle1SpriteImg);

		m_buttons["CROSS_STYLE2"]->drawBtn(target);
		target->draw(m_crossStyle2SpriteImg);
		
		m_buttons["CROSS_STYLE3"]->drawBtn(target);
		target->draw(m_crossStyle3SpriteImg);

		target->draw(m_gameModes0Txt);
		m_buttons["REFLEX_ENEMIES"]->drawBtn(target);
		m_buttons["PRECISION_ENEMIES"]->drawBtn(target);
		m_buttons["FALLING_ENEMIES"]->drawBtn(target);

		m_buttons["GAME_GOBACK"]->drawBtn(target);

		m_buttons["MENU_UP"]->drawBtn(target);
		m_buttons["MENU_DOWN"]->drawBtn(target);
	}
	else
	{
		m_buttons["GAME_START"]->drawBtn(target);
		m_buttons["GAME_OPTIONS"]->drawBtn(target);
		m_buttons["GAME_EXIT"]->drawBtn(target);

		m_buttons["GAME_INFO"]->drawBtn(target);
	}
}

sf::View Menu::getView()
{
	return m_view;
}

