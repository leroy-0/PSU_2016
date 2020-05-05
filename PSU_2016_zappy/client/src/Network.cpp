/*
** network.c for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/network.c
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 12:14:01 2017 Sebastien Bruere
** Last update Mon Jun 26 13:43:07 2017 Sebastien Bruere
*/

#include		<stdbool.h>
#include		<stdio.h>
#include		<iostream>
#include		<unistd.h>
#include		"Network.hpp"

ZappyAI::Network::Network() {

}
ZappyAI::Network::~Network() {}


in_addr_t	ZappyAI::Network::hostnameToIp(const char * hostname)
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

int			ZappyAI::Network::initServerConnexion(const char *hostname, int port)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if ((pe = getprotobyname("TCP")) == NULL)
    return (-1);
  if ((fd = ZappyAI::Socket::connectSocket(pe)) == -1)
    return (-1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = ntohs((uint16_t)(port));
  s_in.sin_addr.s_addr = ZappyAI::Network::hostnameToIp(hostname);
  if (connect(fd, (struct sockaddr *)(&s_in), sizeof(s_in)) == -1)
  {
    std::cerr << "Unable to establish a connection to " << hostname << ":" << port << std::endl;
    if (close(fd) == -1)
      return (-1);
    return (-1);
  }
  return (fd);
}
