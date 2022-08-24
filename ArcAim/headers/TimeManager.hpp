#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

class TimeManager
{
private:

public:
	static sf::Clock clockGame;
	static sf::Clock clockCountdown;
	static sf::Clock clockTargets;

	TimeManager();
};

