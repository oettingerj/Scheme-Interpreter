CC = clang
CFLAGS = -g

SRCS = linkedlist.c main_tokenize.c talloc.c tokenizer.c
HDRS = linkedlist.h value.h talloc.h tokenizer.h
OBJS = $(SRCS:.c=.o)

tokenizer: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

memtest: tokenizer
	valgrind --leak-check=full --show-leak-kinds=all ./$<

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm tokenizer
