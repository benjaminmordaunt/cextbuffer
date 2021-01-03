LINK_DIRS := "../build/lib"
LINK_LIB  := extbuffer

../build/examples/simple_test:
	$(CC) -Wall -Wpedantic -Werror -std=c99 -L$(LINK_DIRS) -I"../include" simple_test/simple_test.c -o ../build/examples/simple_test -l$(LINK_LIB)
