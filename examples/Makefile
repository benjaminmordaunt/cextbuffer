LINK_DIRS := "../build/lib"
LINK_LIB  := extbuffer

../build/examples/simple_test:
	$(CC) -Wall -Wpedantic -Werror -std=c99 -L$(LINK_DIRS) -I"../include" simple_test/simple_test.c -g -O0 -o ../build/examples/simple_test -l$(LINK_LIB)

../build/examples/as_string:
	$(CC) -Wall -Wpedantic -Werror -std=c99 -L$(LINK_DIRS) -I"../include" as_string/as_string.c -g -O0 -o ../build/examples/as_string -l$(LINK_LIB)

.PHONY: clean

clean:
	rm ../build/examples/simple_test ../build/examples/as_string
