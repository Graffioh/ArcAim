#pragma once

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

class Game
{
private:

public:
	void run(sf::RenderWindow* window);
};

