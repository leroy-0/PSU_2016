/*
** Communication.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Communication.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Tue Jun 27 09:00:25 2017 Sebastien Bruere
** Last update Tue Jun 27 09:00:26 2017 Sebastien Bruere
*/

#include		<iostream>
#include		<sys/socket.h>
#include		<cstring>
#include		<sys/signal.h>
#include		"Parser.hpp"
#include		"Signal.hpp"
#include		"Communication.hpp"

ZappyAI::Communication::Communication(int fd) {
  _server_fd = fd;
}
ZappyAI::Communication::~Communication() {}

std::string		ZappyAI::Communication::recvMessage(int fd) {
  char			buf[4096];
  std::string		msg("...");
  int			len;

  std::memset(buf, 0, 4096);
  if (fd > 0)
  {
    if ((len = recv(fd, buf, 4096, 0)) <= 0)
    {
      ZappyAI::Signal::sendSignal(SIGUSR2);
      exit(0);
    }
  }
  else
    exit(84);
  if (buf[0] == '\0')
    msg = "dead";
  else
  {
    msg = buf;
    msg.pop_back();
  }
  std::cout << "Message recv : [" << msg << "]" << std::endl;
  return (msg);
}

bool			ZappyAI::Communication::sendMessage(int fd, std::string msg) {
  if ((*msg.end()) != '\n')
    msg += "\n";
  std::cout << "Message send : [" << msg << "]" << std::endl;
  if (send(fd, msg.c_str(), std::strlen(msg.c_str()), 0) < 0)
    return (false);
  return (true);
}

void			ZappyAI::Communication::recordInitialProperty(const std::string &msg)
{
  unsigned long		pos = msg.find("\n");
  std::string		cut(msg.substr(pos, msg.size()));

  _maxClient = std::stoi(msg.substr(0, pos));
  _x = std::stoi(msg.substr(pos, cut.find(" ")));
  _y = std::stoi(msg.substr(cut.find(" ") + 1, cut.size()));
}

bool			ZappyAI::Communication::initConnexion(const std::string & teamName) {
  std::string		msg;

  msg = ZappyAI::Communication::recvMessage(_server_fd);
  if (msg.compare("WELCOME") == 0)
  {
    if (ZappyAI::Communication::sendMessage(_server_fd, teamName))
    {
      msg = ZappyAI::Communication::recvMessage(_server_fd);
      if (msg.empty() || msg.compare("ko") == 0)
      {
	std::cerr << "Connexion initialisation failed, exiting now." << std::endl;
	return (false);
      }
      recordInitialProperty(msg);
    }
  }
  else
  {
    std::cerr << "Wrong welcome message, exiting now." << std::endl;
    return (false);
  }
  return (true);
}
