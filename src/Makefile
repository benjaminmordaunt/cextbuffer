all:
	$(CC) -Wall -Wpedantic -Werror -std=c99 -I"../include" extbuffer.c -c -O0 -g -o ../build/out/extbuffer.o
	ar crs ../build/lib/libextbuffer.a ../build/out/extbuffer.o

.PHONY: clean

clean:
	rm ../build/lib/libextbuffer.a ../build/out/extbuffer.o
