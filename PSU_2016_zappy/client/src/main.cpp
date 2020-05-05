/*
** main.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/main.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 13:59:40 2017 Sebastien Bruere
** Last update Wed Jun 28 08:16:32 2017 Sebastien Bruere
*/

#include		<iostream>
#include		"Client.hpp"
#include	<unistd.h>

bool			shouldIFork = false;
bool			isClientDead = false;

int			main(int ac, char **av)
{
  ZappyAI::Client	client;

  std::srand(time(NULL) * getpid());
  if (!(client.getArgs(ac, av)))
    return (1);
  client.run();
  return (0);
}