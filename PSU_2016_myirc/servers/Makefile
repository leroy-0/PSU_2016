##
## Makefile for myftp in /home/yan/Documents/psu/PSU_2016_myftp
## 
## Made by yan
## Login   <yan.poinssot@epitech.eu>
## 
## Started on  Wed May 10 14:11:10 2017 yan
## 
## Last update Fri Jun  9 18:34:22 2017 yan
##

NAME		=	../server

CC		=	gcc

RM		=	rm -f

SRCS		=	./src/main.c \
			./src/server.c \
			./src/client.c \
			./src/exec.c \
			./src/channel.c \
			./src/msg.c \
			./src/manage.c \
			./src/commands.c \
			./src/commands2.c \
			./src/commands3.c \
			./src/commands4.c \
			./src/fnc_ptrs.c \
			../common/src/buffer.c \
			../common/src/buffer2.c \
			../common/src/error.c \
			../common/src/tools.c \
			../common/src/tools2.c \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-I./include/ -I./../common/include/

CFLAGS		+=	-W -Wall -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
