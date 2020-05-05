##
## Makefile for Makefile in /home/tekm/tek2/PSU_2016_zappy
## 
## Made by leroy_0
## Login   <maxime.leroy@epitech.eu>
## 
## Started on  Thu Jun 29 16:14:59 2017 leroy_0
## Last update Thu Jun 29 17:08:34 2017 Sebastien
##

all:
	$(MAKE)	-C server/
	$(MAKE) -C client/

server:
	$(MAKE) -C server/

client:
	$(MAKE) -C client/

graphical:
	$(MAKE) -C graphical/

clean:
	$(MAKE) clean -C server/
	$(MAKE) clean -C client/
	$(MAKE) clean -C graphical/

fclean:
	$(MAKE) fclean -C server/
	$(MAKE) fclean -C client/
	$(MAKE) fclean -C graphical/

re:
	$(MAKE) re -C server/
	$(MAKE) re -C client/

.PHONY: all clean fclean re server client graphical
