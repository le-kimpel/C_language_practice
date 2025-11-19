CC = clang
CFLAGS = -std=gnu99 -ggdb
UNAME_M := $(shell uname -m)

all:
	$(MAKE) inject little_fella.so target

inject:
	$(CC) $(CFLAGS) -o inject util/etc.c src/inject.c  -ldl

little_fella.so:
	$(CC) $(CFLAGS) -D_GNU_SOURCE -shared -o little_fella.so -fPIC so/little_fella.c

target:
	$(CC) $(CFLAGS) -o target src/target.c


clean:
	rm target
	rm little_fella.so
	rm inject
