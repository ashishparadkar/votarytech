default: program

program.o: program.c
	gcc -c program.c -o program.o
	echo ".o created"
program: program.o
	gcc program.o -o program

clean:
	rm -f program.o
	rm -f program

	

