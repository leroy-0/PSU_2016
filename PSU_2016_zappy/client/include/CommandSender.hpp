/*
** CommandSender.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/CommandSender.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Thu Jun 29 12:14:56 2017 Sebastien Bruere
** Last update Thu Jun 29 12:14:56 2017 Sebastien Bruere
*/

#ifndef PROJECT_COMMANDSENDER_HPP
#define PROJECT_COMMANDSENDER_HPP

#include	<vector>

namespace	ZappyAI
{
  class		CommandSender
  {
  public:
    CommandSender(){};
    virtual ~CommandSender(){};

    static std::string	forward(int fd, std::vector<std::string> &);
    static std::string	right(int fd, std::vector<std::string> &);
    static std::string	left(int fd, std::vector<std::string> &);
    static std::string	look(int fd, std::vector<std::string> &);
    static std::string	inventory(int fd, std::vector<std::string> &);
    static std::string	connectNbr(int fd, std::vector<std::string> &);
    static std::string	fork(int fd, std::vector<std::string> &);
    static std::string	eject(int fd, std::vector<std::string> &);
    static std::string	take(int fd, const std::string & object, std::vector<std::string> &);
    static std::string	incantation(int fd, std::vector<std::string> &);
    static std::string	broadcast(int, const std::string &, std::vector<std::string> &);
    static std::string drop(int fd, const std::string &object, std::vector<std::string> &queue);
    static std::string checkLevelUp(int fd, std::vector<std::string> &queue);

    static bool		isSpecialMessage(const std::string &);
  };
}

#endif //PROJECT_COMMANDSENDER_HPP
