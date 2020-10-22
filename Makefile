# flags for compiling a .o file
OFLAGS = -Wall -std=c99 -pedantic -o $@ -c -g

all: test

test: list.o test.o
	gcc -Wall -std=c99 -pedantic -o $@ -g list.o test.o

# .o files
list.o:
	gcc $(OFLAGS) list.c

test.o:
	gcc $(OFLAGS) test.c -DLIST

# clean
clean: 
	rm *.o test