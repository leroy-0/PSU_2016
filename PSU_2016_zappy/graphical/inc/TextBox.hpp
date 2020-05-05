//
// TextBox.hpp for TextBox in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 15:15:24 2017 leroy_0
// Last update Mon Jun 26 15:15:24 2017 leroy_0
//

#ifndef __TEXTBOX_HPP__
#define __TEXTBOX_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "typedef.hpp"

namespace Zappy
{
	class TextBox : public sf::Text
	{
	public:
		TextBox(const std::string & name, int size, float backgroundX, float backgroundY);
		virtual ~TextBox();
	public:
		void 				addBackground(const std::string & filename);
		void				setContainerPosition(const sf::Vector2f pos);

	public:
		sf::Sprite	 		*getBackground() const;
		sf::Vector2f 		getSize() const;

	private:
		sf::Sprite 			*_background;
		sf::Texture 		*_texture;
	};
};
#endif	/* __TEXTBOX_HPP__ */
