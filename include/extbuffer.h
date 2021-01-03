/* Description:
 * 	The header file corresponding to extbuffer.c
 * Author:
 * 	Benjamin Mordaunt
 * Date:
 * 	02/01/2021
 */

#ifndef _H_EXTBUFFER
#define _H_EXTBUFFER

#define CEXTPUT(buf, x) ceb_append_object(buf, &x, (sizeof x))
#define CEXTGET(buf, idx, type) *((type*)ceb_get_object(buf, idx))

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Types */

typedef struct ceb_buffer_sz {
	size_t sz;
	size_t used_sz;
	size_t *buf;
	int rsz_ratio;
} _ceb_buffer_sz_t;

typedef struct ceb_buffer {
	size_t sz;              // Size of this buffer in multiples of sizeof(char)
        size_t used_sz;         // Occupied contiguous space inside this buffer.
	char *buf;              // Beginning of the memory region where this buffer is stored.
	_ceb_buffer_sz_t types; // Similar buffer structure designed only to contain sequential type sizes as they are contained within this buffer.
	int rsz_ratio;          // Ratio /100 when the buffer should be resized.
} ceb_buffer_t;

/* Functions */

char ceb_init_buffer(ceb_buffer_t *buf, size_t init_sz);
char ceb_append_object(ceb_buffer_t *buf, void *obj_ref, size_t sz);
char *ceb_get_object(ceb_buffer_t *buf, size_t idx);
char ceb_remove_object(ceb_buffer_t *buf, size_t idx);
char ceb_free_buffer(ceb_buffer_t *buf);

#endif /* _H_EXTBUFFER */
