
CC = gcc
FLAGS = -std=c99 -Wall -Werror -g -pedantic

default:
	$(CC) $(FLAGS) *.c -o aes_out

clean:
	rm -f *_out
