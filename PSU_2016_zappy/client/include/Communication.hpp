/*
** Communication.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Communication.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Tue Jun 27 08:59:41 2017 Sebastien Bruere
** Last update Tue Jun 27 08:59:42 2017 Sebastien Bruere
*/

#pragma				once

#include			<string>

namespace			ZappyAI
{
  class				Communication {
  public:
    Communication(int fd);
    virtual ~Communication();

    static bool			sendMessage(int, std::string);
    static std::string		recvMessage(int);
    bool			initConnexion(const std::string & );
    void			recordInitialProperty(const std::string &);

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