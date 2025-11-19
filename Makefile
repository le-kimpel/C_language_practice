CC = clang
CFLAGS = -std=gnu99 -ggdb
UNAME_M := $(shell uname -m)

little_fella.so:
	$(CC) $(CFLAGS) -D_GNU_SOURCE -shared -o little_fella.so -fPIC so/little_fella.c

target:
	$(CC) $(CFLAGS) -o target src/target.c


clean:
	rm -f target
	rm -f little_fella.so
