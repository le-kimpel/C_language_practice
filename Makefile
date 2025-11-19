CC := gcc
CFLAGS := -Wall

# src
SRC := $(src/*.c)
OBJ := $(SRC:.c=.o)

TARGETS := target

%: %.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)
