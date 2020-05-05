/*
** Signal.cpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/src/Signal.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 16:00:33 2017 Sebastien Bruere
** Last update Wed Jun 28 16:00:33 2017 Sebastien Bruere
*/

#include			<unistd.h>
#include			<signal.h>
#include			<csignal>
#include			"Signal.hpp"
#include			"Client.hpp"

ZappyAI::Signal::Signal() {}
ZappyAI::Signal::~Signal() {}

bool ZappyAI::Signal::sendSignal(int sig) {
  pid_t 		ppid;

  ppid = getppid();
  kill(ppid, sig);
  return (true);
}

void ZappyAI::Signal::handlerSignal(int sig) {
  if (sig == SIGUSR1)
    shouldIFork = true;
  if (sig == SIGUSR2)
    isClientDead = true;
}

void ZappyAI::Signal::receiveSignal(int sig) {
  std::signal(sig, handlerSignal);
}