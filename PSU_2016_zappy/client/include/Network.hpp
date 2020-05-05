/*
** Network.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Network.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 13:54:07 2017 Sebastien Bruere
** Last update Fri Jun 23 13:54:09 2017 Sebastien Bruere
*/

#pragma once

#include		<netdb.h>
#include		<arpa/inet.h>
#include		"Socket.hpp"

namespace		ZappyAI {
  class			Network {

  public:
    Network();
    virtual ~Network();

    static int			initServerConnexion(const char *, int);
    static in_addr_t		hostnameToIp(const char * hostname);

  private:
  };
}