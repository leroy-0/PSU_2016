/*
** Group.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Group.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Thu Jun 29 09:09:17 2017 Sebastien Bruere
** Last update Thu Jun 29 09:09:17 2017 Sebastien Bruere
*/

#include <vector>
#include "AI.hpp"

namespace			ZappyAI
{
  class				Group
  {
  public:
    Group();
    ~Group();

  private:
    unsigned int		_nbPlayers;
    unsigned int		_idGroup;
    std::vector<ZappyAI::AI>	_players;
  };
}