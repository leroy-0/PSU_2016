/*
** AI.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/AI.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 15:01:15 2017 Sebastien Bruere
** Last update Wed Jun 28 15:01:15 2017 Sebastien Bruere
*/

#include		<iostream>
#include		<signal.h>
#include		<unistd.h>
#include		"Parser.hpp"
#include		"AI.hpp"
#include		"Signal.hpp"
#include		"CommandSender.hpp"
#include		"MessageList.hpp"
#include		"PathFinder.hpp"
#include		"Broadcast.hpp"

ZappyAI::AI::AI(const std::string & teamName, const std::string & machineName, int port,
		unsigned int id)
  : _inv(ZappyAI::Inventory()), _inc(ZappyAI::Incantation()), _vision(ZappyAI::Vision())
{
  _inc.initRequirement();
  _name = teamName;
  _machine = machineName;
  _port = port;
  _level = 1;
  _state = IDLE;
  _destinationTile = -1;
  _lay = false;
  _maxIdleElevationTurn = 5;
  _id = id;
  move = false;
  _targetId = -1;
  _numberOfMates = 0;
}
ZappyAI::AI::~AI() {}

bool					ZappyAI::AI::run()
{
  ZappyAI::Incantation::requirement	req;
  int					maxTurn = 3;
  std::list<ZappyAI::PathFinder::path>	path;


  ZappyAI::Broadcast::sendBroadcast(_server_fd, _id, "born " + _name, _queue.getQueue());
  while (1)
  {
    std::cout << std::endl << "Début de boucle, id : " << _id << ", _level : " << _level << ", state " << _state << "############" << std::endl;
    _inv.updateInventory(ZappyAI::CommandSender::inventory(_server_fd, _queue.getQueue())); // UPDATE INVENTORY EACH ITERATION
    _vision.look(ZappyAI::CommandSender::look(_server_fd, _queue.getQueue())); // LOOK EACH ITERATION
    this->pickFood();
    if (!_queue.getQueue().empty()) // HANDLE SPECIAL MESSAGE
    {
      if (handleSpecialMessage() == 1)
	break;
    }
    if (_destinationTile != -1)
    {
      if ((*_vision.getVision().begin()).player == 1)
      {
	path = ZappyAI::PathFinder::goToBroadcast(_destinationTile, _server_fd,
						  _queue);
	this->pathfinder(path);
      }
      _destinationTile = -1;
    }
    if (!handleLevelUp() && _state == IDLE) // BLOC DEPLACEMENT VERS STONE
    {
      path = ZappyAI::PathFinder::findPath(_inc.getMissingStones(_level + 1, _inv.getStones()), _vision.getVision());
      if (path.empty())
	this->searchForRessources(maxTurn);
      else
	this->pathfinder(path);
    }
    if (!_queue.getQueue().empty()) // HANDLE SPECIAL MESSAGE
    {
      if (handleSpecialMessage() == 1)
	break;
    }
    if (move)
      move = false;
    _queue.getQueue().clear();
  }
  ZappyAI::Signal::sendSignal(SIGUSR2);
  return (true);
}


bool ZappyAI::AI::initAI() {
  if (!(connexionToServer()) || (!(getInitialProperty())))
    return (false);
  return (true);
}

bool			ZappyAI::AI::handleLevelUp()
{
  bool			canILevelUp = false;
  ZappyAI::Vision::t_vision vision = (*_vision.getVision().begin());
  ZappyAI::Incantation::requirement req;

  req = _inc.getRequirement(_level + 1);
  if (_inc.canIlevelUp(_level + 1,
		       _inv.getStones())) // BLOC LEVEL UP IF ENOUGH IN INVENtORY
  {
    canILevelUp = true;
    if ((_numberOfMates + 1) == _inc.getRequirement(_level + 1).players)
      _state = HANDLING_ELEVATION;
    else if (_state == IDLE)
      _state = LOOKING_FOR_MATES;
  }
  if (canILevelUp) {
    if (vision.player == req.players)
    {
      if (_state == HANDLING_ELEVATION)
	this->handlingElevation();
    }
    else if (_state == LOOKING_FOR_MATES)
      ZappyAI::Broadcast::sendBroadcast(_server_fd, _id,
					"need " + std::to_string(_level),
					_queue.getQueue());
    else if (_state == HANDLING_ELEVATION)
      ZappyAI::Broadcast::sendBroadcast(_server_fd, _id, "join", _queue.getQueue());
  }
  return (canILevelUp);
}


void		ZappyAI::AI::pickFood()
{
  if (_vision.getVision().begin()->food > 0)
    ZappyAI::CommandSender::take(_server_fd, "food", _queue.getQueue());
}

int		ZappyAI::AI::handleSpecialMessage()
{
  for (std::vector<std::string>::iterator it = _queue.getQueue().begin(); it < _queue.getQueue().end(); ++it)
  {
    if ((*it).find("dead") != (*it).npos) // DEAD OF THE PLAYER
      return (1);
    if ((*it).find("Current") != (*it).npos && _state == IDLE_ELEVATION)
    {
      _level++;
      _state = IDLE;
      _numberOfMates = 0;
    }
    else if ((*it).find("message") != (*it).npos) {
      this->handlingBroadcast((*it));
      if (_state == ASKING_ELEVATION)
	break;
    }
  }
  for (auto i = _sendQueue.begin(); i < _sendQueue.end(); ++i)
    ZappyAI::Broadcast::sendBroadcast(_server_fd, _id, (*i), _queue.getQueue());
  _sendQueue.clear();
  return (0);
}

void		ZappyAI::AI::demandForkToParent() {
  if (ZappyAI::CommandSender::fork(_server_fd, _queue.getQueue()).compare("ok\n"))
  {
    ZappyAI::Signal::sendSignal(SIGUSR1);
    _lay = true;
  }
}

bool		ZappyAI::AI::getInitialProperty() {
  _com = new ZappyAI::Communication(_server_fd);

  if (!_com->initConnexion(_name))
    return (false);
  _maxClient = _com->getMaxClient();
  _mapX = _com->getMapX();
  _mapY = _com->getMapY();
  return (true);
}

bool		ZappyAI::AI::connexionToServer() {
  if ((_server_fd = ZappyAI::Network::initServerConnexion(_machine.c_str(), _port)) == -1)
    return (false);
  return (true);
}

void		ZappyAI::AI::searchForRessources(int &maxTurn)
{
  int		rand;

  rand = std::rand() % 100;
  if (maxTurn > 0)
  {
    ZappyAI::CommandSender::left(_server_fd, _queue.getQueue());
    move = true;
    maxTurn--;
  }
  else
  {
    if (rand >= 0 && rand < 25)
      ZappyAI::CommandSender::left(_server_fd, _queue.getQueue());
    if (rand >= 25 && rand < 50)
      ZappyAI::CommandSender::right(_server_fd, _queue.getQueue());
    for (unsigned int i = 0; i < ((rand % _level) + _level) ; ++i)
    {
      ZappyAI::CommandSender::forward(_server_fd, _queue.getQueue());
    }
    move = true;
    maxTurn = 3;
  }
}

void		ZappyAI::AI::pathfinder(std::list<ZappyAI::PathFinder::path> & path)
{

  for (auto pathfind = path.begin(); pathfind != path.end() ; ++pathfind)
    {
      if ((*pathfind).gatherFood && (*_vision.getVision().begin()).food > 0)
	ZappyAI::CommandSender::take(_server_fd, std::string("food"),
				     _queue.getQueue());
      if ((*pathfind).toGather.empty())
      {
	if ((*pathfind).toDo == PathFinder::direction::LEFT) {
	  ZappyAI::CommandSender::left(_server_fd, _queue.getQueue());
	  move = true;
	}
	if ((*pathfind).toDo == PathFinder::direction::RIGHT) {
	  ZappyAI::CommandSender::right(_server_fd, _queue.getQueue());
	  move = true;
	}
	if ((*pathfind).toDo == PathFinder::direction::FORWARD) {
	  ZappyAI::CommandSender::forward(_server_fd, _queue.getQueue());
	  move = true;
	}
      }
      else
      {
	for (auto gathering = (*pathfind).toGather.begin(); gathering < (*pathfind).toGather.end(); ++gathering)
	{
	  ZappyAI::CommandSender::take(_server_fd, ZappyAI::Inventory::stoneToString((*gathering)), _queue.getQueue());
	}
      }
      (*pathfind).toGather.clear();
    }
  path.clear();
}

void		ZappyAI::AI::dropStones(ZappyAI::Incantation::requirement & requirement)
{
  int		nbStonesToDrop = 0;
  std::string	stringStone;

  nbStonesToDrop = requirement.stones[ZappyAI::Stones::LINEMATE];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "linemate", _queue.getQueue());
    }
  }
  nbStonesToDrop = requirement.stones[ZappyAI::Stones::SIBUR];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "sibur", _queue.getQueue());
    }
  }
  nbStonesToDrop = requirement.stones[ZappyAI::Stones::PHIRAS];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "phiras", _queue.getQueue());
    }
  }
  nbStonesToDrop = requirement.stones[ZappyAI::Stones::MENDIANE];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "mediane", _queue.getQueue());
    }
  }
  nbStonesToDrop = requirement.stones[ZappyAI::Stones::THYSTAME];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "thystame", _queue.getQueue());
    }
  }
  nbStonesToDrop = requirement.stones[ZappyAI::Stones::DERAUMERE];
  if (nbStonesToDrop > 0)
  {
    for (int i = 0; i < nbStonesToDrop; ++i)
    {
      ZappyAI::CommandSender::drop(_server_fd, "deraumere", _queue.getQueue());
    }
  }
}


void		ZappyAI::AI::handlingElevation()
{
  auto		vision = (*_vision.getVision().begin());
  ZappyAI::Incantation::requirement req;

  req = _inc.getRequirement(_level + 1);
  if (!vision.stones.empty())
  {
    for (auto stone = vision.stones.begin();
	 stone < vision.stones.end(); ++stone)
    {
      std::cout << ZappyAI::Inventory::stoneToString((*stone))
		<< std::endl;
      ZappyAI::CommandSender::take(_server_fd,
				   ZappyAI::Inventory::stoneToString(
				     (*stone)), _queue.getQueue());
    }
  }
  this->dropStones(req);
  if (ZappyAI::CommandSender::incantation(_server_fd,
					  _queue.getQueue()).compare(
    "ko") != 0
      && ZappyAI::CommandSender::checkLevelUp(_server_fd,
					      _queue.getQueue()).find(
    "Current") != std::string::npos)
  {
    _state = IDLE;
    _level += 1;
    _numberOfMates = 0;
    _joiningId.clear();
  }
}

void		ZappyAI::AI::handlingBroadcast(std::string & it)
{
  std::vector<std::string>		tab;
  unsigned int				tmpPos = 0;
  unsigned int				tmpLvl = 0;
  int					checkingId = -1;

  tab = ZappyAI::Parser::tokeniser(it, ',');
  tmpPos = ZappyAI::Parser::getTileNumberInBroadcast(tab.at(0));
  checkingId = ZappyAI::Parser::getTileNumberInBroadcast(tab.at(1));
  std::cout << "Message => " << it << std::endl;
  std::cout << "ID => " << checkingId << std::endl;
  if (it.find("here") != it.npos)
  {
    tmpLvl = ZappyAI::Parser::getTileNumberInBroadcast(tab.at(2));
    if (tmpLvl == _level && (_numberOfMates + 1) < _inc.getRequirement(_level + 1).players && this->isNotConsidered(checkingId))
    {
      _sendQueue.push_back("come " + std::to_string(checkingId));
      _numberOfMates++;
    }
  }
  if (it.find("need") !=
      it.npos) // BROADCAST NEED OTHER PLAYER FOR LEVEL UP
  {
    tmpLvl = ZappyAI::Parser::getTileNumberInBroadcast(tab.at(2));
    if (tmpLvl >= _level)
    {
      if (!move && tmpLvl == _level && _state != IDLE_ELEVATION && _state != HANDLING_ELEVATION && checkingId != _targetId)
      {
	_state = ASKING_ELEVATION;
	_targetId = checkingId;
	_sendQueue.push_back("here " + std::to_string(_level));
      }
    }
  }
  if (it.find("come") != it.npos && _state == ASKING_ELEVATION && _maxIdleElevationTurn != 0)
  {
    if (_targetId == checkingId &&
      static_cast<int>(_id) == ZappyAI::Parser::getTileNumberInBroadcast(tab.at(2)))
      _state = IDLE_ELEVATION;
    _maxIdleElevationTurn--;
  }
  else if (_state == ASKING_ELEVATION && _maxIdleElevationTurn == 0)
  {
    _maxIdleElevationTurn = 5;
    _state = IDLE;
  }
  if (it.find("join") != it.npos && _targetId == checkingId && _state == IDLE_ELEVATION)
    _destinationTile = tmpPos;
}

bool ZappyAI::AI::isNotConsidered(int tocheck)
{
  for (auto it = _joiningId.begin(); it < _joiningId.end(); ++it)
  {
    if ((*it) == tocheck)
      return (false);
  }
  return (true);
}
