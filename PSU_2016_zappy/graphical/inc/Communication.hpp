//
// Communication.hpp for Communication in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 29 15:14:01 2017 leroy_0
// Last update Thu Jun 29 15:14:01 2017 leroy_0
//

#pragma				once

#include      "zappy_tile.h"
#include			<string>
#include      <vector>

namespace			Zappy
{
  class				Communication {
  public:
    Communication(int fd);
    virtual ~Communication();

    static bool		 sendMessage(int, std::string);
    std::string		 recvMessage(int);
    bool			     initConnexion(const std::string & );
    t_tile         *recvMap(int _fd);

    inline int			getMaxClient() const {return _maxClient;}
    inline int			getMapX() const {return _x;}
    inline int			getMapY() const {return _y;}
  private:
    int				_server_fd;
    int				_maxClient;
    int				_x;
    int				_y;
  };
}
