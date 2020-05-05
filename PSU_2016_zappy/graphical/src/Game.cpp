//
// Game.cpp for Game in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 14:44:55 2017 leroy_0
// Last update Fri Jun 23 14:44:56 2017 leroy_0
//

#include "Game.hpp"

Zappy::Game::Game()
{
	_map = new Zappy::Map();
	_ready = false;
	_clock = new sf::Clock();
	_communication = new Zappy::Communication(_map->getServerFd());
	_sqrtnb = perfectSqrt(TileType::SIZE);
	_delim = std::pow(_sqrtnb, 2);
	_waitForMoves = false;
}

Zappy::Game::~Game()
{
	delete _map;
	delete _clock;
}

bool 						Zappy::Game::connect(const std::string & hostname, int port)
{
	Zappy::Tile 			*tmp;
	int 					x = GAME_POSX / 4;
	int 					y = (WINSIZE_Y / 2) - (((TileType::SIZE) * PADDING_INFO) / 2);

	_ready = _map->connect(hostname, port);
	if (_map->isConnected())
	{
		initMapObjects();
		for (int i = 0; i < TileType::SIZE; ++i)
		{
			tmp = new Zappy::Tile(static_cast<TileType>(i), 1, 0, sf::Vector2f(x, y));
			_blockInfoTiles.push_back(tmp);
			Zappy::TextBox  *info = new Zappy::TextBox(MSGFONT, 20, tmp->getPosition().x + tmp->getSize().x + PADDING_QNT, tmp->getPosition().y + (tmp->getSize().y / 2));
			info->setString("000");
			info->addBackground(MSGBOX);
			_blockInfoTexts.push_back(info);
			y += PADDING_INFO;
		}
	}
	return (_ready);
}

int							Zappy::Game::perfectSqrt(int nb)
{
	float					res;

	res = std::sqrt(nb);
	while (std::fmod(res, 1) != 0)
	{
		nb++;
		res = std::sqrt(nb);
	}
	return (res);
}

bool						Zappy::Game::initMapObjects()
{
	std::vector<std::vector<std::map<TileType, int> *> *> 		mapTiles = _map->getMap();
	float														ratiox = (GAME_WIDTH - _map->getWidth()) / _map->getWidth();
	float 														ratioy = (GAME_HEIGHT - _map->getHeight()) / _map->getHeight();
	float														x = GAME_POSX;
	float 														y = GAME_POSY;
	float														scalex,scaley;
	int															blockx,blocky = 0;
	int															iterator = 0;
	int															iteratorScale = 1;
	Zappy::Tile 												*tile;
	Zappy::Tile 												*ground;

	for (auto yit = mapTiles.begin(); yit < mapTiles.end(); ++yit)
	{
		x = GAME_POSX;
		for (auto xit = (*yit)->begin(); xit < (*yit)->end(); ++xit)
		{
			blockx = x;
			blocky = y;
			iterator = 0;
			std::map<TileType, int> 	*block = (*xit);
			for (int i = 0; i < _delim; ++i)
			{
				ground = new Zappy::Tile(TileType::GROUND, 1, TileType::GROUND, sf::Vector2f(blockx, blocky));
				scalex = (ratiox / _sqrtnb) / ground->getSize().x;
				scaley = (ratioy / _sqrtnb) / ground->getSize().y;
				if (iterator != 0 && (iterator + 1) % static_cast<int>(_sqrtnb) == 0 && blockx + ratiox != x + ratiox)
				{
					iteratorScale = 1;
					while (static_cast<int>(blockx + (scalex * ground->getSize().x)) < static_cast<int>(x + ratiox))
					{
						scalex = ((ratiox + iteratorScale) / _sqrtnb) / ground->getSize().x;
						iteratorScale++;
					}
				}
				if (iterator >= (_delim - _sqrtnb) && ratioy + y != blocky + ratioy)
				{
					iteratorScale = 1;
					while (static_cast<int>(blocky + (scaley * ground->getSize().y)) < static_cast<int>(y + ratioy))
					{
						scaley = ((ratioy + iteratorScale) / _sqrtnb) / ground->getSize().y;
						iteratorScale++;
					}
				}
				ground->setScale(scalex, scaley);
				_mapObjects.push_back(ground);

				if (i < TileType::SIZE)
				{
					tile = new Zappy::Tile(static_cast<TileType>(i), block->at(static_cast<TileType>(i)), static_cast<TileType>(i), sf::Vector2f(blockx, blocky));
					scalex = (ratiox / _sqrtnb) / tile->getSize().x;
					scaley = (ratioy / _sqrtnb) / tile->getSize().y;
					tile->setScale(scalex, scaley);
				}
				else
					tile = new Zappy::Tile(TileType::EMPTY, 0, 0, sf::Vector2f(blockx, blocky));
				_mapObjects.push_back(tile);

				if (iterator != 0 && (iterator + 1) % static_cast<int>(_sqrtnb) == 0)
				{
					blockx = x;
					blocky += (ratioy / _sqrtnb);
				}
				else
					blockx += (ratiox / _sqrtnb);
				iterator++;
			}
			x += ratiox + 1;
		}
		y += ratioy + 1;
	}
	return (true);
}

void						Zappy::Game::newPlayer(std::stringstream & ss)
{
	Zappy::Tile 			*player;
	std::string 			team;
	int 					playerx,playery = 0;
	int 					nb,orientation = 0;

	ss >> nb;
	ss >> playerx;
	ss >> playery;
	auto it = _mapObjects.begin();
	for (int i = 0; i < _map->getHeight(); ++i)
	{
		for (int j = 0; j < _map->getWidth(); ++j)
		{
			if (j == playerx && i == playery)
			{
				player = new Zappy::Tile(TileType::PLAYER, 1, nb, (*it)->getPosition());
				ss >> orientation;
				ss >> nb;
				ss >> team;
				player->setLevel(nb);
				player->setTeam(team);
				player->updateSkinTeam(_map->getTeamNames());
				player->animate(static_cast<e_dir>(orientation));
				player->setScale(player->getScale().x / 2, player->getScale().y / 2);
				_mapPlayers.push_back(player);
				break;
			}
			for (int k = 0; k < getSizeBlock(); ++k)
			{
				it++;
				it++;
			}
		}
	}
}

void						Zappy::Game::deletePlayer(std::stringstream & ss)
{
	int 					id;

	ss >> id;
	for (auto it = _mapPlayers.begin(); it < _mapPlayers.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			_mapPlayers.erase(it);
			break;
		}
	}
}

void						Zappy::Game::movePlayer(std::stringstream & ss)
{
	int 					id;
	int 					x,y = 0;
	sf::Vector2f 			pos;
	sf::Vector2f 			pos2;

	ss >> id;
	ss >> x;
	ss >> y;
	for (auto it = _mapPlayers.begin(); it < _mapPlayers.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			pos = getMapPosition(sf::Vector2f((*it)->getPosition().x, (*it)->getPosition().y));
			if (pos.x > (x + 2) || pos.y > (y + 2)
				|| (pos.x + 2) < x || (pos.y + 2) < y)
				(*it)->set_position(getRealPosition(sf::Vector2f(x, y)));
			else
				(*it)->goTo(getRealPosition(sf::Vector2f(x, y)));
			break;
		}
	}
	_waitForMoves = true;
}

void 						Zappy::Game::manageRessource(std::stringstream & ss)
{
	sf::Vector2f			pos;
	int 					nb;

	ss >> pos.x;
	ss >> pos.y;
	auto it = _mapObjects.begin();
	for (int i = 0; i < _map->getHeight(); ++i)
	{
		for (int j = 0; j < _map->getWidth(); ++j)
		{
			for (int i = 0; i < TileType::SIZE; ++i)
			{
				it++;
				if (j == pos.x && i == pos.y)
				{
					ss >> nb;
					(*it)->setQuantity(nb);
				}
				it++;
			}
			if (j == pos.x && i == pos.y)
				break;
		}
	}
}

void						Zappy::Game::manageBroadcast(std::stringstream & ss)
{
	std::size_t 			found;
	std::string 			tmp;
	std::string 			msg;
	int 					id;

	ss >> id;
	for (auto it = _mapPlayers.begin(); it < _mapPlayers.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			while (ss >> tmp)
				msg += tmp + std::string(" ");
			if (!msg.empty() && (found = msg.find(',')) != std::string::npos
				&& found + 1 < msg.size())
				msg.replace(0, found + 1, "");
			(*it)->setBroadcast(msg);
		}
	}
}

void 						Zappy::Game::manageEvolution(std::stringstream & ss)
{
	int 					id;

	ss >> id;
	for (auto it = _mapPlayers.begin(); it < _mapPlayers.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			(*it)->setLevel((*it)->getLevel() + 1);
			break;
		}
	}
}

void						Zappy::Game::analyseCmd(const std::string & line)
{
	std::stringstream		ss;
	std::string 			cmd;

	ss << line;
	ss >> cmd;
	if (cmd == "pnw")
		newPlayer(ss);
	if (cmd == "pdi")
		deletePlayer(ss);
	if (cmd == "ppo")
		movePlayer(ss);
	if (cmd == "bct")
		manageRessource(ss);
	if (cmd == "pbc")
		manageBroadcast(ss);
	if (cmd == "plv")
		manageEvolution(ss);
}

bool						Zappy::Game::managePlayerMoves()
{
	bool					ok = false;

	for (auto it = _mapPlayers.begin(); it < _mapPlayers.end(); ++it)
	{
		if (!ok)
			ok = (*it)->goTo((*it)->getPosition());
		else
			(*it)->goTo((*it)->getPosition());
	}
	return (ok);
}

void 						Zappy::Game::setBlockInfo(sf::Vector2f pos)
{
	bool 					begin = false;

	auto it = _mapObjects.begin();
	auto info = _blockInfoTiles.begin();
	auto text = _blockInfoTexts.begin();
	for (int i = 0; i < _map->getHeight(); ++i)
	{
		for (int j = 0; j < _map->getWidth(); ++j)
		{
			for (int k = 0; k < _delim; ++k)
			{
				if (!begin && (*it)->getPosition().x >= pos.x && (*it)->getPosition().y >= pos.y)
				{
					begin = true;
					while (k > 0)
					{
						k--;
						it--;
						it--;
					}
				}
				it++;
				if (begin && k < TileType::SIZE && it < _blockInfoTiles.end() && text < _blockInfoTexts.end())
				{
					(*info)->setQuantity((*it)->getQuantity());
					(*text)->setString(std::to_string((*info)->getQuantity()));
					info++;
					text++;
				}
				it++;
			}
			if (begin)
				break;
		}
	}
}

void						Zappy::Game::manageMouse(const sf::Vector2i mousePos)
{
	if (mousePos.x > GAME_POSX && mousePos.x < GAME_POSX + GAME_WIDTH
		&& mousePos.y > GAME_POSY && mousePos.y < GAME_POSY + GAME_HEIGHT)
	{
		setBlockInfo(getRealPosition(getMapPosition(sf::Vector2f(mousePos.x, mousePos.y))));
	}
	else
	{
		_blockInfo.clear();
	}
}

bool						Zappy::Game::run()
{
	std::string				msg;

	if (!_waitForMoves)
	{
		msg = _communication->recvMessage(_map->getServerFd());
		analyseCmd(msg);
	}
	else
	{
		if (!managePlayerMoves())
		{
			_waitForMoves = false;
		}
	}
	return (true);
}

sf::Vector2f 					Zappy::Game::getRealPosition(const sf::Vector2f & new_pos)
{
	sf::Vector2f 				pos;
	float 						ratiox = (GAME_WIDTH - _map->getWidth()) / _map->getWidth();
	float 						ratioy = (GAME_HEIGHT - _map->getHeight()) / _map->getHeight();

	pos.x = (new_pos.x * ratiox) + GAME_POSX;
	pos.y = (new_pos.y * ratioy) + GAME_POSY;
	return (pos);
}

sf::Vector2f 				Zappy::Game::getMapPosition(const sf::Vector2f & pos)
{
	float 					ratiox = (GAME_WIDTH - _map->getWidth()) / _map->getWidth();
	float 					ratioy = (GAME_HEIGHT - _map->getHeight()) / _map->getHeight();

	for (float i = 0; i < _map->getHeight(); ++i)
	{
		for (float j = 0; j < _map->getWidth(); ++j)
		{
			if (pos.x >= ((j * ratiox) + GAME_POSX) && pos.x < (((j + 1.0f) * ratiox) + GAME_POSX)
				&& pos.y >= ((i * ratioy) + GAME_POSY) && pos.y < (((i + 1.0f) * ratioy)) + GAME_POSY)
			{
				return (sf::Vector2f(j, i));
			}
		}
	}
	return (sf::Vector2f(0, 0));
}

std::vector<Zappy::TextBox *> 	Zappy::Game::getBlockInfoTexts() const
{
	return (_blockInfoTexts);
}

std::vector<Zappy::Tile *> 		Zappy::Game::getBlockInfoTiles() const
{
	return (_blockInfoTiles);
}

std::vector<int>				Zappy::Game::getBlockInfo() const
{
	return (_blockInfo);
}

bool 						Zappy::Game::isReady() const
{
	return (_ready);
}

bool 						Zappy::Game::isConnected() const
{
	return (_map->isConnected());
}

int							Zappy::Game::getSizeBlockLine() const
{
	return (_sqrtnb);
}

int 						Zappy::Game::getSizeBlock() const
{
	return (_delim);
}

std::vector<Zappy::Tile *>	Zappy::Game::getMapObjects() const
{
	return (_mapObjects);
}

std::vector<Zappy::Tile *>	Zappy::Game::getMapPlayers() const
{
	return (_mapPlayers);
}