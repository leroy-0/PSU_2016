/*
** Select.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Select.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Mon Jun 26 14:35:55 2017 Sebastien Bruere
** Last update Mon Jun 26 14:35:55 2017 Sebastien Bruere
*/


#pragma			once

#include		<sys/select.h>

namespace		ZappyAI {
  class			Select {

  public:
    Select(int);
    virtual ~Select();

    void		resetSelect();
    int			doSelect();
    int			getChangeServer();


  private:
    int			_server_fd;
    fd_set		_fdset;
  };
}