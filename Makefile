.POSIX:

SRC = sysled.c
OBJ = $(SRC:.c=.o)
PREFIX = ~/.local

sysled: $(OBJ)
	$(CC) -o $@ $(OBJ) $(STLDFLAGS)

clean:
	rm -f sysled $(OBJ)
