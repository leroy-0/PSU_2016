/*
** Parser.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Parser.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 14:05:34 2017 Sebastien Bruere
** Last update Fri Jun 23 14:05:34 2017 Sebastien Bruere
*/

#include			<iostream>
#include			<getopt.h>
#include			<memory.h>
#include			<cstdlib>
#include			"Parser.hpp"

ZappyAI::Parser::Parser(int ac, char **av) {
  _ac = ac;
  _av = av;
  init_ptr_func();
}
ZappyAI::Parser::~Parser() {}

void			ZappyAI::Parser::init_ptr_func()
{
  _ptr[0].arg = 'p';
  _ptr[0].ptr = &get_port;
  _ptr[1].arg = 'n';
  _ptr[1].ptr = &get_name_team;
  _ptr[2].arg = 'h';
  _ptr[2].ptr = &get_name_machine;
  _ptr[3].arg = '\0';
}

bool				ZappyAI::Parser::parse_args(int ac, char **av) {
  int				c;
  int				i;

  i = 0;
  while ((c = getopt(ac, av, "p:n:h:")) != -1)
  {
    i = 0;
    if (c == '?')
      return (false);
    while (_ptr[i].arg != '\0')
    {
      if (_ptr[i].arg == c)
      {
	if (!(_ptr[i].ptr(this, av, ac)))
	  return (false);
      }
      i++;
    }
  }
  if (i == 0)
    return (false);
  std::cout << i << std::endl;
  return (true);
}

bool			ZappyAI::Parser::get_port(Parser *_this, char **av, int ac)
{
  char		*port;

  if ((port = _this->recupValue(av, ac)) == NULL)
    return (false);
  if (!_this->is_number(port))
    return (false);
  _this->setPort(std::atoi(port));
  return (true);
}

bool		ZappyAI::Parser::get_name_team(Parser *_this, char **av, int ac)
{
  char		*name;

  if ((name = _this->recupValue(av, ac)) == NULL)
    return (false);
  _this->setName(name);
  return (true);
}

bool		ZappyAI::Parser::get_name_machine(Parser *_this, char **av, int ac)
{
  char		*localhost;

  if ((localhost = _this->recupValue(av, ac)) == NULL)
    return (false);
  _this->setMachine(localhost);
  return (true);
}

void		ZappyAI::Parser::setMachine(char *machine) {
  _machine = machine;
}
void		ZappyAI::Parser::setName(char *name) {
_name = name;
}
void		ZappyAI::Parser::setPort(int port) {
  _port = port;
}
char		*ZappyAI::Parser::getNameMachine() {
  return (_machine);
}
char		*ZappyAI::Parser::getNameTeam() {
  return (_name);
}
int		ZappyAI::Parser::getPort() {
  return (_port);
}

char		*ZappyAI::Parser::recupValue(char **av, int ac)
{
    if (optind != ac - 1)
    {
      if (av[optind - 1][0] != '-')
	return (strdup(av[optind - 1]));
      else
	return (NULL);
    }
    else
    {
      if (av[optind][0] != '-')
	return (strdup(av[optind]));
      else
	return (NULL);
    }
}

bool		ZappyAI::Parser::is_number(char *s)
{
  int		i;

  i = 0;
  while (s[i] != '\0')
  {
    if (s[i] < '0' || s[i] > '9')
      return (false);
    i++;
  }
  return (true);
}

int		ZappyAI::Parser::getTileNumberInBroadcast(std::string &msg) {
  std::string	tile("");

  for (unsigned int i = 0; i < msg.size(); i++)
  {
    if (std::isdigit(msg[i]))
      tile += msg[i];
  }
  return (std::stoi(tile));
}

std::vector<std::string> ZappyAI::Parser::tokeniser(std::string &toParse,
						    char sep)
{
  std::vector<std::string>	ret;
  std::string		tmp = toParse;
  size_t		save = 0;
  size_t		tmpi = 0;

  if (toParse.find(sep, save) == toParse.npos)
  {
    ret.push_back(toParse);
    return (ret);
  }
  while (tmpi != toParse.npos)
  {
    tmpi = toParse.find(sep, save);
    if (tmpi != toParse.npos)
      tmp = toParse.substr(save, (tmpi - save));
    else
      tmp = toParse.substr(save, toParse.size() - save);
    if (tmp.size() > 0)
    {
      while (tmp.size() > 0 && tmp.find(' ') == 0)
	tmp.erase(0, 1);
      while (tmp.size() > 0 && tmp.back() == ' ')
	tmp.pop_back();
    }
    save = tmpi + 1;
    ret.push_back(tmp);
  }
  return (ret);
}

unsigned int			ZappyAI::Parser::checkInQueueNeedMyLevel(ZappyAI::messageList queue) {
  unsigned int			nb = 0;

  for (auto it = queue.getQueue().begin(); it < queue.getQueue().end(); ++it) {
    std::cout << "CONTENUE DE LA QUEUE => " << (*it) << std::endl;
      if ((*it).find("here") != std::string::npos)
      {
	nb++;
      }
  }
  std::cout << "NB OF HERE " << nb << std::endl;
  return (nb);
}