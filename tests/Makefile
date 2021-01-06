LINKER_FLAGS := -L"../build/lib" -lextbuffer $(shell pkg-config --libs check)
CC_FLAGS     := -std=c99 -O2 -I"../include" $(shell pkg-config --cflags check)

build/expand:
	$(CC) $(CC_FLAGS) expand/expand.c -o $@ $(LINKER_FLAGS)

all:
	mkdir build
	$(MAKE) build/expand
