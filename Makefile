CC = gcc
CFLAGS = -Wall -Wextra

SRCDIR = src

ENC = $(SRCDIR)/encode.c $(SRCDIR)/file.c $(SRCDIR)/list.c
DEC = $(SRCDIR)/decode.c $(SRCDIR)/file.c

TARGET = enc dec

all: $(TARGET)

enc: $(ENC)
	$(CC) $(CFLAGS) -o $@ $^

dec: $(DEC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
