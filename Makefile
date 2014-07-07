
CC = gcc
FLAGS = -std=c99 -Wall -Werror -g -pedantic

default:
	$(CC) $(FLAGS) *.c -o aes_out

test: default
	./tests.py aes_out
	make clean > /dev/null

clean:
	rm -f *_out tests/*.out
