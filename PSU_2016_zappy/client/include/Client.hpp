/*
** Client.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Client.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 13:47:47 2017 Sebastien Bruere
** Last update Fri Jun 23 13:47:47 2017 Sebastien Bruere
*/

#pragma				once

#include			<iostream>
#include			"Parser.hpp"
#include			"Network.hpp"
#include			"Select.hpp"
#include			"Communication.hpp"
#include			"AI.hpp"

extern bool			shouldIFork;
extern bool			isClientDead;


namespace			ZappyAI
{
  class				Client {
  public:
    Client();
    virtual ~Client();

    bool			getArgs(int , char **);
    bool			printUsage();
    bool			run();
    bool			newAI();
    void			shouldFork();

  private:
    std::vector<ZappyAI::AI>	_allAI;
    Parser			*_args;
    Select			*_select;

    std::vector<pid_t>		_allPid;
    int				_port;
    char			*_name;
    char			*_machine;
    int				_server_fd;
    int				_maxClient;
    int				_nbClient;
    int				_mapX;
    int				_mapY;
  };
}