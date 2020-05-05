/*
** receive.c for receive in /home/tekm/tek2/PSU_2016_myirc
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Mon Jun  5 16:28:11 2017 leroy_0
** Last update Wed Jun  7 18:18:10 2017 yan
*/

#include  <pthread.h>
#include  "graphical.h"
#include  "fnc_ptrs.h"

int             close_client(t_connect **client)
{
  char    *message[] = {"/quit", NULL};

  cmd_quit(message, client);
  return (SUCCESS);
}

t_connect   *create_client(in_addr_t ip, int port)
{
  t_connect *back;
  int   real_t;

  real_t = time(NULL);
  if ((back = init_client(ip, port)) == NULL)
    {
      fprintf(stderr, "Error : Connection failed\n");
      return (NULL);
    }
  while (connect(back->fd, (struct sockaddr *)&back->s,
     sizeof(back->s)) == -1)
    {
      if ((time(NULL) - real_t) >= TIMEOUT)
  return (false);
    }
  return (back);
}

t_chat    *find_prev_channel(t_sdl_game *sdl, char *to_find)
{
  t_chat  *tmp;
  t_chat  *prev;

  prev = sdl->chat;
  tmp = sdl->chat;
  while (tmp)
  {
    if (tmp->channel && strcmp_insensible(tmp->channel, to_find))
    {
      return (prev);
    }
    prev = tmp;
    tmp = tmp->next;
  }
  return (NULL);
}

void      manage_channels(t_sdl_game *sdl, char *to_find)
{
  t_chat  *tmp;
  t_chat  *tmp2;

  tmp = find_prev_channel(sdl, to_find);
  if (sdl->chat->channel && !tmp)
  {
    tmp = init_chat();
    tmp->channel = strdup(to_find);
    tmp->next = sdl->chat;
    sdl->chat = tmp;
  }
  else
  {
    if (tmp)
    {
      if (tmp->next)
      {
        tmp2 = sdl->chat;
        sdl->chat = tmp->next;
        tmp->next = tmp->next->next;
        sdl->chat->next = tmp2;
      }
    }
    else
      sdl->chat->channel = strdup(to_find);
  }
}

void		*read_stdin(void *sdl_game)
{
  bool  channel = false;
  char  *msg;
  char  *buf;
  int   r;
  t_sdl_game  *sdl;
  char        **msgs;

  sdl = sdl_game;
  if ((buf = malloc(sizeof(char) * MAX_PATH)) == NULL)
    return (NULL);
  while (42)
    {
      if ((r = recv(sdl->client->fd, buf, MAX_PATH, 0)) == -1)
  return (NULL);
      sdl->finished = false;
      buf[r] = '\0';
      msg = epur_string(buf);
      if (msg)
      {
        int   x;

        x = 0;
        msgs = my_strtab(msg, "\n");
        while (msgs && msgs[x])
        {
          if (channel)
          {
            manage_channels(sdl, msgs[x]);
            channel = false;
          }
          else
          {
          if (strcmp_insensible("CHANNEL/\r", msgs[x]))
            channel = true;
          else if (!strcmp_insensible("NO_CHANNEL/", msgs[x]))
          {
            sdl->chat->msgs[sdl->chat->hist] = strdup(msgs[x]);
            sdl->chat->hist++;
          }
        }
          x++;
        }
        sdl->modif = true;
        sdl->finished = true;
      }
      if ((buf = malloc(sizeof(char) * MAX_PATH)) == NULL)
        return (NULL);
    }
  return (NULL);
}
