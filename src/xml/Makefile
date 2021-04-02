OBJS	= test.o xml.o
SOURCE	= test.c xml.c
HEADER	= xml.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

test.o: test.c
	$(CC) $(FLAGS) test.c 

xml.o: xml.c
	$(CC) $(FLAGS) xml.c 


clean:
	rm -f $(OBJS) $(OUT)
	rm -f *.xml
