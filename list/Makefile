CFLAGS = -Wall -g
LDLIBS= -lpthread

.PHONY: all clean

all: main 

main: main.o list.o th_list.o

main.o: main.c list.h th_list.h

list.o: list.c list.h

th_list.o: th_list.c th_list.h

clean:
	-rm -f main 
	-rm -f list.o main.o th_list.o
	-rm -f *~