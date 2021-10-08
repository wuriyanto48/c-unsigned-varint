.PHONY : build clean

CC=gcc
PROGRAM_NAME='app'
SOURCE='main.c'

build:
	$(CC) $(SOURCE) -o $(PROGRAM_NAME)

clean:
	rm -f $(PROGRAM_NAME)