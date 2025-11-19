CC := gcc
CFLAGS := -Wall

# src
SRC := $(*.c)
OBJ := $(SRC:.c=.o)

TARGETS := target

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)
