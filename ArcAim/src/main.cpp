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
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "ArcAim", sf::Style::Close);

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

	TimeManager timeM;

	char gameStatus = 0;
	float health = 0.f;
	short points = 0;
	bool endgame = false;
	bool start = false;
	bool options = false;
	bool exit = false;
	bool info = false;
	bool vsync = false;
	bool reset = false;
	bool restart = false;
	bool missSpriteActive = true;
	float healthReset = PLAYER_HEALTH;
	float spawnTimerReset = TARGET_SPAWN_TIMER;
	float yFallingVelReset = Y_FALLING_VELOCITY;

	// Icon in the window bar
	auto image = sf::Image{};
	if (!image.loadFromFile("res/Images/Target.png"))
	{
		std::cout << "ERROR: could not load the image\n";
	}
	window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	previous_time = std::chrono::steady_clock::now();

	winManager.initWindow(window);

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
					std::cout << "Process Killed\n";
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						restart = true;
						start = false;
						info = false;
						std::cout << "Menu\n";
					}

					if (event.key.code == sf::Keyboard::R)
					{
						restart = true;
						std::cout << "Game Restarted\n";
					}

					if (event.key.code == sf::Keyboard::F1) // Idk if it works
					{
						vsync = !vsync;
						window->setVerticalSyncEnabled(vsync);
						if (vsync)
							std::cout << "VSync ON\n";
						else
							std::cout << "VSync OFF\n";
					}

					if (event.key.code == sf::Keyboard::F2)
					{
						window->setFramerateLimit(60);
						std::cout << "Frame limit set to 60\n";
					}

					if (event.key.code == sf::Keyboard::F3)
					{
						window->setFramerateLimit(144);
						std::cout << "Frame limit set to 144\n";
					}

					if (event.key.code == sf::Keyboard::F5)
					{
						missSpriteActive = !missSpriteActive;
						if (missSpriteActive)
							std::cout << "Miss Sprite ON\n";
						else
							std::cout << "Miss Sprite OFF\n";
					}

				default:
					break;
				}
			}

			// Activate miss red cross from default
			targetsManager.setMissActivation(missSpriteActive);

			// Change button color when hovered
			menu.updateBtn(mouseManager.getMousePos());

			// START MENU
			if (!start && !options && !info)
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
				case GAME_INFO:
					info = true;
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
			else if (info)
			{
				window->clear(sf::Color(0, 0, 0, 255));

				//info func from menu
				menu.displayInfo(*window);

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
				// DIFFICULTY
				case DIFFICULTY_EASY: // Default
					healthReset = 110.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 1.f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					// Only for falling mode
					yFallingVelReset = 1.4f;
					targetsManager.setYFallingVel(yFallingVelReset);

					std::cout << "Difficulty set to EASY\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_MEDIUM:
					healthReset = 80.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.65f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					// Only for falling mode
					yFallingVelReset = 1.9f;
					targetsManager.setYFallingVel(yFallingVelReset);

					std::cout << "Difficulty set to MEDIUM\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case DIFFICULTY_HARD:
					healthReset = 70.f;
					targetsManager.setHealth(healthReset);
					spawnTimerReset = 0.5f;
					targetsManager.setSpawnTimer(spawnTimerReset);
					// Only for falling mode
					yFallingVelReset = 2.2f;
					targetsManager.setYFallingVel(yFallingVelReset);

					std::cout << "Difficulty set to HARD\n";
					sf::sleep(sf::milliseconds(100));
					break;

				// CROSSHAIR STYLE
				case CROSS_STYLE1:
					mouseManager.setCrossStyle(CROSS_STYLE1);

					std::cout << "Crosshair STYLE 1 set\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case CROSS_STYLE2:
					mouseManager.setCrossStyle(CROSS_STYLE2);

					std::cout << "Crosshair STYLE 2 set\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case CROSS_STYLE3:
					mouseManager.setCrossStyle(CROSS_STYLE3);

					std::cout << "Crosshair STYLE 3 set\n";
					sf::sleep(sf::milliseconds(100));
					break;

				// MODE
				case REFLEX_ENEMIES:
					targetsManager.setSpawnType(REFLEX_ENEMIES);

					std::cout << "Reflex mode set\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case PRECISION_ENEMIES:
					targetsManager.setSpawnType(PRECISION_ENEMIES);
					std::cout << "Precision mode set\n";
					sf::sleep(sf::milliseconds(100));
					break;
				case FALLING_ENEMIES:
					targetsManager.setSpawnType(FALLING_ENEMIES);

					std::cout << "Falling mode set\n";
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
				info = false;

				window->setMouseCursorVisible(false);

				// Clear the window and set the grey background
				window->clear(sf::Color(18, 18, 18, 255));

				menu.updateText(options);

				mouseManager.updateMousePos(*window);

				// TARGET
				//
				// Managing target's funcs
				if (!endgame)
				{
					targetsManager.updateSpawn();
					targetsManager.eraseOnClick(mouseManager.getMousePos());

				}

				mouseManager.syncPositionWithSprite(*window);

				points = targetsManager.getPoints();
				health = targetsManager.getPlayerHealth();

				// WINDOW
				// 
				// HUD Text updateSpawn and drawTarget + pause mechanism (if -1 change the text to PAUSE)
				winManager.updateClock();
				winManager.updateTimerText();
				winManager.updateText(points, health, endgame);


				// GAME OVER & RESTART
				//
				// Endgame trigger
				if (health <= 0 || winManager.getCountdown() == 0)
				{
					endgame = true;
				}

				if (endgame)
				{
					window->clear(sf::Color(0, 0, 0, 255));
					winManager.initUIText(WIN_WIDTH / 3.5f, WIN_HEIGHT / 5.f, 60);
					winManager.updateText(points, health, endgame);

					targetsManager.eraseAllEnemiesAndCo();
				}

				// Restart trigger
				if (restart)
				{
					// Reset
					targetsManager.reset(healthReset, 0);
					targetsManager.eraseAllEnemiesAndCo();

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
						targetsManager.drawMissSprite(*window);
						targetsManager.drawTarget(*window);

						mouseManager.drawTarget(*window);

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