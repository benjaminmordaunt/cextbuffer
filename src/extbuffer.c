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
	
	(buf->types).buf = calloc(init_sz / 4, sizeof(size_t));
	(buf->types).sz = (init_sz / 4) * sizeof(size_t);
	(buf->types).used_sz = 0;
	(buf->types).rsz_ratio = 90;

	return 0;
}

char _ceb_type_sz_expand(_ceb_buffer_sz_t *buf) {
	size_t *new_mem = realloc(buf->buf, buf->sz * 2);
	// Zero initialisation not required for sz buffer.
	if (new_mem) {
		buf->buf = new_mem;
		buf->sz *= 2;
		return 0;
	}	
	return -1;
}

char ceb_append_object(ceb_buffer_t *buf, void *obj_ref, size_t sz) {
	if(buf->sz - buf->used_sz < sz) { return 1; } // In future, this will resize the underlying buffer.
	
	memcpy(buf->buf + buf->used_sz, obj_ref, sz); // Note that this assumes that the caller was truthful about size. 
	buf->used_sz += sz;


	if(100 * ((buf->types).used_sz + sizeof(size_t)) > (buf->types).rsz_ratio * (buf->types).sz)
		_ceb_type_sz_expand(buf->types);	

	// Add type size
	int cbtb_idx = (buf->types).used_sz / sizeof(size_t);

	(buf->types).buf[cbtb_idx+1] = sz + (buf->types).buf[cbtb_idx];
	(buf->types).used_sz += sizeof(size_t);

	return 0;
}

char _ceb_remove_type_sz(_ceb_buffer_sz_t *buf, size_t idx) {
	size_t *seek_ptr = buf->buf + idx + 1;

	memmove(seek_ptr, seek_ptr + 1, buf->sz - ((char*)seek_ptr - (char*)buf->buf + sizeof(size_t)));
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
