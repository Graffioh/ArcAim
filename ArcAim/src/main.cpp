
#include "../headers/Game.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "ArcAim", sf::Style::Close);

	Game game;

	game.run(window);

	return 0;
}