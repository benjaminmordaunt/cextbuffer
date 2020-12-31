/* Description:
 * 	This file implements a simple extending and relocating buffer.
 * 	Objects may be added to the buffer and remain contiguous or aligned through configuration.
 * Author:
 * 	Benjamin Mordaunt
 * Date:
 * 	31/12/2020
 */

#ifndef CEXTBUFFER_ALIGN
	#define CEXTBUFFER_ALIGN 1
#endif /* CEXTBUFFER_ALIGN */

#define CEXTARG(x) x, sizeof(x)

#include <stdlib.h>

typedef struct ceb_buffer_sz {
	size_t sz;
	size_t used_sz;
	size_t *sz_buf;
	int rsz_ratio;
} _ceb_buffer_sz_t;

typedef struct ceb_buffer {
	size_t sz; 		// Size of this buffer in multiples of sizeof(char)
	size_t used_sz;		// Occupied contiguous space inside this buffer.
	void *buf;		// Beginning of the memory region where this buffer is stored.
	_ceb_buffer_sz_t types; // Similar buffer structure designed only to contain sequential type sizes as they are contained within this buffer.
	int rsz_ratio;          // Ratio /100 when the buffer should be resized.
} ceb_buffer_t;

char ceb_append_object(ceb_buffer_t *buf, void *obj_ref, size_t sz) {
	if(buf->sz - buf->used_sz < sz) { return 1; } // In future, this will resize the underlying buffer.
	
	/* NOTE: memcpy not used here as sizes pre-verified */	
	*(buf->buf + buf->used_sz) = *obj_ref; // Note that this assumes that the caller was truthful about size. 
	buf->used_sz += sz;

	// Add type size
	// TODO: Handle case where _ceb_buffer_sz_t runs out of size_t slots
	int cbtb_idx = (buf->types).used_sz / sizeof(size_t);
	(buf->types).sz_buf[cbtb_idx] = sz;
	return 0;
}

char ceb_remove_object(ceb_buffer_t *buf, void *obj_ref, size_t sz) { // Size argument to accommodate CEXTARG macro
	// NOTE: This function assumes that the value of *obj_ref has not changed since adding to buffer. TODO Add indexing
	
	// Iterate through type lengths
	for(int i = 0; 1; i++) {
		size_t jmplen = (buf->types).sz_buf[i];
	}
}


