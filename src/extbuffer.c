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

#define CEXTARG(x) x, (sizeof x)
#define CEXTGET(buf, idx, type) *((type*)ceb_get_object(buf, idx))

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct ceb_buffer_sz {
	size_t sz;
	size_t used_sz;
	size_t *buf;
	int rsz_ratio;
} _ceb_buffer_sz_t;

typedef struct ceb_buffer {
	size_t sz; 		// Size of this buffer in multiples of sizeof(char)
	size_t used_sz;		// Occupied contiguous space inside this buffer.
	void *buf;		// Beginning of the memory region where this buffer is stored.
	_ceb_buffer_sz_t types; // Similar buffer structure designed only to contain sequential type sizes as they are contained within this buffer.
	int rsz_ratio;          // Ratio /100 when the buffer should be resized.
} ceb_buffer_t;

char ceb_init_buffer(ceb_buffer_t *buf, size_t init_sz) {
	buf->buf = calloc(init_sz, 1);
	buf->used_sz = 0;
	buf->sz = init_sz;
	buf->rsz_ratio = 90;
	
	(buf->types).buf = calloc(20, sizeof(size_t));
	(buf->types).sz = 20 * sizeof(size_t);
	(buf->types).used_sz = 0;
	(buf->types).rsz_ratio = 90;

	return 0;
}

char ceb_append_object(ceb_buffer_t *buf, void *obj_ref, size_t sz) {
	if(buf->sz - buf->used_sz < sz) { return 1; } // In future, this will resize the underlying buffer.
	
	memcpy((void*)((uintptr_t)buf->buf + buf->used_sz), obj_ref, sz); // Note that this assumes that the caller was truthful about size. 
	buf->used_sz += sz;

	// Add type size
	// TODO: Handle case where _ceb_buffer_sz_t runs out of size_t slots
	int cbtb_idx = (buf->types).used_sz / sizeof(size_t);

	(buf->types).buf[cbtb_idx] = sz + (buf->types).buf[cbtb_idx-1];

	return 0;
}

char _ceb_remove_type_sz(_ceb_buffer_sz_t *buf, size_t idx) {
	void *seek_ptr = (void*)((uintptr_t)buf->buf + idx * sizeof(size_t));

	memmove(seek_ptr, (void*)((uintptr_t)seek_ptr + (uintptr_t)sizeof(size_t)), buf->sz - ((uintptr_t)seek_ptr - (uintptr_t)buf->buf));
	buf->used_sz -= sizeof(size_t);
	return 0;
}

void *ceb_get_object(ceb_buffer_t *buf, size_t idx) {
	return 
}

char ceb_remove_object(ceb_buffer_t *buf, size_t idx) {
	void *seek_ptr;
	
	// Get accumulated type length
	seek_ptr = (buf->types).buf[idx]; 

	memmove(seek_ptr, (void*)((uintptr_t)seek_ptr + (uintptr_t)(buf->types).buf[i]), buf->types.sz - ((uintptr_t)seek_ptr - (uintptr_t)buf->buf));
	buf->used_sz -= (buf->types).buf[i];

	// Call to remove corresponding type size
	_ceb_remove_type_sz(&buf->types, idx);
	return 0;
}


