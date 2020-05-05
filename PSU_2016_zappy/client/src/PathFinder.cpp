#include	<iostream>
#include	<unistd.h>
#include <CommandSender.hpp>
#include <MessageList.hpp>
#include	"Inventory.hpp"
#include	"PathFinder.hpp"

ZappyAI::PathFinder::path ZappyAI::PathFinder::generateNode(
  std::vector<ZappyAI::Stones> toGather, bool gatherFood, int pos)
{
  ZappyAI::PathFinder::path ret;

  ret.toGather = toGather;
  ret.gatherFood = gatherFood;
  ret.pos = pos;
  ret.toDo = FORWARD;
  return (ret);
}


//Rangée du milieu +2, +4, +6, +8 etc...
//Rangée du milieu == taille rangée précedente + 2
std::list<ZappyAI::PathFinder::path> ZappyAI::PathFinder::findPath(
  std::map<ZappyAI::Stones, int> toFind,
  std::list<ZappyAI::Vision::t_vision> vision)
{
  std::list<ZappyAI::PathFinder::path>	path;
  std::vector<ZappyAI::Stones>		gathering;
  int					tileNb;

  for (auto it = vision.begin(); it != vision.end(); ++it) {
    tileNb = (*it).pos;
    for (auto stones = (*it).stones.begin();
	 stones < (*it).stones.end(); ++stones) {
      if (toFind[(*stones)] > 0)
      {
	gathering.push_back((*stones));
	toFind[(*stones)]--;
      }
    }
    if (!gathering.empty()) {
      path.push_back(
	ZappyAI::PathFinder::generateNode(gathering, false, tileNb));
      break;
    }
    gathering.clear();
  }
  if (!path.empty())
    path = ZappyAI::PathFinder::stickPath(path);
 return (path);
}


std::list<ZappyAI::PathFinder::path> ZappyAI::PathFinder::stickPath(
  std::list<ZappyAI::PathFinder::path>	path)
{
  int		rowToGo;
  int		myRow = 0;
  int		myPos = 0;
  auto		toGo = (*path.begin());
  auto		tmp_It = path.begin();
  std::list<ZappyAI::PathFinder::path>	ret;
  ZappyAI::PathFinder::path	tmp;
  ZappyAI::PathFinder::direction dir;

  rowToGo = ZappyAI::Vision::getRowNb(toGo.pos);
  if (rowToGo == 0)
    return (path);
  else
  {
    while (myRow != rowToGo)
    {
      myRow++;
      tmp.pos = myPos + (myRow * 2);
      tmp.toDo = FORWARD;
      myPos  = myPos + (myRow * 2);
      ret.push_back(tmp);
    }
    if (myPos - toGo.pos > 0)
      dir = ZappyAI::PathFinder::direction::LEFT;
    else if (myPos - toGo.pos < 0)
      dir = ZappyAI::PathFinder::direction::RIGHT;
    else
      dir = ZappyAI::PathFinder::direction::FORWARD;
    tmp.toDo = dir;
    tmp.pos = myPos;
    ret.push_back(tmp);
    while (myPos != toGo.pos)
    {
      if (dir == ZappyAI::PathFinder::direction::RIGHT)
	myPos++;
      else if (dir == ZappyAI::PathFinder::direction::LEFT)
	myPos--;
      tmp.toDo = ZappyAI::PathFinder::direction ::FORWARD;
      tmp.pos = myPos;
      ret.push_back(tmp);
    }
  }
  ret.push_back((*tmp_It));
  return (ret);
}

std::list<ZappyAI::PathFinder::path> ZappyAI::PathFinder::goToBroadcast(
  int directionTile, int fd, ZappyAI::messageList &_queue)
{
  int			newDir = 0;
  std::list<ZappyAI::PathFinder::path>	path;
  ZappyAI::PathFinder::path		route;

  if (directionTile == 3 || directionTile == 4)
    while (ZappyAI::CommandSender::left(fd, _queue.getQueue()).compare("ok"));
  if (directionTile == 7 || directionTile == 6)
    while (ZappyAI::CommandSender::right(fd, _queue.getQueue()).compare("ok"));
  if (directionTile == 5)
  {
    while (ZappyAI::CommandSender::right(fd, _queue.getQueue()).compare("ok"));
    while (ZappyAI::CommandSender::right(fd, _queue.getQueue()).compare("ok"));
  }
  if (directionTile == 4 || directionTile == 2 || directionTile == 5)
    newDir = 1;
  else if (directionTile == 3 || directionTile == 7 || directionTile == 1)
    newDir = 2;
  else if (directionTile == 6 || directionTile == 8)
    newDir = 3;
  route.pos = newDir;
  path.push_back(route);
  return (ZappyAI::PathFinder::stickPath(path));
}

void ZappyAI::PathFinder::dump(std::list<ZappyAI::PathFinder::path> path)
{
  int		nb;

  nb = 1;
  for (auto i = path.begin(); i != path.end(); ++i)
  {
    std::cout << "Action n° " << nb << std::endl;
    std::cout << "Case vue n° "  << (*i).pos << std::endl;
    std::cout << "Les pierres à rammasser : " << std::endl;
    for (auto j = (*i).toGather.begin(); j < (*i).toGather.end(); ++j)
    {
      std::cout << "     " << ZappyAI::Inventory::stoneToString(*j) << std::endl;
    }
    std::cout << "Direction ";
    if ((*i).toDo == LEFT)
    {
      std::cout << " LEFT " << std::endl;
    }
    if ((*i).toDo == RIGHT)
    {
      std::cout << " RIGHT " << std::endl;
    }
    if ((*i).toDo == FORWARD)
    {
      std::cout << " FORWARD " << std::endl;
    }
    nb++;

    std::cout << std::endl << std::endl;
  }
}
