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

#include "extbuffer.h"

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
	
	memcpy(buf->buf + buf->used_sz, obj_ref, sz); // Note that this assumes that the caller was truthful about size. 
	buf->used_sz += sz;

	// Add type size
	// TODO: Handle case where _ceb_buffer_sz_t runs out of size_t slots
	int cbtb_idx = (buf->types).used_sz / sizeof(size_t);

	(buf->types).buf[cbtb_idx+1] = sz + (buf->types).buf[cbtb_idx];

	return 0;
}

char _ceb_remove_type_sz(_ceb_buffer_sz_t *buf, size_t idx) {
	size_t *seek_ptr = buf->buf + idx + 1;

	memmove(seek_ptr, seek_ptr + 1, buf->sz - (seek_ptr + 1 - buf->buf));
	buf->used_sz -= sizeof(size_t);
	return 0;
}

char *ceb_get_object(ceb_buffer_t *buf, size_t idx) {
	char *obj_ref = buf->buf + (buf->types).buf[idx];	 
	return obj_ref;
}

char ceb_remove_object(ceb_buffer_t *buf, size_t idx) {
	char *seek_ptr;
	
	// Get accumulated type length
	seek_ptr = buf->buf + (buf->types).buf[idx]; 

	// Calculate type length from accumulated lengths
	size_t t_len = (buf->types).buf[idx+1] - (buf->types).buf[idx];

	memmove(seek_ptr, seek_ptr + t_len, buf->sz - (seek_ptr + t_len - buf->buf));
	buf->used_sz -= t_len;

	// Call to remove corresponding type size
	_ceb_remove_type_sz(&buf->types, idx);
	return 0;
}

char ceb_free_buffer(ceb_buffer_t *buf) {
	free(buf->buf);
	free((buf->types).buf);

	return 0;
}
