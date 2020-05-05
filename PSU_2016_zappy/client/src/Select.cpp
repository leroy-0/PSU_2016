/*
** Select.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Select.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Mon Jun 26 14:36:35 2017 Sebastien Bruere
** Last update Mon Jun 26 14:36:35 2017 Sebastien Bruere
*/

#include		<sys/socket.h>
#include		<iostream>
#include		"Select.hpp"

ZappyAI::Select::Select(int fd) {
  _server_fd = fd;
}

ZappyAI::Select::~Select() {}

void			ZappyAI::Select::resetSelect()
{
  FD_ZERO(&_fdset);
  FD_SET(0, &_fdset);
  FD_SET(_server_fd, &_fdset);
}

int			ZappyAI::Select::doSelect() {
  return (select(_server_fd + 1, &_fdset, NULL, NULL, NULL));
}

int			ZappyAI::Select::getChangeServer()
{
  int			size;
  char			buf[4096];

  if (FD_ISSET(_server_fd, &_fdset))
  {
    if ((size = recv(_server_fd, buf, 4096, 0)) <= 0)
      return (1);
    std::cout << "RECV == " << buf << std::endl;
  }
  return (0);
}