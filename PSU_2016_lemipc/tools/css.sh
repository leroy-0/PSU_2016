#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

make re > /dev/null

./tools/clean.sh > /dev/null

if      [ -f "lemipc" ]
then
    echo -e "${GREEN}Launching deathmatch...${NC}"
else
    echo -e "${RED}Please fix your makefile errors${NC}"
    exit 84
fi

./lemipc ~/.bashrc 1 &
./lemipc ~/.bashrc 1 &
./lemipc ~/.bashrc 1 &
./lemipc ~/.bashrc 1 &
./lemipc ~/.bashrc 1 &

./lemipc ~/.bashrc 2 &
./lemipc ~/.bashrc 2 &
./lemipc ~/.bashrc 2 &
./lemipc ~/.bashrc 2 &
./lemipc ~/.bashrc 2 &

make fclean > /dev/null
make sdl > /dev/null

./lemipc ~/.bashrc

make fclean > /dev/null