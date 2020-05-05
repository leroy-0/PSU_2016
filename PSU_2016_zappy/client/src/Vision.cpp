/*
** Vision.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Vision.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 30 11:13:41 2017 Sebastien Bruere
** Last update Fri Jun 30 11:13:41 2017 Sebastien Bruere
*/

#include	"Vision.hpp"
#include	"Parser.hpp"
#include	"Inventory.hpp"

ZappyAI::Vision::Vision() {}

ZappyAI::Vision::~Vision() {}


ZappyAI::Vision::t_vision ZappyAI::Vision::getTileStruct(std::string &tile, int howMuch)
{
  std::vector<std::string>	tab;
  t_vision			ret;
  ZappyAI::Stones		stone;

  ret.pos = howMuch;
  ret.player = 0;
  ret.food = 0;
  if (!tile.empty())
  {
    tab = ZappyAI::Parser::tokeniser(tile, ' ');
    for (auto it = tab.begin(); it < tab.end(); ++it)
    {
      //std::cout << "-----------------[" << (*it) << "]-----------------" << std::endl;
      if ((*it).find("food") != (*it).npos)
	ret.food += 1;
      else if ((*it).find("player") != (*it).npos)
	ret.player += 1;
      else
      {
	if ((*it).size() > 0)
	{
	  stone = ZappyAI::Inventory::stringToStone((*it));
	  if (!stone) {
	    //On jete une exception sa mère
	  }
	  ret.stones.push_back(stone);
	}
      }
    }
  }
  return (ret);
}

void ZappyAI::Vision::updateVision(std::string &tile, int howMuch)
{
  vision.push_back(this->getTileStruct(tile, howMuch));
}

void ZappyAI::Vision::look(std::string toParse)
{

  //std::string toParse("[player food thystame linemate sibur food,,,,,,,,,,,,,,,,]");
  std::vector<std::string>	tiles;
  int				howMuch = 0;
  std::vector<std::string>::iterator it;

  this->vision.clear();
  toParse.pop_back();
  toParse.erase(0, 1);
  tiles = ZappyAI::Parser::tokeniser(toParse, ',');

  for (it = tiles.begin() ; it < (tiles.end()); ++it)
  {
    this->updateVision((*it), howMuch);
    howMuch++;
  }
}

void ZappyAI::Vision::dump()
{
  for (auto i = this->vision.begin(); i != this->vision.end(); ++i)
  {
      std::cout << "Numero de case de vision " << (*i).pos << std::endl;
      std::cout << "Player " << (*i).player << std::endl;
      std::cout << "Food " << (*i).food << std::endl;
      std::cout << "Stones : " << std::endl;
      for (auto k = (*i).stones.begin(); k < (*i).stones.end(); ++k)
      {
	std::cout << "[" << ZappyAI::Inventory::stoneToString((*k)) << "] ";
      }
      std::cout << std::endl << std::endl;
  }
}

bool			ZappyAI::Vision::isTileEmpty(int tile) {
  static_cast<void>(tile);
  return (false);
}

int			ZappyAI::Vision::getRowNb(int pos)
{
  int		start;
  int		ret = 0;
  int		total = 0;

  start = 1;
  while (total < pos)
  {
    total += start;
    start = start + 2;
    total += start;
    ret++;
  }
  return (ret);
}