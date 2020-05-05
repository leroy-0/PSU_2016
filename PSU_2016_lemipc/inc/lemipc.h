/*
** lemipc.h for lemipc in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Wed Mar 22 08:52:44 2017 leroy_0
** Last update Sun Apr  2 13:18:52 2017 longle_h
*/

#ifndef		__LEMIPC_H_
# define	__LEMIPC_H_

#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<semaphore.h>
#include	<stdbool.h>

# define	DEFAULT_SHMSIZE 	(1024)
# define	MAXLENMSG		(5)

typedef struct	s_pos
{
  int		x;
  int		y;
}		t_pos;

typedef struct	s_msgbuf
{
  long		mtype;
  char		mtext[MAXLENMSG];
}		t_msg;

typedef struct 	s_game
{
  key_t		team_channel;
  key_t		key;
  int		team_id;
  int		shmflg;
  size_t	pos_player;
  size_t	size;
  int		mesid;
  int		mesid_team;
  int		semid;
  int		shmid;
  char		*addr;
}		t_game;

typedef enum	e_where
  {
    UP		= -32,
    DOWN	= 32,
    LEFT	= -1,
    RIGHT	= 1,
    UP_R	= -31,
    UP_L	= -33,
    DOWN_R	= 33,
    DOWN_L	= 31,
    UNDEFINED	= 0
  }		e_where;

typedef	struct	s_enemy
{
  e_where	dir;
  int		pos;
}		t_enemy;

bool		is_digit(char *nb);
bool 		is_lower(char *key);
void		launch_game(t_game *game);
void		print_map(t_game *game);
void		join_team(t_game *game);
void		end_game(t_game *game);
void		lemipc(char *team_key, int team_lvl);
t_game		*init_game(key_t key, int id, key_t team_channel);
char		*createmap(unsigned int size);
void		print_map(t_game *game);
bool		set_position(t_game *game, size_t pos, int team_id);
void		launch_game(t_game *game);
void		put_pos_in_mes(size_t pos, t_msg *mes);
char		*positon_to_string(size_t pos);
t_pos		pos_to_x_y(size_t player_pos);
void		send_position(t_game *game, size_t pos);
t_pos		receive_position(t_game *game);
int		cmp_pos(int x, int y);
char		*reverse_buf(char *src, int len);
t_pos		receive_position_no_block(t_game *game, long type);
t_enemy		*search_enemy(t_game *game, int pos, char id);
t_pos		attack_enemy(t_game *game, t_enemy *enemy);
void		game_loop(t_game *pGame, t_pos pos);
bool		is_alive(t_game *pGame);
t_pos		set_aim(t_game *pGame);
bool		check_victory(t_game *game);
int		get_next_pos(int, int);
void		first_player(t_game *game);
void		other_player(t_game *game);
e_where		getDir(int x, int y, int x2, int y2);
bool		is_alive(t_game *game);
void		go_to_dir(t_game *game, int x, int y);
bool		check_victory(t_game *game);
void    lock(t_game *game);
void    unlock(t_game *game);

#endif		/* __LEMIPC_H_ */
