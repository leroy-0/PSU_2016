/*
** Incantation.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Incantation.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 08:45:18 2017 Sebastien Bruere
** Last update Wed Jun 28 08:45:18 2017 Sebastien Bruere
*/

#include	<iostream>
#include <vector>
#include	"Incantation.hpp"


void ZappyAI::Incantation::initRequirement()
{
  requirement		tmp;
  std::map<ZappyAI::Stones, unsigned int> lvlMap;

  //1 -> 2
  tmp.players = 1;
  lvlMap[LINEMATE] = 1;
  lvlMap[DERAUMERE] = 0;
  lvlMap[SIBUR] = 0;
  lvlMap[MENDIANE] = 0;
  lvlMap[PHIRAS] = 0;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[2] = tmp;

  // 2 -> 3
  tmp.players = 2;
  lvlMap[LINEMATE] = 1;
  lvlMap[DERAUMERE] = 1;
  lvlMap[SIBUR] = 1;
  lvlMap[MENDIANE] = 0;
  lvlMap[PHIRAS] = 0;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[3] = tmp;

  // 3 -> 4
  tmp.players = 2;
  lvlMap[LINEMATE] = 2;
  lvlMap[DERAUMERE] = 0;
  lvlMap[SIBUR] = 1;
  lvlMap[MENDIANE] = 0;
  lvlMap[PHIRAS] = 2;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[4] = tmp;

  // 4 -> 5
  tmp.players = 4;
  lvlMap[LINEMATE] = 1;
  lvlMap[DERAUMERE] = 1;
  lvlMap[SIBUR] = 2;
  lvlMap[MENDIANE] = 0;
  lvlMap[PHIRAS] = 1;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[5] = tmp;

  // 5 -> 6
  tmp.players = 4;
  lvlMap[LINEMATE] = 1;
  lvlMap[DERAUMERE] = 2;
  lvlMap[SIBUR] = 1;
  lvlMap[MENDIANE] = 3;
  lvlMap[PHIRAS] = 0;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[6] = tmp;

  // 6 -> 7
  tmp.players = 6;
  lvlMap[LINEMATE] = 1;
  lvlMap[DERAUMERE] = 2;
  lvlMap[SIBUR] = 3;
  lvlMap[MENDIANE] = 0;
  lvlMap[PHIRAS] = 1;
  lvlMap[THYSTAME] = 0;
  tmp.stones = lvlMap;
  this->require[7] = tmp;

  // 7 -> 8
  tmp.players = 6;
  lvlMap[LINEMATE] = 2;
  lvlMap[DERAUMERE] = 2;
  lvlMap[SIBUR] = 2;
  lvlMap[MENDIANE] = 2;
  lvlMap[PHIRAS] = 2;
  lvlMap[THYSTAME] = 1;
  tmp.stones = lvlMap;
  this->require[8] = tmp;
}

//Recup l'inventaire ici
bool ZappyAI::Incantation::canIlevelUp(int level, std::map<ZappyAI::Stones, unsigned int>  stones)
{
  if (level < 9 && level > 1)
  {
    if (this->require[level].stones[ZappyAI::Stones::LINEMATE] <= stones[ZappyAI::Stones::LINEMATE]
      && this->require[level].stones[ZappyAI::Stones::DERAUMERE] <= stones[ZappyAI::Stones::DERAUMERE]
      && this->require[level].stones[ZappyAI::Stones::SIBUR] <= stones[ZappyAI::Stones::SIBUR]
      && this->require[level].stones[ZappyAI::Stones::MENDIANE] <= stones[ZappyAI::Stones::MENDIANE]
      && this->require[level].stones[ZappyAI::Stones::PHIRAS] <= stones[ZappyAI::Stones::PHIRAS]
      && this->require[level].stones[ZappyAI::Stones::THYSTAME] <= stones[ZappyAI::Stones::THYSTAME])
      return (true);
  }
  return (false);
}


std::map<ZappyAI::Stones, int> ZappyAI::Incantation::getMissingStones(
  int level, std::map<ZappyAI::Stones, unsigned int> stones)
{
  std::map<ZappyAI::Stones, int>	ret;

  ret[ZappyAI::Stones::LINEMATE] = 0;
  ret[ZappyAI::Stones::DERAUMERE] = 0;
  ret[ZappyAI::Stones::SIBUR] = 0;
  ret[ZappyAI::Stones::MENDIANE] = 0;
  ret[ZappyAI::Stones::PHIRAS] = 0;
  ret[ZappyAI::Stones::THYSTAME] = 0;

  if (level < 9 && level > 1) {
    ret[ZappyAI::Stones::LINEMATE] = this->require[level].stones[ZappyAI::Stones::LINEMATE] -
    stones[ZappyAI::Stones::LINEMATE];
    ret[ZappyAI::Stones::DERAUMERE] = this->require[level].stones[ZappyAI::Stones::DERAUMERE] -
    stones[ZappyAI::Stones::DERAUMERE];
    ret[ZappyAI::Stones::SIBUR] = this->require[level].stones[ZappyAI::Stones::SIBUR] -
    stones[ZappyAI::Stones::SIBUR];
    ret[ZappyAI::Stones::MENDIANE] = this->require[level].stones[ZappyAI::Stones::MENDIANE] -
    stones[ZappyAI::Stones::MENDIANE];
    ret[ZappyAI::Stones::PHIRAS] = this->require[level].stones[ZappyAI::Stones::PHIRAS] -
    stones[ZappyAI::Stones::PHIRAS];
    ret[ZappyAI::Stones::THYSTAME] = this->require[level].stones[ZappyAI::Stones::THYSTAME] -
    stones[ZappyAI::Stones::THYSTAME];
  }
  return (ret);
}

const ZappyAI::Incantation::requirement ZappyAI::Incantation::getRequirement(int level)
{
  if (level < 9 && level > 1)
  {
    return (require[level]);
  }
  else
    return (require[0]);
}