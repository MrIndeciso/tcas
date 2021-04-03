OBJS	= parser.o rpn_parser.o test.o util.o xml.o rpn_defs.o tokenizer.o
SOURCE	= parser.c rpn_parser.c test.c util.c ../xml/xml.c rpn_defs.c ../tokenizer/tokenizer.c
HEADER	= parser.h rpn_parser.h util.h rpn_defs.h ../xml/xml.h ../types/tokenizer_structs.h ../types/parser_structs.h ../types/parser_enums.h ../tokenizer/tokenizer.h
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

util.o: util.c
	$(CC) $(FLAGS) util.c

xml.o: ../xml/xml.c
	$(CC) $(FLAGS) ../xml/xml.c

rpn_defs.o: rpn_defs.c
	$(CC) $(FLAGS) rpn_defs.c

tokenizer.o: ../tokenizer/tokenizer.c
	$(CC) $(FLAGS) ../tokenizer/tokenizer.c

clean:
	rm -f $(OBJS) $(OUT)
	rm -f *.xml
