CC = gcc
flags = -O3

build/main: escuchar.c identificar.c message.c main.c
			${CC} ${flags} $^ -o $@

clean: 
	rm -rf build/*