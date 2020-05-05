/*
** Client.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Client.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 14:01:19 2017 Sebastien Bruere
** Last update Fri Jun 23 14:01:19 2017 Sebastien Bruere
*/

#include		<iostream>
#include		<unistd.h>
#include		<signal.h>
#include		<sys/wait.h>
#include		"Client.hpp"
#include		"Signal.hpp"

ZappyAI::Client::Client() {
  _nbClient = 0;
}

ZappyAI::Client::~Client() {}

bool			ZappyAI::Client::newAI() {
  int			pid;

  _allAI.push_back(ZappyAI::AI(_name, _machine, _port, rand()));
  _nbClient++;
  if (!_allAI.back().initAI())
    return (false);
  if ((pid = fork()) == -1)
    return (false);
  else if (pid == 0)
  {
    _allAI.back().run();
    exit(0);
  }
  else
    _allPid.push_back(pid);
  return (true);
}

void ZappyAI::Client::shouldFork() {
  if (shouldIFork)
  {
    newAI();
    shouldIFork = false;
  }
}

bool			ZappyAI::Client::run() {
  newAI();
  ZappyAI::Signal::receiveSignal(SIGUSR1);
  ZappyAI::Signal::receiveSignal(SIGUSR2);
  while (1)
  {
    shouldFork();
    if (isClientDead)
    {
      _nbClient--;
      isClientDead = false;
      if (_nbClient == 0)
	break;
    }
    //_com->recvMessage();
  }
  for (auto it = _allPid.begin(); it < _allPid.end(); ++it) {
    waitpid((*it), 0, 0);
  }
  return (true);
}

bool			ZappyAI::Client::getArgs(int ac, char **av)
{
  _args = new Parser(ac, av);
  if (!(_args->parse_args(ac, av)))
    return (printUsage());

  _name = _args->getNameTeam();
  _port = _args->getPort();
  _machine = _args->getNameMachine();
  return (true);
}


bool		ZappyAI::Client::printUsage()
{
  std::cerr << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
  std::cerr << "\tport is the port number" << std::endl;
  std::cerr << "\tname is the name of the team" << std::endl;
  std::cerr << "\tmachine is the name of the machine; localhost by default" << std::endl;
  return (false);
}