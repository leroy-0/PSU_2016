##
## Makefile for makefile in /home/adrien/rendu/PSU_2016_zappy/server
## 
## Made by Bachelet
## Login   <adrien.bachelet@epitech.eu>
## 
## Started on  Thu Jun 29 22:16:29 2017 Bachelet
## Last update Sun Jul  2 21:59:54 2017 Bachelet
##

NAME	=	../zappy_server

CC	=	gcc -g

RM	=	rm -f

SRCS	=	./src/main.c			\
		./src/parsing_args.c		\
		./src/utils.c			\
		./src/ptr_func.c		\
		./src/usage.c			\
		./src/server_create.c		\
		./src/server_func.c		\
		./src/select_func.c		\
		./src/set_position.c		\
		./src/player.c			\
		./src/player_func.c		\
		./src/buffer.c			\
		./src/team.c			\
		./src/free.c			\
		./src/ptr_func_next.c		\
		./src/check_error_parsing.c	\
		./src/opt_func.c		\
		./src/coma_and_create_map.c	\
		./src/utils_next.c		\
		./src/ptr_cmd.c			\
		./src/ptr_cmd_next.c		\
		./src/ptr_cmd_move.c		\
		./src/gest_command.c		\
		./src/str_func.c		\
		./src/send_func.c		\
		./src/send_graphical.c		\
		./src/look_top.c		\
		./src/look_right.c		\
		./src/look_left.c		\
		./src/look_bottom.c		\
		./src/queue.c			\
		./src/life.c			\
		./src/list_player.c		\
		./src/inventory.c		\
		./src/broadcast.c		\
		./src/get_tile_bottom.c		\
		./src/get_tile_top.c		\
		./src/move_to_direction.c	\
		./src/eggs.c			\
		./src/take_and_set.c		\
		./src/eject.c			\
		./src/make_elevation.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I ./include/
CFLAGS	+=	-W -Wall -Wextra

all :		$(NAME)

$(NAME) :	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean :
		$(RM) $(OBJS)

fclean :	clean
		$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re
