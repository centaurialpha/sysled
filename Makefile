.POSIX:

SRC = sysled.c
OBJ = $(SRC:.c=.o)
PREFIX = ~/.local

.c.o:
	$(CC) $(STCFLAGS) -c $<

sysled: $(OBJ)
	$(CC) -o $@ $(OBJ) $(STLDFLAGS)

clean:
	rm -f sysled $(OBJ)

install: sysled
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f sysled $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/sysled

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/sysled

.PHONY: all clean install uninstall
