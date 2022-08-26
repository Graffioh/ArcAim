#include <iostream>
#include <chrono>

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

	// Framerate
	window->setFramerateLimit(240);

	// For framerate indipendent gameplay (thanks to Kofybrek's source codes)
	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	sf::Event event;

	WindowManager winManager;

	TargetsManager targetsManager;

	MouseManager mouseManager;

	Menu menu;

	TimeManager time;

	char gameStatus = 0;
	unsigned short health = 0;
	short points = 0;
	bool endgame = false;
	bool pause = false;
	bool start = false;
	bool options = false;
	bool exit = false;
	bool vsync = false;
	bool reset = false;
	bool restart = false;

	unsigned short healthReset = PLAYER_HEALTH;
	float spawnTimerReset = TARGET_SPAWN_TIMER;

	winManager.initWindow(window);

	previous_time = std::chrono::steady_clock::now();

	// Game loop
	while (window->isOpen())
	{
		// Frames and others calculations to make the game framerate indipendent
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

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
						reset = true;
						std::cout << "Reset" << std::endl; // NEED TO RESET COUNTDOWN POINTS AND HEALTH WHEN PRESSED
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

			if (reset)
			{
				reset = false;
				start = false;

				// Reset
				targetsManager.reset(healthReset, 0);

				winManager.setCountdown(20);

				// Sync the clock
				TimeManager::clockCountdown.restart();
				TimeManager::clockTargets.restart();
			}

			// START MENU
			if (!start && !options)
			{
				window->setMouseCursorVisible(true);

				menu.initStartBtn();
				menu.displayMenu(*window, pause, options);
				menu.updateText(pause, options);

				// Start menu buttons
				switch (menu.activateStartBtn(mouseManager.getMousePos()))
				{
				case GAME_START:
					start = true;
					break;
				case GAME_OPTIONS:
					options = true;
					break;
				case GAME_EXIT:
					exit = true;
					break;
				default:
					break;
				}

				if (exit)
				{
					window->close();
				}

				mouseManager.updateMousePos(*window);

				// Sync the clock
				TimeManager::clockCountdown.restart();
				TimeManager::clockTargets.restart();
			}
			else if (options)
			{
				menu.initOptionsBtn();
				menu.displayMenu(*window, pause, options);
				menu.updateText(pause, options);

				// Options buttons
				switch (menu.activateOptionBtn(mouseManager.getMousePos()))
				{
				case GAME_GOBACK:
					options = false;
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_EASY:
					healthReset = 120;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 1.2f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					std::cout << "Difficulty set to EASY" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_MEDIUM:
					//targetsManager.setHealth(100);
					//targetsManager.setSpawnTimer(0.7f);

					healthReset = 100;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.7f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					std::cout << "Difficulty set to MEDIUM" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_HARD:
					//targetsManager.setHealth(70);
					//targetsManager.setSpawnTimer(0.5f);

					healthReset = 70;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.5f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					std::cout << "Difficulty set to HARD" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				default:
					break;
				}

				mouseManager.updateMousePos(*window);

				// Sync the clock
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
				}

				mouseManager.syncPosition(*window);

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

					menu.updateText(pause, options);

					TimeManager::clockTargets.restart();

					if (menu.activateStartBtn(mouseManager.getMousePos()) == GAME_RESUME)
					{
						pause = !pause;
					}
				}

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
				}

				// Restart trigger
				if (restart)
				{
					// Reset
					targetsManager.reset(healthReset, 0);

					winManager.setCountdown(20);
					winManager.initUIText();

					endgame = false;
					restart = false;

					// Sync the clock
					TimeManager::clockCountdown.restart();
					TimeManager::clockTargets.restart();
				}

				// Drawing here
				if (FRAME_DURATION > lag)
				{
					if (!pause && !endgame)
					{
						targetsManager.draw(*window);
						mouseManager.draw(*window);
					}

					if (pause)
						menu.displayMenu(*window, pause, options);

					if (!endgame)
					{
						winManager.drawText();
						winManager.drawTimerText();
					}

					winManager.drawText();
				}
			}
		}
		// Displaying the window
		if (FRAME_DURATION > lag)
			winManager.displayWindow();
	}

	std::cout << "Total Points: " << points << "\n";

	return 0;
}