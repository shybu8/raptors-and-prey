.PHONY: clean

NAME = raptors-and-prey

all: main.c
	gcc main.c -Wall -Wpedantic -ggdb -lraylib -o ${NAME}

run: all
	./${NAME}

clean:
	rm ${NAME}

