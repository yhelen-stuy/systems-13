all:
	gcc -o pipeit pipe.c

run: all
	./pipeit

clean:
	rm pipeit
