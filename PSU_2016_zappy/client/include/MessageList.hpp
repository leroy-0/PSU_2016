/*
** MessageList.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/MessageList.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Thu Jun 29 12:06:46 2017 Sebastien Bruere
** Last update Thu Jun 29 12:06:46 2017 Sebastien Bruere
*/

#pragma				once

#include	<iostream>
#include			<string>
#include			<stack>

namespace			ZappyAI {
  class				messageList {
  public:
    messageList() {};
    virtual ~messageList() {};

    inline std::vector<std::string>	&getQueue() {return _queue;};

    bool				checkIsBorn(const std::string &teamName) {
      for (auto it = _queue.begin(); it < _queue.end(); ++it) {
	if ((*it).find("born") != std::string::npos &&
	    (*it).find(teamName) != std::string::npos) {
	  std::cout << "UNE IA EST NEE--------------" << std::endl;
	  return (true);
	}
      }
      return (false);
    }

  private:
    std::vector<std::string>	_queue;
  };
}