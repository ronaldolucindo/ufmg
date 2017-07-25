CC = gcc

CFLAGS = -Wall -g

RM = rm -fr

OBJS = main.o tree.o 

MAIN = main

$(MAIN): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)
	

%.o: %.c %.h
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	clear

run: $(MAIN)
	./$(MAIN)
