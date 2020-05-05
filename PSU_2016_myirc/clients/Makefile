##
## Makefile for client in /home/tekm/tek2/PSU_2016_myirc
## 
## Made by leroy_0
## Login   <maxime.leroy@epitech.eu>
## 
## Started on  Wed May 24 15:37:22 2017 leroy_0
## Last update Fri Jun  9 16:24:04 2017 yan
##

NAME	= ../client

CC	= gcc

RM	= rm -f

SRCS	= src/main.c \
	  src/client.c \
	  src/fnc_ptrs.c \
	  src/commands.c \
	  src/commands2.c \
	  src/commands3.c \
	  src/commands4.c \
	  src/tools.c \
	  src/receive.c \
	  src/send.c \
	  ../common/src/error.c \
	  ../common/src/tools.c \
	  ../common/src/tools2.c \
	  ../common/src/tools3.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I./include/ -I../common/include

CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -lpthread

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
