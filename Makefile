CC = clang
CFLAGS = -g

SRCS = linkedlist.c main.c talloc.c tokenizer.c parser.c interpreter.c
HDRS = linkedlist.h value.h talloc.h tokenizer.h parser.h interpreter.h
OBJS = $(SRCS:.c=.o)

interpreter: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

memtest: tokenizer
	valgrind --leak-check=full --show-leak-kinds=all ./$<

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm linkedlist
	rm talloc
	rm parser
	rm interpreter
