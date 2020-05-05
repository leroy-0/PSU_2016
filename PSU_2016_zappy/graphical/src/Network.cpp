//
// Network.cpp for network in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 29 15:13:41 2017 leroy_0
// Last update Thu Jun 29 15:13:41 2017 leroy_0
//

#include		<stdbool.h>
#include		<stdio.h>
#include		<unistd.h>
#include		<iostream>
#include		"Network.hpp"

Zappy::Network::Network() {

}
Zappy::Network::~Network() {}


in_addr_t	Zappy::Network::hostnameToIp(const char * hostname)
{
  struct hostent	*he;
  struct in_addr	**addr_list;

  if ((he = gethostbyname(hostname)) == NULL) {  // get the host info
    herror("gethostbyname");
    return ((in_addr_t)(-1));
  }
  addr_list = (struct in_addr **)he->h_addr_list;
  return (inet_addr(inet_ntoa(*addr_list[0])));
  return ((in_addr_t)(-1));
}

int			Zappy::Network::initServerConnexion(const char *hostname, int port)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if ((pe = getprotobyname("TCP")) == NULL)
    return (-1);
  if ((fd = Zappy::Socket::connectSocket(pe)) == -1)
    return (-1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = ntohs((uint16_t)(port));
  s_in.sin_addr.s_addr = Zappy::Network::hostnameToIp(hostname);
  if (connect(fd, (struct sockaddr *)(&s_in), sizeof(s_in)) == -1)
  {
    std::cerr << "Unable to establish a connection to " << hostname << ":" << port << std::endl;
    if (close(fd) == -1)
      return (-1);
    return (-1);
  }
  return (fd);
}
