##
## Makefile for makefile in /home/tekm/tek2/PSU_2016_myirc
## 
## Made by leroy_0
## Login   <maxime.leroy@epitech.eu>
## 
## Started on  Mon May 22 18:49:50 2017 leroy_0
## Last update Wed Jun  7 19:48:05 2017 yan
##

all: server client

server:
	make -C servers/

client:
	make -C clients/

graphical:
	make -C bonus/

$(SERVER):
	make -C servers/

$(CLIENT):
	make -C clients/

$(GRAPHICAL):
	make -C bonus/

clean:
	make clean -C servers/
	make clean -C clients/
	make clean -C bonus/

fclean:
	make fclean -C servers/
	make fclean -C clients/
	make fclean -C bonus/

re:
	make re -C servers/
	make re -C clients/

.PHONY: all clean fclean re
