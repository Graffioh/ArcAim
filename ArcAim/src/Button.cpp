#include "../headers//Button.hpp"

Button::Button(sf::Color btnColorIdle, sf::Color btnColorHovered, float width, float height, float x, float y, sf::Font* font, std::string string, sf::Color txtColor)
	:m_mouseHeld(false), m_colorOutline(sf::Color::Blue)
{
	m_shape.setFillColor(btnColorIdle);
	m_shape.setOutlineColor(m_colorOutline);
	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setPosition(x, y);
	m_xBtnPos = x;
	m_yBtnPos = y;

	m_font = font;
	m_text.setFont(*font);
	m_text.setString(string);
	m_text.setFillColor(txtColor);
	m_text.setCharacterSize(22);
	m_text.setPosition((int)((m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2.f) - (m_text.getGlobalBounds().width / 2.f)) + 1,
		(int)((m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2.f) - (m_text.getGlobalBounds().height / 1.3f)));

	m_colorIdle = btnColorIdle;
	m_colorHovered = btnColorHovered;
}

Button::~Button()
{
}

void Button::updateBtnColorHovered(sf::Vector2f mousePos)
{
	if (m_shape.getGlobalBounds().contains(mousePos))
		m_shape.setFillColor(m_colorHovered);
	else
		m_shape.setFillColor(m_colorIdle);
}

void Button::updateBtnOutlineWhenClicked(float thickness)
{
	m_shape.setOutlineThickness(thickness);
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

void Button::setUpDownBtnYPos(float y)
{
	m_shape.setPosition(m_xBtnPos, m_yBtnPos += y);
	m_text.setPosition((int)((m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2.f) - (m_text.getGlobalBounds().width / 2.f)) + 1,
		(int)((m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2.f) - (m_text.getGlobalBounds().height / 1.3f)));
}

