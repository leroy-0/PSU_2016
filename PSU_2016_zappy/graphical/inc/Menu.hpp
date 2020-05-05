//
// Menu.hpp for Menu in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 15:11:07 2017 leroy_0
// Last update Mon Jun 26 15:11:08 2017 leroy_0
//

#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "TextBox.hpp"
#include "typedef.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace Zappy
{
	class Menu : public sf::Sprite
	{
	public:
		Menu(float x, float y);
		virtual ~Menu();
	public:
		sf::Sprite						*getCursor() const;
		std::vector<Zappy::TextBox *>	getMenuChoices() const;
		void							setCursorPos(sf::Keyboard::Key);
		void							setMenuType(MenuType *_type);

	private:
		sf::Sprite 						*_cursor;
		std::vector<Zappy::TextBox *>	_menuChoices;
		unsigned int 					_choice;
	};
};

#endif	/* __MENU_HPP__ */