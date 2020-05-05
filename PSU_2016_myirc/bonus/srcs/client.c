/*
** client.c for graphical in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Thu Jun  1 15:30:19 2017 leroy_0
** Last update Thu Jun  1 15:30:19 2017 leroy_0
*/

#include "graphical.h"

char *composition;
Sint32 cursor;
Sint32 selection_len;

void            display_channels(t_sdl_game *sdl)
{
  SDL_Surface   *text_surface;
  SDL_Rect      location;
  SDL_Color     color  = {255, 255, 255, 0xFF};
  t_chat        *tmp;
  int           it = 1;
  int           sizex = 2;
  char          *msg;

  tmp = sdl->chat;
  while ((tmp = tmp->next))
    sizex++;
  sizex = WINSIZE_X / sizex;

  tmp = sdl->chat;
  while (tmp)
  {
    if (!tmp->channel || tmp->channel[0] == '\0')
      msg = " ";
    else
    {
      if (!(msg = malloc(sizeof(char) * strlen(tmp->channel) + 2)))
        return ;
      msg[0] = '\0';
      msg = strcat(msg, "#");
      msg = strcat(msg, tmp->channel);
    }
    location.x = sizex * it;
    location.y = 10;
    location.w = sizex;
    location.h = SIZE_MSG + 4;
    if(!(text_surface = TTF_RenderText_Solid(sdl->font, msg, color)))
    { 
      printf("Failed to render text\n");
      return ;
    }
    else
    {
      SDL_BlitSurface(text_surface, NULL, sdl->screen, &location);
      SDL_FreeSurface(text_surface);
    }
    it++;
    tmp = tmp->next;
  }
}

void            displayMsg(t_sdl_game *sdl, char *msg, int x, int y)
{
  SDL_Surface   *text_surface;
  SDL_Rect      location = { x , y, SIZE_MSG, SIZE_MSG};
  SDL_Color     color  = {255, 255, 255, 0xFF};

  if (!msg || msg[0] == '\0')
  {
    msg = " ";
  }
  if(!(text_surface = TTF_RenderText_Solid(sdl->font, msg, color)))
  { 
    printf("Failed to render text\n");
    return ;
  }
  else
  {
    SDL_BlitSurface(text_surface, NULL, sdl->screen, &location);
    SDL_FreeSurface(text_surface);
  }
}

void            display_chat(t_sdl_game *sdl)
{
  int           x = sdl->chat->hist - 1;
  int           y = 0;

  while (x >= 0)
  {
    if (WINSIZE_Y - (SIZE_MSG * 2) - (SIZE_MSG * x) - 20 >= 10 + SIZE_MSG + 4)
      displayMsg(sdl, sdl->chat->msgs[y], 50, WINSIZE_Y - (SIZE_MSG * 2) - (SIZE_MSG * x) - 20);
    y++;
    x--;
  }
  displayMsg(sdl, sdl->msg, (WINSIZE_X / 2) - (sdl->channel->w / 2) + 40, WINSIZE_Y - SIZE_MSG);
}

void            display_render(t_sdl_game *sdl)
{
  SDL_Texture   *texture;

  texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->screen);
  SDL_RenderCopy(sdl->renderer, texture, NULL, NULL);
  SDL_RenderPresent(sdl->renderer);
  blit_background(sdl);
}

void            display_overlays(t_sdl_game *sdl)
{
  SDL_Rect    location = { WINSIZE_X / 2 - (sdl->channel->w / 2), WINSIZE_Y - SIZE_MSG * 2, WINSIZE_X, WINSIZE_Y };
  SDL_Rect    location2 = { 0, 0, sdl->channel->w, SIZE_MSG * 2 };

  SDL_BlitSurface(sdl->channel, &location2, sdl->screen, &location);
  location.x = -10;
  location.y = 0;
  location.w = WINSIZE_X;
  location.h = WINSIZE_Y;
  location2.x = 0;
  location2.y = sdl->channel->h - SIZE_MSG * 2;
  location2.w = sdl->channel->w * RATIO_CHANNEL;
  location2.h = sdl->channel->h;
  SDL_BlitSurface(sdl->channel, &location2, sdl->screen, &location);
  location2.x = sdl->channel->w - (sdl->channel->w * RATIO_CHANNEL);
  location2.y = sdl->channel->h - SIZE_MSG * 2;
  location2.w = sdl->channel->w;
  location2.h = sdl->channel->h;
  location.x = sdl->channel->w * RATIO_CHANNEL - 10;
  SDL_BlitSurface(sdl->channel, &location2, sdl->screen, &location);
}

void            displayer(t_sdl_game *sdl)
{
  display_overlays(sdl);
  display_chat(sdl);
  display_channels(sdl);
  display_render(sdl);
}

void            manage_client_side(t_sdl_game *sdl, int ret, bool connected)
{
    if (ret == FATAL_ERROR || ret == EXIT)
      sdl->quit = true;
    else if (ret == SUCCESS)
    {
      if (sdl->msg[0] == '/' && sdl->client
        && strncmp(sdl->msg, "/join", 4) == 0)
      {
        send_message(sdl->client->fd, "active");
      }
    }
    else
    {
      sdl->chat->msgs[sdl->chat->hist] = get_error(ret);
      sdl->chat->hist++;
    }
    if (sdl->client != NULL && !connected)
    {
      pthread_create(&sdl->client->reader, NULL, read_stdin, sdl);
      connected = true;
    }
}

int             cmd_return(t_sdl_game *sdl)
{
  static bool   connected = false;
  char          *command;
  int           ret;

  sdl->modif = true;
  command = strdup(sdl->msg);
  if (check_validity(&command))
  {
    ret = manage_commands(command, &sdl->client);
    manage_client_side(sdl, ret, connected);
  }
  else
  {
    sdl->chat->msgs[sdl->chat->hist] = get_error(BAD_COMMAND);
    sdl->chat->hist++;
  }
  init_msg(sdl);
  if (load_music(sdl, SEND_SOUND) == false)
    return (FATAL_ERROR);
  return (SUCCESS);
}

void            cmd_backspace(t_sdl_game *sdl)
{
  sdl->modif = true;
  sdl->msg_len--;
  if (sdl->msg_len >= 0)
    sdl->msg[strlen(sdl->msg) - 1] = '\0';
}

void            cmd_textinput(t_sdl_game *sdl)
{
  if (strlen(sdl->msg) != MAX_MSG)
  {
    sdl->modif = true;
    strcat(sdl->msg, sdl->event.text.text);
    sdl->msg_len++;
  }
}

void            manage_events(t_sdl_game *sdl)
{
  if (sdl->event.type == SDL_QUIT)
    sdl->quit = true;
  if (sdl->event.type == SDL_TEXTINPUT)
    cmd_textinput(sdl);
  if (sdl->event.type == SDL_TEXTEDITING)
  {
    composition = sdl->event.edit.text;
    cursor = sdl->event.edit.start;
    selection_len = sdl->event.edit.length;
  }
}

int         manage_keydown(t_sdl_game *sdl)
{
  if (sdl->event.type == SDL_KEYDOWN)
  {
    if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
      sdl->quit = true;
    if (sdl->event.key.keysym.sym == SDLK_RETURN)
      return (cmd_return(sdl));
    if (sdl->event.key.keysym.sym == SDLK_BACKSPACE)
      cmd_backspace(sdl);
  }
  return (SUCCESS);
}

int            manage_input(t_sdl_game *sdl)
{
  while (SDL_PollEvent(&sdl->event))
  {
    manage_events(sdl);
    manage_keydown(sdl);
  }
  return (SUCCESS);
}

int             sdl_game()
{
  t_sdl_game    *sdl;

  if (!(sdl = init_all()))
    return (-1);

  SDL_StartTextInput();
  while (!sdl->quit)
  {
    manage_input(sdl);
    if (sdl->modif)
      displayer(sdl);
    if (sdl->modif && sdl->finished)
      sdl->modif = false;
  }

  free_sdl(sdl);
  return (0);
}

int     main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  return (sdl_game());
}
