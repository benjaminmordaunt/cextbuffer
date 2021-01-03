/* Description:
 * 	Treat the buffer as a narrow string.
 * Author:
 * 	Benjamin Mordaunt
 * Date:
 * 	03/01/2020
 */

#include "../../include/extbuffer.h"
#include <stdio.h>

int main() {
	char a = 'H', b = 'i', c = '!';

	// Create a new buffer.
	ceb_buffer_t buffer = {0};

	// Initialise the buffer with a size of 4.
	ceb_init_buffer(&buffer, 4);

	// Add the three letters.
	CEXTPUT(&buffer, a);
	CEXTPUT(&buffer, b);
	ceb_append_object(&buffer, CEXTARG(c));

	// Interpret the buffer as a string.
	printf("%s\r\n", buffer.buf);

	// Free the buffer after use.
	ceb_free_buffer(&buffer);

	return 0;
}
