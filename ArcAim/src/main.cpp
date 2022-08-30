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
	float health = 0.f;
	short points = 0;
	bool endgame = false;
	bool start = false;
	bool options = false;
	bool exit = false;
	bool vsync = false;
	bool reset = false;
	bool restart = false;
	float healthReset = PLAYER_HEALTH;
	float spawnTimerReset = TARGET_SPAWN_TIMER;

	winManager.initWindow(window);

	previous_time = std::chrono::steady_clock::now();

	targetsManager.setSpawnType(REFLEX_ENEMIES);

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
						std::cout << "Reset" << std::endl;
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

			// Reset everything with Esc button
			if (reset)
			{
				reset = false;
				start = false;
				restart = true;

				// Reset
				targetsManager.reset(healthReset, 0);
				targetsManager.eraseAllEnemies();

				winManager.setCountdown(20);

				// Sync the clock
				TimeManager::clockCountdown.restart();
				TimeManager::clockTargets.restart();
			}

			// START MENU
			if (!start && !options)
			{
				window->setMouseCursorVisible(true);

				menu.displayMenu(window, *window, options);

				// Start menu buttons
				switch (menu.activateStartBtn(mouseManager.getMousePos()))
				{
				case GAME_START:
					start = true;
					sf::sleep(sf::milliseconds(100));
					break;
				case GAME_OPTIONS:
					options = true;
					sf::sleep(sf::milliseconds(100));
					break;
				case GAME_EXIT:
					exit = true;
					sf::sleep(sf::milliseconds(100));
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
				menu.displayMenu(window, *window, options);
				menu.updateText(options);

				// Options buttons
				switch (menu.activateOptionBtn(mouseManager.getMousePos()))
				{
				case DIFFICULTY_EASY:
					healthReset = 120.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 1.1f;
					targetsManager.setSpawnTimer(spawnTimerReset);

					std::cout << "Difficulty set to EASY" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_MEDIUM:
					healthReset = 80.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.65f;
					targetsManager.setSpawnTimer(spawnTimerReset);

					std::cout << "Difficulty set to MEDIUM" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_HARD:
					healthReset = 70.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.5f;
					targetsManager.setSpawnTimer(spawnTimerReset);

					std::cout << "Difficulty set to HARD" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case CROSS_STYLE1:
					mouseManager.setCrossStyle(CROSS_STYLE1);

					std::cout << "Crosshair STYLE 1 set" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case CROSS_STYLE2:
					mouseManager.setCrossStyle(CROSS_STYLE2);

					std::cout << "Crosshair STYLE 2 set" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case CROSS_STYLE3:
					mouseManager.setCrossStyle(CROSS_STYLE3);

					std::cout << "Crosshair STYLE 3 set" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case REFLEX_ENEMIES:
					targetsManager.setSpawnType(REFLEX_ENEMIES);

					std::cout << "Reflex mode set" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case FALLING_ENEMIES:
					targetsManager.setSpawnType(FALLING_ENEMIES);

					std::cout << "Falling mode set" << std::endl;
					sf::sleep(sf::milliseconds(100));
					break;
				case GAME_GOBACK:
					options = false;

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
				
				menu.updateText(options);

				mouseManager.updateMousePos(*window);

				// TARGET
				//
				// Managing target's funcs
				//targetsManager.setSpawnType(REFLEX_ENEMIES);
				if (!endgame)
				{
					targetsManager.update();
					targetsManager.eraseOnClick(mouseManager.getMousePos());
				}

				mouseManager.syncPositionWithSprite(*window);

				points = targetsManager.getPoints();
				health = targetsManager.getPlayerHealth();

				// WINDOW
				// 
				// HUD Text update and draw + pause mechanism (if -1 change the text to PAUSE)
				winManager.updateClock();
				winManager.updateTimerText();
				winManager.updateText(points, health, endgame);
				
				
				// GAME OVER & RESTART
				//
				// Endgame trigger
				if (health == 0 || winManager.getCountdown() == 0)
				{
					endgame = true; // not workin with falling enemies
				}

				if (endgame)
				{
					window->clear(sf::Color(0, 0, 0, 255));
					winManager.initUIText(WIN_WIDTH / 3.5f, WIN_HEIGHT / 5.f, 60);
					winManager.updateText(points, health, endgame);
				}

				// Restart trigger
				if (restart)
				{
					// Reset
					targetsManager.reset(healthReset, 0);
					targetsManager.eraseAllEnemies();

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
					if (!endgame)
					{
						targetsManager.draw(*window);
						mouseManager.draw(*window);

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