CC=gcc
FLAGS=-Wall -Wextra -pedantic -g

.PHONY: bar

all: liba.so main.c
	$(CC) main.c -L./ -l:liba.so

liba.so: liba.c
	$(CC) -shared liba.c -o liba.so -fPIC $(FLAGS)

bar: liba.so main.c
	@cowsay "I told ya \`bar' is hidden!"
	$(CC) main.c -L./ -l:liba.so -DTRY_BAR
