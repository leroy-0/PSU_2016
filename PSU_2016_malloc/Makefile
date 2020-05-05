NAME	= libmy_malloc.so

CC	= gcc

RM	= rm -f

SRCS	= ./src/lib.c \
	  ./src/malloc.c \
	  ./src/free.c \
	  ./src/realloc.c \
	  ./src/show_alloc_mem.c \
	  ./src/block.c \
	  ./src/tools.c \
	  ./src/calloc.c \

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I./inc/
CFLAGS += -W -Wall -Wextra -fPIC

all: $(NAME)

$(NAME):  $(OBJS)
	  $(CC) -shared -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
