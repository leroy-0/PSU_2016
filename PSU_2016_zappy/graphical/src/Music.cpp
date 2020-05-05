//
// Music.cpp for Music in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 13:53:07 2017 leroy_0
// Last update Mon Jun 26 13:53:08 2017 leroy_0
//

#include "Music.hpp"

Zappy::Music::Music(const std::string & filename, const unsigned int volume, const bool loop)
{
	_music = new sf::Music();
	if (!_music->openFromFile(filename))
		return ;
    _music->setVolume(volume);
    _music->setLoop(loop);
}

Zappy::Music::~Music()
{
	_music->pause();
	_music->stop();
	delete _music;
}

void	Zappy::Music::play()
{
	_music->play();
}

void 	Zappy::Music::stop()
{
	_music->stop();
}