#pragma once
#include <iostream>
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

	float m_xBtnPos;
	float m_yBtnPos;

	sf::Texture m_customTexture;
	sf::Sprite m_customSprite;

public:
	Button(sf::Color btnColorIdle, sf::Color btnColorHovered, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor);
	// Custom button
	Button(sf::Color btnColorIdle, sf::Color btnColorHovered, float width, float height, float x, float y, std::string imgPath, bool isBackArrow);
	~Button();

	void updateBtnColorWhenHovered(sf::Vector2f mousePos);
	void updateBtnOutlineWhenClicked(float thickness);

	void drawBtn(sf::RenderTarget* target);

	sf::FloatRect getBounds();

	void setUpDownBtnYPos(float y);
};
	

	