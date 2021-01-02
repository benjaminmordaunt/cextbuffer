#include "../../include/extbuffer.h"
#include <assert.h>

int main() {
	size_t initial_buffer_size = 20; // (20 chars)

	float a = 0.4f;
	unsigned short b = 2;
	unsigned char c = 1;

	// Create a new buffer
	ceb_buffer_t buffer;
	
	// Initialise the buffer
	ceb_init_buffer(&buffer, initial_buffer_size);

	// Add our arbitrarily sized objects using the CEXTARG macro
	ceb_append_object(&buffer, CEXTARG(a));
	ceb_append_object(&buffer, CEXTARG(b));
	ceb_append_object(&buffer, c, sizeof c); // Alternative syntax

	// Remove the 'b' object by index
	ceb_remove_object(&buffer, 1);

	// Assert that the used buffer size is now sizeof(a) + sizeof(c)
	assert(buffer.used_sz == (sizeof a) + (sizeof c));

	// Get 'c', which is now located at index 1.
	unsigned char c_get = CEXTGET(&buffer, 1, unsigned char);
	assert(c_get == c);

	// Free buffer once no longer needed.
	ceb_free_buffer(&buf);

	return 0;
}
