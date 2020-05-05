/*
** lemipc.h for lemipc in /home/tekm/tek2/PSU_2016_lemipc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Sun Apr  2 18:24:23 2017 leroy_0
** Last update Sun Apr  2 18:24:24 2017 leroy_0
*/

#ifndef __LEMIPC_H_
# define __LEMIPC_H_

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <dirent.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#define 		DEFAULT_SHMSIZE 	(1024)
#define 		MAXLENMSG 			(5)

#define 		AMBIENT_SOUND		"./bonus/sounds/ambient.mp3"
#define 		WIN_SOUND			"./bonus/sounds/win.mp3"
#define 		WIN_GIF				"./bonus/gifs/the_doc/"

#define 		GIF_LATENCY			(10)

typedef struct 	s_msgbuf
{
	long  		mtype;
	char  		mtext[MAXLENMSG];
}				t_msg;

typedef struct 	s_game
{
	key_t 		team_channel;
	key_t     	key;
	int 		team_id;
	int       	shmflg;
	size_t 		pos_player;
	size_t    	size;

	int 		mesid;
	int 		mesid_team;
	int 		semid;
	int 		shmid;

	char 		*addr;
}				t_game;

typedef	struct  s_sdl_game
{
  SDL_Window    *pWindow;
  SDL_Renderer  *renderer;
  SDL_Surface   **gifs;
  SDL_Event     event;

  Mix_Music     *music;

  bool          quit;
  bool 			victory;
}				t_sdl_game;

//LIB
bool     		is_digit(char *nb);
bool 			is_lower(char *key);

//LEMI
void        	launch_game(t_game *game);
void        	print_map(t_game *game);
void    		join_team(t_game *game);
void        	end_game(t_game *game);
t_game      	*init_game(key_t key, int id, key_t team_channel);
char            *createmap(unsigned int size);
void            print_map(t_game *game);
bool        	set_position(size_t pos, char *map, int team_id);
void        	launch_game(t_game *game);
void        	put_pos_in_mes(size_t pos, t_msg *mes);
char    		*positon_to_string(size_t pos);
int 			get_next_pos(int, int);

//BONUS
bool 			check_victory(t_game *);
int             get_victorious(t_game *game);
int             victory_sdl(t_sdl_game  *sdl);
void            SDL_renderGIF(SDL_Renderer  *renderer, SDL_Surface **gifs);
void            display_gameMap(t_sdl_game *sdl, t_game *game);
t_sdl_game      *init_sdl();
void            free_sdl(t_sdl_game *sdl);
bool            load_music(t_sdl_game *sdl, char *directory);
SDL_Surface     **SDL_LoadGIF(char *directory);
int         	rand_color(int x);
int 			cstring_cmp(const void *a, const void *b);
void            free_imgs(char **imgs);

#endif			/* __LEMIPC_H_ */
