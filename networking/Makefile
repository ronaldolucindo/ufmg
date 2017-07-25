all: cliente servidor
CC = gcc

CFLAGS = -Wall -g

RM = rm -fr

OBJS = utils.o cliente.o 

MAIN = cliente

OBJS2 = utils.o servidor.o time.o

MAIN2 = servidor

cliente: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lm -o cliente

servidor: $(OBJS2)
	@$(CC) $(CFLAGS) $(OBJS2) -lm -o servidor
	

%.o: %.c %.h
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	$(RM) $(MAIN2) *.o
	clear


