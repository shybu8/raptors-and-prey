.PHONY = clean

all:
	gcc main.c -lraylib -o raptor-and-prey

run: all
	./raptor-and-prey

clean:
	rm raptor-and-prey

