TARGET = sysled
CC = gcc
CFLAGS = -g -Wall
HEADERS = power_device.h
OBJS = power_device.o sysled.o

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -Wall -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: clean
