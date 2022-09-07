#pragma once
#include <string>

#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_colorIdle;
	sf::Color m_colorHovered;

	bool m_mouseHeld;

public:
	Button(sf::Color btnColorIdle, sf::Color updateBtnColor, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor);
	~Button();

	void updateBtnColor(sf::Vector2f mousePos);

	void drawBtn(sf::RenderTarget* target);

	sf::FloatRect getBounds();
};
	

	