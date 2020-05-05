//
// Menu.cpp for Menu in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 15:11:16 2017 leroy_0
// Last update Mon Jun 26 15:11:16 2017 leroy_0
//

#include "Menu.hpp"

Zappy::Menu::Menu(float backgroundX, float backgroundY)
{
	sf::Texture 	*menu = new sf::Texture();
	sf::Texture 	*cursor_texture = new sf::Texture();
	Zappy::TextBox	*start;
	Zappy::TextBox	*quit;

	_cursor = new sf::Sprite();
	menu->loadFromFile(MENU);
	setTexture(*menu);
	setScale(backgroundX / menu->getSize().x , backgroundY / menu->getSize().y);
	setPosition(sf::Vector2f(0, 0));
	cursor_texture->loadFromFile(CURSOR);
	_cursor->setTexture(*cursor_texture);
	_cursor->setPosition(sf::Vector2f((backgroundX / 2) - 200, backgroundY / 2 - CURSORMOVE / 2));
	start = new Zappy::TextBox(MSGFONT, 40, _cursor->getPosition().x + cursor_texture->getSize().x + CURSOR_PADDING, _cursor->getPosition().y);
	start->setString("Start");
	quit = new Zappy::TextBox(MSGFONT, 40, _cursor->getPosition().x + cursor_texture->getSize().x + CURSOR_PADDING, _cursor->getPosition().y + CURSORMOVE);
	quit->setString("Quit");
	_menuChoices.push_back(start);
	_menuChoices.push_back(quit);
	_choice = 0;
}

Zappy::Menu::~Menu()
{
	delete _cursor;
	_menuChoices.clear();
}

sf::Sprite						*Zappy::Menu::getCursor() const
{
	return (_cursor);
}

std::vector<Zappy::TextBox *>	Zappy::Menu::getMenuChoices() const
{
	return (_menuChoices);
}

void							Zappy::Menu::setMenuType(MenuType *type)
{
	if (_choice == 0)
		*type = MenuType::CONNECTION;
	else if (_choice == 1)
		*type = MenuType::EXIT;
}

void							Zappy::Menu::setCursorPos(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Up && _choice > 0)
	{
		_choice--;
		_cursor->setPosition(sf::Vector2f(_cursor->getPosition().x, _cursor->getPosition().y - CURSORMOVE));
	}
	else if (key == sf::Keyboard::Down && _choice < _menuChoices.size() - 1)
	{
		_choice++;
		_cursor->setPosition(sf::Vector2f(_cursor->getPosition().x, _cursor->getPosition().y + CURSORMOVE));
	}
}