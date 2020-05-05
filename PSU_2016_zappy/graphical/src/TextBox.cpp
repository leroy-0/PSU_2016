//
// TextBox.cpp for TextBox in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 15:15:16 2017 leroy_0
// Last update Mon Jun 26 15:15:16 2017 leroy_0
//

#include "TextBox.hpp"

Zappy::TextBox::TextBox(const std::string & filename, int size, float backgroundX, float backgroundY)
{
	sf::Font                *font = new sf::Font();

	font->loadFromFile(filename);

	_background = NULL;
	setFont(*font);
	setString("TextBox");
	setCharacterSize(size);
	setStyle(sf::Text::Bold);
	setFillColor(sf::Color::White);
	setPosition(backgroundX, backgroundY);
}

Zappy::TextBox::~TextBox()
{
	delete _texture;
	delete _background;
}

void 				Zappy::TextBox::addBackground(const std::string & filename)
{
	setFillColor(sf::Color::Black);
	setPosition(getPosition().x - PADDING_BOX, getPosition().y);

	_background = new sf::Sprite();
	_texture = new sf::Texture();
	_texture->loadFromFile(filename);
	_background->setTexture(*_texture);
	_background->setScale(getLocalBounds().width / (_texture->getSize().x - (PADDING_BOX * 2.5)), getLocalBounds().height / (_texture->getSize().y / 2));
	_background->setPosition(getPosition().x - (PADDING_BOX * _background->getScale().x), getPosition().y - (getLocalBounds().height / 4));
}

void				Zappy::TextBox::setContainerPosition(const sf::Vector2f pos)
{
	setPosition(pos);
	if (_background)
		_background->setPosition(pos);
}

sf::Sprite 			*Zappy::TextBox::getBackground() const
{
	return (_background);
}

sf::Vector2f 		Zappy::TextBox::getSize() const
{
	if (_background)
	{
		return (sf::Vector2f(_texture->getSize().x * _background->getScale().x, _texture->getSize().y * _background->getScale().y));
	}
	return (sf::Vector2f(1, 1));
}