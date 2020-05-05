NM_NAME	= my_nm

OBJ_NAME= my_objdump

CC	= gcc

RM	= rm -f

SRCS_NM	= ./src_nm/nm.c \
	  ./src_nm/print.c \
	  ./src_nm/init.c \
	  ./src_nm/types.c \
	  ./src_obj/print.c \
	  ./src_obj/manager.c \
	  ./src_obj/options.c \
	  ./src_obj/flags.c \
	  ./src_obj/objdump_ar.c \
	  ./src_obj/tools.c \
	  ./lib/fill.c \
	  ./lib/print.c \
	  ./lib/version.c \
	  ./lib/read.c \

SRCS_OBJ= ./src_obj/objdump.c \
	  ./src_obj/tools.c \
	  ./src_obj/print.c \
	  ./src_obj/manager.c \
	  ./src_obj/options.c \
	  ./src_obj/flags.c \
	  ./src_obj/objdump_ar.c \
	  ./lib/fill.c \
	  ./lib/print.c \
	  ./lib/version.c \
	  ./lib/read.c \

OBJS_NM	= $(SRCS_NM:.c=.o)

OBJS_OBJ= $(SRCS_OBJ:.c=.o)

CFLAGS = -I./inc/
CFLAGS += -W -Wall -Wextra -g

all: $(NM_NAME) $(OBJ_NAME)

nm: $(NM_NAME)

objdump: $(OBJ_NAME)

$(NM_NAME):  $(OBJS_NM)
	  $(CC) $(OBJS_NM) -o $(NM_NAME)

$(OBJ_NAME):  $(OBJS_OBJ)
	  $(CC) $(OBJS_OBJ) -o $(OBJ_NAME)

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_OBJ)

fclean: clean
	$(RM) $(NM_NAME)
	$(RM) $(OBJ_NAME)

re: fclean all

.PHONY: all clean fclean re nm objdump
