//
// Network.hpp for Network in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 29 15:13:51 2017 leroy_0
// Last update Thu Jun 29 15:13:51 2017 leroy_0
//

#pragma once

#include		<netdb.h>
#include		<arpa/inet.h>
#include		"Socket.hpp"

namespace		Zappy {
  class			Network {

  public:
    Network();
    virtual ~Network();

    static int			initServerConnexion(const char *, int);
    static in_addr_t		hostnameToIp(const char * hostname);

  private:
  };
}
