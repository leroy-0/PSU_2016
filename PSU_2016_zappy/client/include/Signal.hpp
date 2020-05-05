/*
** Signal.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Signal.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 15:59:28 2017 Sebastien Bruere
** Last update Wed Jun 28 15:59:29 2017 Sebastien Bruere
*/


#pragma once

namespace		ZappyAI
{
  class			Signal {
  public:
    Signal();
    virtual ~Signal();

    static void		handlerSignal(int);
    static bool		sendSignal(int);
    static void		receiveSignal(int);

  private:
  };
}