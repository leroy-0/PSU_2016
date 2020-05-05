/*
** CommandSender.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/CommandSender.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 30 12:48:18 2017 Sebastien Bruere
** Last update Fri Jun 30 12:48:18 2017 Sebastien Bruere
*/

#include <cstring>
#include <iostream>
#include	"Communication.hpp"
#include	"CommandSender.hpp"
#include	"MessageList.hpp"

std::string ZappyAI::CommandSender::look(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Look\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg) /*
	 || msg.compare("ok") == 0 || msg.compare("ko") == 0*/)
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::right(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Right\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::left(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Left\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::forward(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Forward\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::inventory(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Inventory\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg) || msg.compare("ok") == 0 || msg.compare("ko") == 0)
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::connectNbr(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Connect_nbr\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg) || msg.compare("ok") == 0 || msg.compare("ko") == 0)
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::fork(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Fork\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::eject(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Eject\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::take(int fd, const std::string &object, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Take " + object + "\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::incantation(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Incantation\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}


std::string ZappyAI::CommandSender::checkLevelUp(int fd, std::vector<std::string> &queue)
{
  std::string				msg;

  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("Current") != std::string::npos)
      return (msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

std::string ZappyAI::CommandSender::broadcast(int fd, const std::string & msgB, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Broadcast " + msgB + "\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}

bool			ZappyAI::CommandSender::isSpecialMessage(const std::string &msg) {
  if (msg.find("dead") == 0 || msg.find("message") == 0 || msg.find("Eject") == 0 || msg.find("Current") == 0)
    return (true);
  return (false);
}

std::string ZappyAI::CommandSender::drop(int fd, const std::string &object, std::vector<std::string> &queue)
{
  std::string				msg;

  ZappyAI::Communication::sendMessage(fd, "Set " + object + "\n");
  msg = ZappyAI::Communication::recvMessage(fd);
  while (ZappyAI::CommandSender::isSpecialMessage(msg))
  {
    queue.push_back(msg);
    if (msg.find("dead") != msg.npos)
      return ("dead");
    msg = ZappyAI::Communication::recvMessage(fd);
  }
  return (msg);
}
