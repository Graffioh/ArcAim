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
	sf::Color m_colorOutline;

	bool m_mouseHeld;

public:
	Button(sf::Color btnColorIdle, sf::Color btnColorHovered, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor);
	~Button();

	void updateBtnColorHovered(sf::Vector2f mousePos);
	void updateBtnOutlineWhenClicked(float thickness);

	void drawBtn(sf::RenderTarget* target);

	sf::FloatRect getBounds();
};
	

	