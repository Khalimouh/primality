CC=gcc
CFLAGS= -g3 -W -Wall 
LDFLAGS= -lgmp
EXEC= prim
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

prim: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper 

run:
	@./prim

clean:
	@rm -rf obj/*.o prim src/*.o

mrproper: clean
	@rm -rf $(EXEC)
