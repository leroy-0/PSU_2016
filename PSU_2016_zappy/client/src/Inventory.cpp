/*
** Inventory.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Inventory.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 08:45:15 2017 Sebastien Bruere
** Last update Wed Jun 28 08:45:15 2017 Sebastien Bruere
*/

#include	"Parser.hpp"
#include	"Inventory.hpp"

ZappyAI::Inventory::Inventory()
{
  this->food = 10;
  this->stones[LINEMATE] = 0;
  this->stones[DERAUMERE] = 0;
  this->stones[SIBUR] = 0;
  this->stones[MENDIANE] = 0;
  this->stones[PHIRAS] = 0;
  this->stones[THYSTAME] = 0;
}

ZappyAI::Inventory::~Inventory() {}

std::map<ZappyAI::Stones, unsigned int> & ZappyAI::Inventory::getStones()
{
  return (this->stones);
}

std::string ZappyAI::Inventory::stoneToString(ZappyAI::Stones & stone)
{
  std::map<ZappyAI::Stones, std::string> corres;

  corres[ZappyAI::LINEMATE] = std::string("linemate");
  corres[ZappyAI::SIBUR] = std::string("sibur");
  corres[ZappyAI::PHIRAS] = std::string("phiras");
  corres[ZappyAI::MENDIANE] = std::string("mendiane");
  corres[ZappyAI::THYSTAME] = std::string("thystame");
  corres[ZappyAI::DERAUMERE] = std::string("deraumere");
  return (corres[stone]);
}


ZappyAI::Stones ZappyAI::Inventory::stringToStone(std::string &stoneString)
{
  std::map<std::string, ZappyAI::Stones> corres;

  corres["linemate"] = ZappyAI::LINEMATE;
  corres["sibur"] = ZappyAI::SIBUR;
  corres["phiras"] = ZappyAI::PHIRAS;
  corres["mendiane"] = ZappyAI::MENDIANE;
  corres["thystame"] = ZappyAI::THYSTAME;
  corres["deraumere"] = ZappyAI::DERAUMERE;
  return (corres[stoneString]);
}

bool ZappyAI::Inventory::updateRessources(std::string &ressource)
{
  std::string		ress;
  std::string		quantity;
  ZappyAI::Stones	stone;
  int			where;

  where = ressource.find(' ');
  ress = ressource.substr(0, where);
  quantity = ressource.substr(where + 1, ressource.size() - where);

  if (ress.compare("food") == 0)
    this->food = std::atoi(quantity.c_str());
  else
  {
    stone = this->stringToStone(ress);
    if (!stone)
      return (false);
    this->stones[stone] = std::stoul(quantity);
  }
  return (true);
}

bool ZappyAI::Inventory::parseString(std::string &toParse)
{
  std::vector<std::string>	res;

  res = ZappyAI::Parser::tokeniser(toParse, ',');

  for (auto it = res.begin(); it < res.end(); ++it)
  {
    if (!this->updateRessources((*it)))
      return (false);
  }
  return (true);
}

void ZappyAI::Inventory::dump()
{
  std::cout << "--- Starting dump of inventory ------------------" << std::endl;
  std::cout << "Food : " << this->food << std::endl;
  std::cout << "Linemate :" << this->stones[LINEMATE] << std::endl;
  std::cout << "Deraumere :" << this->stones[DERAUMERE] << std::endl;
  std::cout << "Sibur :" << this->stones[SIBUR] << std::endl;
  std::cout << "Mendiane :" << this->stones[MENDIANE] << std::endl;
  std::cout << "Phiras :" << this->stones[PHIRAS] << std::endl;
  std::cout << "Thystame :" << this->stones[THYSTAME] << std::endl;
  std::cout << "--- Ending dump of inventory ---------------------" << std::endl << std::endl;

}

void ZappyAI::Inventory::updateInventory(std::string toParse)
{

  //std::string toParse("[food 345, sibur 3, phiras 5, linemate 10, mendiane 999, thystame 1, deraumere 10]");
  toParse.pop_back();
  toParse.erase(0, 1);
  this->parseString(toParse);
  //this->dump();
}