//
// main.cpp for main.cpp in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 14:33:05 2017 leroy_0
// Last update Fri Jun 23 14:33:06 2017 leroy_0
//

#include "Renderer.hpp"

int		main()
{
	Zappy::Renderer	renderer(WINSIZE_X, WINSIZE_Y);
	renderer.run();
}