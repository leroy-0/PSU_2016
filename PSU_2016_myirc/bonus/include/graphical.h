/*
** graphical.h for graphical in /home/tekm/tek2/PSU_2016_myirc/bonus
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Jun  1 15:23:31 2017 leroy_0
** Last update Thu Jun  1 15:23:34 2017 leroy_0
*/

#ifndef __GRAPHICAL_H__
#define __GRAPHICAL_H__

#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <pthread.h>

#include "myirc.h"

#define 		DEFAULT_BOX 		"./bonus/assets/transparent.png"
#define 		DEFAULT_POLICE		"./bonus/police/Roboto-Thin.ttf"
#define 		DEFAULT_BACKGROUND 	"./bonus/assets/background.jpg"

#define 		AMBIENT_SOUND		"./bonus/sounds/ambient.mp3"
#define 		WIN_SOUND			"./bonus/sounds/win.mp3"
#define 		SEND_SOUND 			"./bonus/sounds/send.mp3"

#define 		WIN_GIF				"./bonus/gifs/the_doc/"

#define 		MAX_MSG				(4096)
#define 		GIF_LATENCY			(10)

#define 		WINSIZE_X 			(1080)
#define 		WINSIZE_Y 			(920)

#define 		SIZE_MSG			(30)
#define 		SIZE_FONT			(16)

#define 		RATIO_CHANNEL 		(0.683)

typedef struct 		s_chat
{
	char 			*channel;
	char 			**msgs;
	int 			hist;
	struct s_chat 	*next;
}					t_chat;

typedef	struct  s_sdl_game
{
  SDL_Window    *pWindow;
  SDL_Renderer  *renderer;
  SDL_Surface   **gifs;
  SDL_Surface 	*screen;
  TTF_Font 		*font;
  SDL_Surface 	*background;
  SDL_Surface 	*channel;
  SDL_Event     event;
  Mix_Music     *music;

  bool 			modif;
  bool          quit;
  char 			*msg;
  int 			msg_len;
  char			*username;
  bool 			finished;

  struct s_chat	*chat;
  t_connect 	*client;
}				t_sdl_game;

//GIF
void            SDL_renderGIF(SDL_Renderer  *renderer, SDL_Surface **gifs);
SDL_Surface     **SDL_LoadGIF(char *directory);

//INIT
t_sdl_game      *init_all();
t_sdl_game      *init_sdl();
t_chat        	*init_chat();
void            free_sdl(t_sdl_game *sdl);
void            init_msg(t_sdl_game *sdl);

//TOOLS
bool            load_music(t_sdl_game *sdl, char *directory);
int         	rand_color(int x);
int 			cstring_cmp(const void *a, const void *b);
void            free_imgs(char **imgs);
void            blit_background(t_sdl_game *sdl);

//client
void            displayer(t_sdl_game *sdl);

//receive
void			*read_stdin(void *sdl);

#endif			/* __GRAPHICAL_H_ */
