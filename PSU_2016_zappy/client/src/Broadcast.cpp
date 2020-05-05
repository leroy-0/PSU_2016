/*
** Broadcast.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Broadcast.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 30 15:21:12 2017 Sebastien Bruere
** Last update Fri Jun 30 15:21:12 2017 Sebastien Bruere
*/

#include			"Broadcast.hpp"
#include			"CommandSender.hpp"

ZappyAI::Broadcast::Broadcast() {}
ZappyAI::Broadcast::~Broadcast() {}

void ZappyAI::Broadcast::sendBroadcast(int fd, unsigned  int id, const std::string &msg, std::vector<std::string> &queue)
{
  ZappyAI::CommandSender::broadcast(fd, "id : " + std::to_string(id) + "," + msg, queue);
}