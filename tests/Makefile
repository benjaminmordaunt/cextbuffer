O            := ../build/tests
LINKER_FLAGS := -L"../build/lib" -lextbuffer $(shell pkg-config --libs check)
CC_FLAGS     := -std=c99 -Wall -Wpedantic -Werror -O2 -I"../include" $(shell pkg-config --cflags check)

$O/expand:
	$(CC) $(CC_FLAGS) expand/expand.c -o $@ $(LINKER_FLAGS)

all:
	mkdir -p $O
	$(MAKE) $O/expand

clean:
	rm -r build
