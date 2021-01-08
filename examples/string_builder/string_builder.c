#include <stdio.h>
#include <string.h>
#include "extbuffer.h"

int main() {
	char *my_string = "Hello, World!";

	ceb_buffer_t buf = {0};

	ceb_init_buffer(&buf, 20);

	memcpy(buf.buf, my_string, 13); // Sentinel character already in buffer.


}
