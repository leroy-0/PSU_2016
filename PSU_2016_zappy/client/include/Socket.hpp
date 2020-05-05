/*
** Socket.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Socket.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Mon Jun 26 13:41:43 2017 Sebastien Bruere
** Last update Mon Jun 26 13:43:13 2017 Sebastien Bruere
*/

#pragma once

#include		<netdb.h>
#include		<arpa/inet.h>

namespace		ZappyAI {
  class			Socket {

  public:
    Socket();
    virtual ~Socket();

    static int			connectSocket(struct protoent *);

  private:
  };
}