#pragma once
#include <string>

#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;
	sf::Color m_color;

	bool m_mouseHeld;

public:
	Button(sf::Color btnColor, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor);
	~Button();

	void draw(sf::RenderTarget* target);

	sf::FloatRect getBounds();
};
	

	