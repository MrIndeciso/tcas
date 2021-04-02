OBJS	= test.o tokenizer.o
SOURCE	= test.c tokenizer.c
HEADER	= tokenizer.h ../types/tokenizer_structs.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

test.o: test.c
	$(CC) $(FLAGS) test.c -std=c99

tokenizer.o: tokenizer.c
	$(CC) $(FLAGS) tokenizer.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)
