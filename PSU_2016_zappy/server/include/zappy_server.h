/*
** zappy_server.h for zappy_server in /home/yan/Documents/psu/PSU_2016_zappy
** 
** Made by yan
** Login   <yan.poinssot@epitech.eu>
** 
** Started on  Wed Jun 21 14:47:05 2017 yan
** Last update Sun Jul  2 22:07:46 2017 Bachelet
*/

#ifndef		__ZAPPY_SERVER__
# define	__ZAPPY_SERVER__

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<netinet/in.h>
# include 	<sys/time.h>
# include 	<sys/resource.h>
# include	"zappy_parsing.h"
# include	"zappy_args.h"
# include	"zappy_player.h"
# include	"zappy_team.h"
# include	"zappy_tile.h"
# include	"zappy_ptr.h"

typedef struct          s_info
{
  int			width;
  int			height;
  int			freq;
  int			max_per_team;
  int			count;
} t_info;

typedef struct          s_connect
{
  struct sockaddr_in    s;
  int                   fd;
  int			max_fd;
  fd_set		fdset;
} t_connect;

typedef struct		s_server
{
  t_player		*player;
  t_team		*team;
  t_connect		*connect;
  t_tile		**map;
  t_info		info;
  struct rusage 	time;
} t_server;

t_team		*find_team(t_server *server, char *name);
int		add_team(t_server *server, char *name);
int		accept_new_player(t_server *server);
void		add_player_to_server(t_server *server, t_player *player);
int		add_player_to_team(t_server *server, char *team,
				   t_player *player);
t_server	*create_server(t_opt *info);
void		update_queues(t_server *server);
void		reset_select(t_server *server);
char		*add_coma(char *str);
char		*my_add_to_str(char *, char *);
void		print_my_map(t_player *player, t_tile **map,
			     int width, int height);
int		analyse_select(t_server *server);
void		update_max_fd(t_server *server);
bool		eject(t_server *server, char *line, t_player *player);
bool		connect_nbr(t_server *server, char *line, t_player *player);
bool		take(t_server *server, char *line, t_player *player);
bool		set(t_server *server, char *line, t_player *player);
bool		incantation(t_server *server, char *line, t_player *player);
bool		forward(t_server *server, char *line, t_player *player);
bool		left(t_server *server, char *line, t_player *player);
bool		right(t_server *server, char *line, t_player *player);
bool		look(t_server *server, char *line, t_player *player);
bool		broadcast(t_server *server, char *line, t_player *player);
bool		my_fork(t_server *server, char *line, t_player *player);
bool		inventory(t_server *server, char *line, t_player *player);
bool		error(t_server *server, char *line, t_player *player);
bool		death(t_server *server, t_player *player);
t_ptr_cmd	*init_my_ptr_func_cmd();
int		read_buffer(t_server *server, t_player *player);
int		execute_buffer(t_server *server, t_player *player);
void		add_player_to_server(t_server *server, t_player *player);
int		add_graphical(t_server *server, t_player *player);
t_player	*remove_player(t_server *server, t_player *player);
void		free_server(t_server *server);
bool		send_message(int fd, char *message);
bool		send_graphical(t_server *server, char *message);
bool		send_map(t_server *server, t_player *player);
bool		send_active_players(t_server *server, t_player *player);
bool		send_tile(t_server *server, int x, int y);
int		gest_command(t_player *player, t_server *server, char *line);
char		*epur_str(char *str);
void		set_position(t_server *server, t_player *player,
			     int pos_x, int pos_y);
char		*look_top(t_player *player, t_server *server);
char		*look_right(t_player *player, t_server *server);
char		*look_left(t_player *player, t_server *server);
char		*look_bottom(t_player *player, t_server *server);
int		update_life(t_server *server, t_player *player, double time_now);
bool		send_info(t_server *server, t_queue *tmp, t_player *player);
char		*add_element_inventory(char *inventory, int nb, char *name);
t_pos		find_shortest_path(t_pos start, t_pos end, t_info info_map);
char		*find_matching_tile(t_pos path, t_player *player);
char		get_tile_top(t_player *player);
char		get_tile_bottom(t_player *player);
char		get_tile_left(t_player *player);
char		get_tile_right(t_player *player);
char		get_tile_bottom_left(t_player *player);
char		get_tile_bottom_right(t_player *player);
char		get_tile_top_right(t_player *player);
char		get_tile_top_left(t_player *player);
void		update_new_pos(t_dir direction, t_pos *new_pos, t_info info);
bool		elevation_success(t_server *server, t_player *player);
int		count_nb_player(t_tile tile);
char		*message_to_broadcast(t_server *, t_player *, t_player *, char *);
void		update_on_map(t_server *server, t_player *player, t_pos pos);
void		make_elevation(t_tile *tile, t_server *server);

# define 	QUIT_PLAYER 1
# define	MSG_LENGTH 1024
# define	GRAPHICAL_NAME "GRAPHIC"

#endif /* __ZAPPY_SERVER__ */
