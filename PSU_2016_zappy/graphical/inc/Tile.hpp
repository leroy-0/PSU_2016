//
// Tile.hpp for Tile in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 14:09:30 2017 leroy_0
// Last update Mon Jun 26 14:09:31 2017 leroy_0
//

#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <SFML/Graphics.hpp>

#include "TextBox.hpp"
#include "zappy_player.h"
#include "typedef.hpp"

namespace Zappy
{
	class Tile : public sf::Sprite
	{
	public:
		Tile(const TileType & type, int nb, int id, const sf::Vector2f pos);
		virtual ~Tile();

	public:
		void				animate(e_dir dir);
		bool				goTo(sf::Vector2f newpos);

	public:
		sf::Vector2u		getSize() const;
		TileType			getType() const;
		int 				getQuantity() const;
		int 				getId() const;
		int					getLevel() const;
		std::string 		getTeam() const;
		Zappy::TextBox 		*getBroadcast() const;
		void 				updateSkinTeam(const std::vector<std::string> & teamNames);

	public:
		void				setLevel(int lvl);
		void				setTeam(std::string & name);
		void	 			setQuantity(int nb);
		void				setBroadcast(const std::string & msg);
		void				set_position(const sf::Vector2f & pos);

	private:
		sf::Texture     					*_texture;
		sf::Vector2f						_newpos;
		std::map<TileType, std::string *>   _textureNames;
		TileType							_type;
		int									_nb;
		unsigned int						_x;
		unsigned int						_y;

	private:
		int									_animate;
		int									_id;
		int 								_lvl;
		std::string							_teamname;
		Zappy::TextBox 						*_textbox;
	};
};

#endif	//__TILE_HPP__