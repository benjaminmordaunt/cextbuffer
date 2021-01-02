/* Description:
 * 	The header file corresponding to extbuffer.c
 * Author:
 * 	Benjamin Mordaunt
 * Date:
 * 	02/01/2021
 */

#ifndef _H_EXTBUFFER
#define _H_EXTBUFFER

#define CEXTARG(x) x, (sizeof x)
#define CEXTGET(buf, idx, type) *((type*)ceb_get_object(buf, idx))

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#endif /* _H_EXTBUFFER */
