CC = gcc
LINKER = gcc
CFLAGS = -std=gnu11 -Wall -Wpointer-arith -Wfatal-errors -lm
DEBUG = -g
MATH = -lm
PROG1LIBNAME = prog1
PROG1LIBDIR = ../prog1lib/lib

SOURCES=$(wildcard *.c)
BINARIES=$(SOURCES:.c=)

# disable default suffixes
.SUFFIXES:

# pattern rule for compiling the library
prog1lib:
	cd $(PROG1LIBDIR) && make

all: $(BINARIES)

# pattern rule for compiling .c-file to executable
%: %.c prog1lib
	$(CC) $(CFLAGS) $(DEBUG) $< -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -iquote$(PROG1LIBDIR) -o $@ $(MATH)

.PHONY: clean
clean:
	rm -f $(BINARIES)
