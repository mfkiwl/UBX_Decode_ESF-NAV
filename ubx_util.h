#ifndef _UBX_UTIL_H_
#define _UBX_UTIL_H_

#include <stdio.h>
#include <stdint.h>

void sprint_hex(char *buf, uint8_t data);
void fprint_hex(FILE *fp, uint8_t data);
void sprint_hexes(char *buf, uint8_t *data, size_t length);
void fprint_hexes(FILE *fp, uint8_t *data, size_t length);
void *ubx_malloc(size_t size);
void ubx_free(void *ptr);
FILE *ubx_fopen(const char *filename, const char *mode);
void ubx_fclose(FILE *stream);
void ubx_fseek(FILE *stream, long offset, int whence);
size_t ubx_fread(void *ptr, size_t size, size_t nitems, FILE *stream);
void fprintf__detials_data(FILE *fp, uint64_t *data, size_t length);
#define ubx_fread_in_loop(ptr, size, nitems, stream)\
{\
	ubx_fread(ptr, size, nitems, stream); \
	if (feof(stream))\
		break; \
}

#endif