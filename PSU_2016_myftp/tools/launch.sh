#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if      [ -f "server" ]
then
	if [ -f "client" ]
	then
    	echo -e "${GREEN}Testing server and client communication...${NC}"
    else
    	echo -e "${RED}Please fix your makefile errors${NC}"
	    exit 84
	fi
else
    echo -e "${RED}Please fix your makefile errors${NC}"
    exit 84
fi

cat tools/commands | netcat $3 $2 > 1
cat tools/commands | netcat $3 $2 > 2
cat tools/commands | netcat $3 $2 > 3
cat tools/commands | netcat $3 $2 > 4
cat tools/commands | netcat $3 $2 > 5
cat tools/commands | netcat $3 $2 > 6

cat tools/commands | netcat ftp.epitech.eu 21 > real
cat 1 | colrm 4  > first
cat real | colrm 4 > second

diff first second

rm 1 2 3 4 5 6 real first second
