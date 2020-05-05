/*
** Socket.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Socket.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Mon Jun 26 13:44:02 2017 Sebastien Bruere
** Last update Mon Jun 26 14:14:58 2017 Sebastien Bruere
*/

#include		<iostream>
#include		"Socket.hpp"

ZappyAI::Socket::Socket() {
}
ZappyAI::Socket::~Socket() {}

int			ZappyAI::Socket::connectSocket(struct protoent *pe) {
  int			fd;

  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
  {
    std::cerr << "Socket call failed\n" << std::endl;
    return (-1);
  }
  return (fd);
}