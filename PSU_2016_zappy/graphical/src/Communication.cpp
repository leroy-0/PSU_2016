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
#include		"Communication.hpp"

Zappy::Communication::Communication(int fd) {
  _server_fd = fd;
}
Zappy::Communication::~Communication() {}

t_tile        *Zappy::Communication::recvMap(int fd)
{
  t_tile      *map;

  if (recv(fd, &map, sizeof(map), 0) == -1)
    return (NULL);
  return (map);
}

std::string		         Zappy::Communication::recvMessage(int fd) {
  int                  r;
  std::string		       msg;
  std::vector<char>    buffer(2);

  while ((r = recv(fd, buffer.data(), 1, 0)) != -1)
  {
    if ((*buffer.cbegin()) == '\n')
      break;
    else
      msg += buffer[0];
  }
  std::cout << "MSG:" << msg << std::endl;
  return (msg);
}

bool			Zappy::Communication::sendMessage(int fd, std::string msg)
{
  msg += "\n";
  if (send(fd, msg.c_str(), std::strlen(msg.c_str()), 0) < 0)
    return (false);
  return (true);
}

bool			       Zappy::Communication::initConnexion(const std::string & teamName) {
  std::string		 msg;

  msg = Zappy::Communication::recvMessage(_server_fd);
  if (msg == "WELCOME")
  {
    if (!Zappy::Communication::sendMessage(_server_fd, teamName))
    {
      std::cerr << "Connexion initialisation failed, exiting now." << std::endl;
      return (false);
    }
  }
  else
  {
    std::cerr << "Wrong welcome message, exiting now." << std::endl;
    return (false);
  }
  return (true);
}
