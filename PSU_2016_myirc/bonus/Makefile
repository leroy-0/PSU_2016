##
## Makefile for graphical in /home/tekm/tek2/PSU_2016_myirc
## 
## Made by leroy_0
## Login   <maxime.leroy@epitech.eu>
## 
## Started on  Mon Jun  5 16:30:43 2017 leroy_0
## Last update Fri Jun  9 18:37:17 2017 leroy_0
##

NAME	= ../graphical

CC	= gcc

RM	= rm -f

SRCS	= ./srcs/client.c \
	  ./srcs/init.c \
	  ./srcs/gifs.c \
	  ./srcs/tools.c \
	  ./srcs/receive.c \
	  ./../clients/src/client.c \
	  ./../clients/src/commands.c \
	  ./../clients/src/commands2.c \
	  ./../clients/src/commands3.c \
	  ./../clients/src/commands4.c \
	  ./../clients/src/fnc_ptrs.c \
	  ./../clients/src/send.c \
	  ./../clients/src/tools.c \
	  ./../common/src/tools.c \
	  ./../common/src/tools2.c \
	  ./../common/src/tools3.c \
	  ./../common/src/error.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS  = -I./include -I./../common/include -I./../clients/include/

CFLAGS  += -W -Wall -Wextra

LDFLAGS = -lSDL2main -lSDL2 -lSDL2_gfx -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
