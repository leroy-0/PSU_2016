NAME_S	= server

NAME_C	= client

CC	= gcc

RM	= rm -f

SRCS_S	= ./src/server.c \
	  ./src/init.c \
	  ./src/tools.c \
	  ./src/tools_analyse.c \
	  ./src/active_passive.c \
	  ./src/start.c \
	  ./src/ptrs.c \
	  ./src/get_next_line.c \
	  ./src/cdup_cwd.c \
	  ./src/auth_and_basic.c \
	  ./src/pasv_cmds.c \
	  ./src/list.c \
	  ./src/tools_exec.c \
	  ./src/manage_fd.c \
	  ./src/pwd_quit_delete.c \

OBJS_S	= $(SRCS_S:.c=.o)

SRCS_C	= ./src/client.c \
	  ./src/init.c \
	  ./src/tools.c \
	  ./src/get_next_line.c \

OBJS_C	= $(SRCS_C:.c=.o)

CFLAGS = -I./inc/
CFLAGS += -W -Wall -Wextra

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJS_S)
	 $(CC) $(OBJS_S) -o $(NAME_S)

$(NAME_C): $(OBJS_C)
	 $(CC) $(OBJS_C) -o $(NAME_C)

clean:
	$(RM) $(OBJS_S)
	$(RM) $(OBJS_C)

fclean: clean
	$(RM) $(NAME_S)
	$(RM) $(NAME_C)

re: fclean all

.PHONY: all clean fclean re
