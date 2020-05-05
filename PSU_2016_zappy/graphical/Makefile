NAME	= ../zappy_graphical

CC	= g++

RM	= rm -f

SRCS	= ./src/Game.cpp \
	  ./src/Map.cpp \
	  ./src/Menu.cpp \
	  ./src/Renderer.cpp \
	  ./src/Tile.cpp \
	  ./src/Music.cpp \
	  ./src/TextBox.cpp \
	  ./src/Network.cpp \
	  ./src/Communication.cpp \
	  ./src/Socket.cpp \
	  ./src/main.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I./inc/ -I../server/include/
CPPFLAGS += -W -Wall -Wextra

LDFLAGS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
