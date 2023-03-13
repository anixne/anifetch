CC=gcc
FLAGS=-g -lm
BINDIR=bin
SRCDIR=src
MAIN=main
SOURCE=$(shell find $(SRCDIR) -type f -name '*.c')

all: always $(MAIN)

main: $(SOURCE)
	$(CC) $(FLAGS) $(SOURCE) -o $(BINDIR)/$(MAIN)

always:
	mkdir -p $(BINDIR)

run:
	$(BINDIR)/$(MAIN)

debug:
	gdb $(BINDIR)/$(MAIN)

clean:
	rm -rf $(BINDIR)
