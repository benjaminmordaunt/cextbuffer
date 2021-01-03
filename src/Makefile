all:
	$(CC) -Wall -Wpedantic -Werror -std=c99 -I"../include" extbuffer.c -c -o ../build/out/extbuffer.o
	ar crs ../build/lib/libextbuffer.a ../build/out/extbuffer.o
