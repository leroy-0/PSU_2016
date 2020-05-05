/*
** Inventory.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Inventory.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 08:45:30 2017 Sebastien Bruere
** Last update Wed Jun 28 08:45:31 2017 Sebastien Bruere
*/

#ifndef PROJECT_INVENTORY_HPP
#define PROJECT_INVENTORY_HPP

#include	"Stones.hpp"
#include	<iostream>
#include	<string>
#include	<map>

namespace					ZappyAI
{
  class						Inventory
  {
  public:
    Inventory();
    ~Inventory();

    std::map<ZappyAI::Stones, unsigned int> &	getStones();
    inline int					getFood() {return food;};
    void					updateInventory(std::string toParse);
    void					dump();
    static ZappyAI::Stones			stringToStone(std::string & stoneString);
    static std::string				stoneToString(ZappyAI::Stones & stone);

  private:
    int						food;
    std::map<ZappyAI::Stones, unsigned int>	stones;

  private:
    bool					parseString(std::string & toParse);
    bool					updateRessources(std::string & ressource);
  };
}

#endif //PROJECT_INVENTORY_HPP
