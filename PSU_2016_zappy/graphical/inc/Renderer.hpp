//
// Renderer.hpp for Renderer in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 14:29:39 2017 leroy_0
// Last update Fri Jun 23 14:29:40 2017 leroy_0
//

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "Menu.hpp"
#include "Music.hpp"
#include "Game.hpp"
#include "TextBox.hpp"
#include "typedef.hpp"

namespace Zappy
{
	class Renderer
	{
	public:
		Renderer(const unsigned int width, const unsigned int height);
		virtual ~Renderer();
	public:
		void				run();
		void 				manageMenu();
		void				manageMain();
		void    			manageConnection();
		void				manageGame();
		void				manageEvents();
		void				display();
		void        		displayTile(const std::vector<TileType> map, unsigned int x, unsigned int y);

	private:
		unsigned int 		_width;
		unsigned int 		_height;
		MenuType			_type;
		bool 				_firstBox;

	private:
		Zappy::Game					*_game;
		Zappy::Menu					*_menu;
		Zappy::Music				*_menuAmbient;
		Zappy::Music 				*_gameAmbient;
		Zappy::Music 				*_bonusSound;
		Zappy::TextBox				*_textbox;
		Zappy::Tile					*_background;
		Zappy::Tile 				*_logo;
		Zappy::Tile 				*_connect;
		Zappy::TextBox 				*_ipBox;
		Zappy::TextBox 				*_portBox;
		std::string 				_connectString;
		sf::RenderWindow			*_window;
		sf::Event					*_event;
	};
};

#endif	//__RENDERER_HPP__