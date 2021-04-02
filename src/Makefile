OBJS	= tcas.o test.o
SOURCE	= tcas.c test.c
HEADER	= tcas.h types/tcas_structs.h types/tcas_enums.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

tcas.o: tcas.c
	$(CC) $(FLAGS) tcas.c -std=c99

test.o: test.c
	$(CC) $(FLAGS) test.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)
