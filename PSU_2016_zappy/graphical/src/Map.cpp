//
// Map.cpp for Map in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 13:40:55 2017 leroy_0
// Last update Mon Jun 26 13:40:57 2017 leroy_0
//

#include "Map.hpp"

Zappy::Map::Map()
{
	_connected = false;
	_width = 0;
	_height = 0;
}

Zappy::Map::~Map()
{

}

bool 										Zappy::Map::connect(const std::string & hostname, int port)
{
	_fd = Zappy::Network::initServerConnexion(hostname.c_str(), port);
	_communication = new Zappy::Communication(_fd);
	if (!_communication->initConnexion(std::string("GRAPHIC")))
	{
		_connected = false;
		return (false);
	}
	_connected = true;
	if (initSettings() && initMap() && initPlayers())
		return (true);
	return (false);
}

bool 										Zappy::Map::isConnected() const
{
	return (_connected);
}

bool										Zappy::Map::initSettings()
{
	std::string 							msg;
	std::stringstream						ss;
	std::string 							cmd;

	msg = _communication->recvMessage(_fd);
	ss << msg;
	ss >> cmd;
	if (cmd == "msz")
	{
		ss >> _width;
		ss >> _height;
	}
	else
	{
		std::cerr << "Error initializing map" << std::endl;
		return (false);
	}
	ss.str("");
	ss.clear();
	msg = _communication->recvMessage(_fd);
	ss << msg;
	if (cmd == "sgt")
		ss >> _frequency;
	ss.str("");
	ss.clear();
	return (true);
}

bool										Zappy::Map::initMap()
{
	std::map<TileType, int> 				*block;
	std::vector<std::map<TileType, int> *> 	*line;
	std::string 							msg;
	std::stringstream						ss;
	std::string 							cmd;
	int 									nb = 0;

	for (int y = 0; y < _height; ++y)
	{
		line = new std::vector<std::map<TileType, int> *>;
		for (int x = 0; x < _width; ++x)
		{
			block = new std::map<TileType, int>;
			ss << _communication->recvMessage(_fd);
			ss >> cmd;
			if (cmd != "bct")
			{
				std::cerr << "Error parsing map" << std::endl;
				return (false);
			}
			ss >> nb;
			ss >> nb;
			for (int k = 0; k < TileType::SIZE; ++k)
			{
				ss >> nb;
				block->insert(std::pair<TileType, int>(static_cast<TileType>(k), nb));
			}
			ss.str("");
			ss.clear();
			line->push_back(block);
		}
		_map.push_back(line);
	}
	return (true);
}

bool										Zappy::Map::initPlayers()
{
	std::string 							msg;
	std::stringstream						ss;
	std::string 							cmd;

	_communication->sendMessage(_fd, "msz");
	while (cmd != "msz")
	{
		msg = _communication->recvMessage(_fd);
		ss << msg;
		ss >> cmd;
		if (cmd == "tna")
		{
			ss >> cmd;
			_teamNames.push_back(cmd);
		}
		else
			break;
		ss.str("");
		ss.clear();
	}
	return (true);
}

std::vector<std::string> 					Zappy::Map::getTeamNames() const
{
	return (_teamNames);
}

int 										Zappy::Map::getServerFd() const
{
	return (_fd);
}

const std::vector<std::vector<std::map<TileType, int> *> *> Zappy::Map::getMap() const
{
	return (_map);
}

float		 		Zappy::Map::getWidth() const
{
	return (_width);
}

float		 		Zappy::Map::getHeight() const
{
	return (_height);
}