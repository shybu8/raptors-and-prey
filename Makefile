.PHONY = clean

NAME := raptors-and-prey

all:
	gcc main.c -Wall -Wpedantic -ggdb -lraylib -o ${NAME}

run: all
	./${NAME}

clean:
	rm ${NAME}

