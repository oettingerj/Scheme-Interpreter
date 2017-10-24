CC = clang
CFLAGS = -g

SRCS = linkedlist.c main_parse.c talloc.c tokenizer.c parser.c
HDRS = linkedlist.h value.h talloc.h tokenizer.h parser.h
OBJS = $(SRCS:.c=.o)

parser: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

memtest: tokenizer
	valgrind --leak-check=full --show-leak-kinds=all ./$<

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm tokenizer
