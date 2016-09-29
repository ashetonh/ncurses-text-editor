CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -Wall -std=c++11 -c $(NCURSES) $(DEBUG)
LFLAGS = -Wall $(NCURSES) $(DEBUG)
NCURSES = -lncurses

all: editor

editor: editor.o Text.o
	$(CC) $(LFLAGS) -o editor editor.o Text.o

editor.o: editor.cpp Text.h
	$(CC) $(CFLAGS) editor.cpp
Text.o: Text.cpp Text.h
	$(CC) $(CFLAGS) Text.cpp
.PHONY: clean


clean: 
	rm -rf *.o
	rm -rf editor