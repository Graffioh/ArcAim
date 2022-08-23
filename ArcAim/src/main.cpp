#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../headers/Global.hpp"
#include "../headers/WindowManager.hpp"
#include "../headers/TargetsManager.hpp"
#include "../headers/TargetC.hpp"
#include "../headers/MouseManager.hpp"
#include "../headers/Menu.hpp"
#include "../headers/TimeManager.hpp"

sf::Clock TimeManager::clockCountdown;
sf::Clock TimeManager::clockTargets;

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "ArcAim", sf::Style::Default);
	window->setFramerateLimit(300);

	sf::Event event;

	WindowManager winManager;

	TargetsManager targetsManager;

	MouseManager mouseManager;

	Menu menu;

	char gameStatus = 0;
	unsigned short health = 0;
	short points = 0;
	bool endgame = false;
	bool pause = false;
	bool start = false;
	bool exit = false;
	bool vsync = false;
	bool restart = false;

	winManager.initWindow(window);

	// Game loop
	while (window->isOpen())
	{
		// EVENTS
		// 
		// Press esc or window's x to close the window and P to pause the game
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				std::cout << "Process Killed" << std::endl;
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
					std::cout << "Process Killed" << std::endl;
				}

				if (event.key.code == sf::Keyboard::P)
				{
					pause = !pause;
					std::cout << "Game Paused" << std::endl;
				}

				if (event.key.code == sf::Keyboard::F1) // Idk if it works
				{
					vsync = !vsync;
					window->setVerticalSyncEnabled(vsync);
					std::cout << "VSync Toggled" << std::endl;
				}

				if (event.key.code == sf::Keyboard::F2)
				{
					window->setFramerateLimit(60);
					
					std::cout << "Frame limit set to 60" << std::endl;
				}

				if (event.key.code == sf::Keyboard::F3)
				{
					window->setFramerateLimit(144);
					
					std::cout << "Frame limit set to 144" << std::endl;
				}

				if (event.key.code == sf::Keyboard::R && endgame)
				{
					restart = true;
					std::cout << "Game Restarted" << std::endl;
				}

			default:
				break;
			}
		}

		// START MENU
		if (!start)
		{
			menu.displayMenu(*window, pause);
			menu.updateText(pause);
			menu.drawText(*window, pause);

			if (menu.gameStatus(mouseManager.getMousePos()) == GAME_START)
			{
				start = true;
			}

			if (menu.gameStatus(mouseManager.getMousePos()) == GAME_EXIT)
			{
				window->close();
			}

			mouseManager.updateMousePos(*window);

			// Reset the clock to sync it when You are not in the start menu
			TimeManager::clockCountdown.restart();
			TimeManager::clockTargets.restart();
		}
		else
		{

			window->setMouseCursorVisible(false);

			// Clear the window and set the grey background

			window->clear(sf::Color(18, 18, 18, 255));


			mouseManager.updateMousePos(*window);

			// TARGET
			//
			// Managing target's funcs
			targetsManager.setSpawnType(REFLEX_ENEMIES);
			if (!pause && !endgame)
			{
				targetsManager.update();
				targetsManager.eraseOnClick(mouseManager.getMousePos());


				targetsManager.draw(*window);

			}

			mouseManager.syncPosition(*window);

			mouseManager.draw(*window);


			points = targetsManager.getPoints();
			health = targetsManager.getPlayerHealth();

			// WINDOW
			// 
			// HUD Text update and render + pause mechanism (if -1 change the text to PAUSE)
			if (!pause)
			{
				winManager.updateClock();
				winManager.updateTimerText();
				winManager.updateText(points, health, endgame);
			}
			else // PAUSE Setup
			{
				window->setMouseCursorVisible(true);

				winManager.updateText(-1, health, endgame);

				menu.displayMenu(*window, pause);
				menu.updateText(pause);
				menu.drawText(*window, pause);

				//TimeManager::clockCountdown.restart(); //not necessary
				TimeManager::clockTargets.restart();

				if (menu.gameStatus(mouseManager.getMousePos()) == GAME_RESUME)
				{
					pause = !pause;
				}
			}

			winManager.drawText();
			winManager.drawTimerText();

			// GAME OVER & RESTART
			//
			// Endgame trigger
			if (health == 0 || winManager.getCountdown() == 0)
			{
				endgame = true;
			}

			if (endgame)
			{
				window->clear(sf::Color(0, 0, 0, 255));
				winManager.initUIText(WIN_WIDTH / 3.5, WIN_HEIGHT / 5, 60);
				winManager.updateText(points, health, endgame);
				winManager.drawText();
			}

			// Restart trigger
			if (restart)
			{
				targetsManager.setHealth(PLAYER_HEALTH);
				targetsManager.setPoints(0);

				winManager.setCountdown(COUNTDOWN);
				winManager.initUIText();

				endgame = false;
				restart = false;

				// Reset the clock
				TimeManager::clockCountdown.restart();
				TimeManager::clockTargets.restart();
			}
		}

		// Displaying the window
		winManager.displayWindow();
	}

	std::cout << "Total Points: " << points << "\n";

	return 0;
}