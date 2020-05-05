/*
** Broadcast.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Broadcast.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 30 15:10:48 2017 Sebastien Bruere
** Last update Fri Jun 30 15:10:48 2017 Sebastien Bruere
*/

#include			<vector>
#include			<string>

namespace 			ZappyAI {
  class				Broadcast {
  public:
    Broadcast();
    virtual ~Broadcast();

    static void			sendBroadcast(int ,unsigned  int, const std::string &, std::vector<std::string> &);
  };
}