//
// Game.hpp for Game in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 14:45:03 2017 leroy_0
// Last update Fri Jun 23 14:45:04 2017 leroy_0
//

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Map.hpp"
#include "Tile.hpp"
#include "typedef.hpp"

#include <cmath>
#include <iostream>
#include <string>

namespace Zappy
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

	public:
		bool						run();
		bool						initMapObjects();
		int							perfectSqrt(int nb);
		void						manageMouse(const sf::Vector2i mousePos);
		void						analyseCmd(const std::string & cmd);
		bool						managePlayerMoves();
		bool 						connect(const std::string & hostname, int port);
		void 						setBlockInfo(sf::Vector2f pos);

	public:
		std::vector<Zappy::Tile *>		getMapObjects() const;
		std::vector<Zappy::Tile *>		getMapPlayers() const;
		int								getSizeBlock() const;
		int 							getSizeBlockLine() const;
		sf::Vector2f 					getRealPosition(const sf::Vector2f & new_pos);
		std::vector<int> 				getBlockInfo() const;
		sf::Vector2f 					getMapPosition(const sf::Vector2f & pos);
		bool 							isReady() const;
		bool 							isConnected() const;
		std::vector<Zappy::Tile *> 		getBlockInfoTiles() const;
		std::vector<Zappy::TextBox *> 	getBlockInfoTexts() const;

	//PTR SUR FNC
	public:
		void						newPlayer(std::stringstream & ss);
		void						deletePlayer(std::stringstream & ss);
		void						movePlayer(std::stringstream & ss);
		void						manageBroadcast(std::stringstream & ss);
		void 						manageRessource(std::stringstream & ss);
		void 						manageEvolution(std::stringstream & ss);

	private:
		bool									_waitForMoves;
		float									_sqrtnb;
		int										_delim;
		bool 									_ready;

	private:
		std::vector<Zappy::Tile *>				_mapObjects;
		std::vector<Zappy::Tile *>				_mapPlayers;
		std::vector<int>						_blockInfo;
		std::vector<Zappy::Tile *> 				_blockInfoTiles;
		std::vector<Zappy::TextBox *>			_blockInfoTexts;
		Zappy::Communication					*_communication;
		Zappy::Map								*_map;
		sf::Clock								*_clock;
	};
};

#endif 	// __GAME_HPP__