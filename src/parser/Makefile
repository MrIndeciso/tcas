OBJS	= parser.o rpn_parser.o test.o util.o ../xml/xml.o
SOURCE	= parser.c rpn_parser.c test.c util.c ../xml/xml.c
HEADER	= parser.h rpn_parser.h util.h ../xml/xml.h ../types/tokenizer_structs.h ../types/parser_structs.h ../types/parser_enums.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

parser.o: parser.c
	$(CC) $(FLAGS) parser.c 

rpn_parser.o: rpn_parser.c
	$(CC) $(FLAGS) rpn_parser.c 

test.o: test.c
	$(CC) $(FLAGS) test.c 


clean:
	rm -f $(OBJS) $(OUT)
