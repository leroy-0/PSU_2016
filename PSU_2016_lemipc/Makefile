NAME	= lemipc

CC	= gcc

RM	= rm -f

SRCS	= 	./src/lib.c \
	  	./src/game_init.c \
		./src/map_position_helper.c \
	  	./src/message_manager.c \
	  	./src/utils.c \
	  	./src/launch.c \
	  	./src/lemipc.c \
	  	./src/semaphores.c \
	  	./src/search.c \
	  	./src/attack.c \
	  	./src/alive.c \

SRCS_B 	= 	./src/lib.c \
	  	./src/game_init.c \
	  	./src/launch.c \
		./src/map_position_helper.c \
	      	./src/message_manager.c \
		./src/utils.c \
	  	./src/semaphores.c \
	  	./src/search.c \
	  	./src/alive.c \
	  	./src/attack.c \
	  	./bonus/srcs/lemipc.c \
	  	./bonus/srcs/display.c \
	  	./bonus/srcs/gifs.c \
	  	./bonus/srcs/tools.c \

OBJS	= $(SRCS:.c=.o)

OBJS_B 	= $(SRCS_B:.c=.o)

LDFLAGS = -lSDL2main -lSDL2 -lSDL2_gfx -lSDL2_mixer -lSDL2_image

CFLAGS = -I./inc/

CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

sdl:	fclean	$(OBJS_B)
	$(CC) $(OBJS_B) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
