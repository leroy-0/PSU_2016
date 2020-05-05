//
// Map.hpp for Map in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 13:41:30 2017 leroy_0
// Last update Mon Jun 26 13:41:32 2017 leroy_0
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Communication.hpp"
#include "Network.hpp"
#include "typedef.hpp"

namespace Zappy
{
    class Map
    {
    public:
        Map();
        virtual ~Map();

    public:
        const std::vector<std::vector<std::map<TileType, int> *> *>     getMap() const;
        float                                                           getWidth() const;
        float                                                           getHeight() const;
        int                                                             getServerFd() const;
        std::vector<std::string>                                        getTeamNames() const;
        bool                                                            isConnected() const;

    public:
        bool                                                            connect(const std::string & hostname, int port);

    public:
        bool                                                            initSettings();
        bool                                                            initMap();
        bool                                                            initPlayers();

    private:
        std::vector<std::vector<std::map<TileType, int> *> *>           _map;
        std::vector<std::string>                                        _teamNames;
        Zappy::Communication                                            *_communication;
        int                                                             _frequency;
        int                                                             _fd;
        float                                                           _width;
        float                                                           _height;
        bool                                                            _connected;
    };
};

#endif //__MAP_HPP__
