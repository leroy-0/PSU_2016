/*
** Incantation.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Incantation.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 08:45:21 2017 Sebastien Bruere
** Last update Wed Jun 28 08:45:21 2017 Sebastien Bruere
*/

#ifndef PROJECT_INCANTATION_HPP
#define PROJECT_INCANTATION_HPP

#include	"Stones.hpp"
#include	<iostream>
#include	<string>
#include	<map>

namespace	ZappyAI
{
  class		Incantation
  {
  public:
    Incantation() {};
    virtual ~Incantation() {};
    struct requirement
    {
      unsigned int					players;
      std::map<ZappyAI::Stones, unsigned int>		stones;
    };

    void					initRequirement();
    bool					canIlevelUp(int level, std::map<ZappyAI::Stones, unsigned int> stones);
    std::map<ZappyAI::Stones, int>		getMissingStones(int level, std::map<ZappyAI::Stones, unsigned int> stones);
    const requirement				getRequirement(int level);

  private:
    std::map<unsigned int, struct requirement>	require;
  };
}

#endif //PROJECT_INCANTATION_HPP
