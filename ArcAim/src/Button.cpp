#include "../headers//Button.hpp"

Button::Button(sf::Color btnColorIdle, sf::Color updateBtnColor, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor)
	:m_mouseHeld(false)
{
	m_shape.setFillColor(btnColorIdle);
	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setPosition(x, y);

	m_font = font;
	m_text.setFont(*font);
	m_text.setString(string);
	m_text.setFillColor(txtColor);
	m_text.setCharacterSize(25);
	m_text.setPosition((int)((m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2.f) - (m_text.getGlobalBounds().width / 2.f)) + 1,
		(int)((m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2.f) - (m_text.getGlobalBounds().height / 1.3f)));

	m_colorIdle = btnColorIdle;
	m_colorHovered = updateBtnColor;
}

Button::~Button()
{
}

void Button::updateBtnColor(sf::Vector2f mousePos)
{
	if(m_shape.getGlobalBounds().contains(mousePos))
		m_shape.setFillColor(m_colorHovered);
	else
		m_shape.setFillColor(m_colorIdle);
}

void Button::drawBtn(sf::RenderTarget* target)
{
	target->draw(m_shape);
	target->draw(m_text);
}

sf::FloatRect Button::getBounds()
{
	return m_shape.getGlobalBounds();
}

