##
## Makefile for zappy in /home/bruere_s/Projets/PSU_2016_zappy/client
## 
## Made by Sebastien
## Login   <sebastien.bruere@epitech.eu>
## 
## Started on  Thu Jun 22 15:50:40 2017 Sebastien
## Last update Fri Jun 30 15:50:21 2017 Sebastien
##

NAME		=	../zappy_ai

CC		=	g++ -g

RM		=	rm -f

SRCS		=	./src/main.cpp			\
			./src/Parser.cpp		\
			./src/Network.cpp		\
			./src/Socket.cpp		\
			./src/Signal.cpp		\
			./src/AI.cpp			\
			./src/Broadcast.cpp		\
			./src/Communication.cpp		\
			./src/CommandSender.cpp		\
			./src/PathFinder.cpp		\
			./src/Incantation.cpp		\
			./src/Inventory.cpp		\
			./src/Vision.cpp		\
			./src/Client.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-g -I ./include/
CPPFLAGS	+=	-W -Wall -Wextra

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
