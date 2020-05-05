//
// Music.hpp for Music in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 13:54:22 2017 leroy_0
// Last update Mon Jun 26 13:54:25 2017 leroy_0
//

#ifndef __MUSIC_HPP__
#define __MUSIC_HPP__

#include <SFML/Audio.hpp>

namespace Zappy
{
	class Music
	{
	public:
		Music(const std::string & filename, const unsigned int volume, const bool loop);
		virtual ~Music();

	public:
		void	play();
		void	stop();

	private:
		sf::Music 	*_music;
	};
};

#endif 	// __MUSIC_HPP__