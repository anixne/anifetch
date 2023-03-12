CC=clang
FLAGS=-g
BINDIR=bin
SRCDIR=src
MAIN=main
SOURCE=$(shell find $(SRCDIR) -type f -name '*.c')

all: always $(MAIN)

main: $(SOURCE)
	$(CC) $(FLAGS) $(SOURCE) -o $(BINDIR)/$(MAIN)

always:
	mkdir -p bin

run:
	$(BINDIR)/$(MAIN)

debug:
	gdb $(BINDIR)/$(MAIN)

clean:
	rm -rf bin