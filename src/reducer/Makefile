OBJS	= reducer.o test.o xml.o tokenizer.o rpn_defs.o util.o parser.o rpn_parser.o
SOURCE	= reducer.c test.c ../xml/xml.c ../tokenizer/tokenizer.c ../parser/rpn_defs.c ../parser/util.c ../parser/parser.c ../parser/rpn_parser.c
HEADER	= reducer.h ../types/parser_enums.h ../types/parser_structs.h ../types/tokenizer_structs.h ../xml/xml.h ../tokenizer/tokenizer.h ../parser/parser.h ../parser/rpn_defs.h ../parser/rpn_parser.h ../parser/util.h
OUT	= test
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

reducer.o: reducer.c
	$(CC) $(FLAGS) reducer.c 

test.o: test.c
	$(CC) $(FLAGS) test.c 

xml.o: ../xml/xml.c
	$(CC) $(FLAGS) ../xml/xml.c 

tokenizer.o: ../tokenizer/tokenizer.c
	$(CC) $(FLAGS) ../tokenizer/tokenizer.c

rpn_defs.o: ../parser/rpn_defs.c
	$(CC) $(FLAGS) ../parser/rpn_defs.c

util.o: ../parser/util.c
	$(CC) $(FLAGS) ../parser/util.c

parser.o: ../parser/parser.c
	$(CC) $(FLAGS) ../parser/parser.c

rpn_parser.o: ../parser/rpn_parser.c
	$(CC) $(FLAGS) ../parser/rpn_parser.c

clean:
	rm -f $(OBJS) $(OUT)
	rm -f *.xml
