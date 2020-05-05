NAME	= philo

CC	= gcc

RM	= rm -f

SRCS	= ./src/main.c 

OBJS	= $(SRCS:.c=.o)

LDFLAGS = -L./lib/ -lriceferee -lpthread
CFLAGS = -I./inc/ -I./lib/
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
