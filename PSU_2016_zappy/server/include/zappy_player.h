/*
** zappy_player.h for player in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 14:40:17 2017 yan
** Last update Wed Jun 28 16:55:19 2017 Bachelet
*/

#ifndef			__ZAPPY_PLAYER__
# define		__ZAPPY_PLAYER__

#include		<stdbool.h>
#include		"zappy_buffer.h"
#include		"zappy_queue.h"
#include		"zappy_eggs.h"

enum			object
{
  FOOD = 0,
  LINEMATE,
  DERAUMERE,
  SIBUR,
  MENDIANE,
  PHIRAS,
  THYSTAME
};

typedef enum		e_dir
{
  UP = 1,
  RIGHT,
  DOWN,
  LEFT
} t_dir;

typedef struct		s_pos
{
  int			x;
  int			y;
} t_pos;

typedef struct		s_life_unit
{
  float			life;
  double		last;
} t_life_unit;

typedef struct		s_player
{
  t_dir			dir;
  t_pos			pos;
  int			fd;
  char			elevation;
  char			name[256];
  char			name_team[256];
  bool			team;
  int			inventory[7];
  int			id;
  t_buffer		*buffer;
  t_eggs		*eggs;
  t_queue		*queue;
  t_life_unit		health;
  struct s_player	*next;
} t_player;

t_player		*init_player();
t_player		*create_player();

#endif /* __ZAPPY_PLAYER__ */
