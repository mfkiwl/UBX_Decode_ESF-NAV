#include <stdlib.h>
#include <string.h>

#include "ubx_util.h"

void fprint_hex(FILE *fp, uint8_t data)
{
	if (data <= 0xF)
		fprintf(fp, "0%x", data);
	else
		fprintf(fp, "%x", data);
}

void fprint_hexes(FILE *fp, uint8_t *data, size_t length)
{
	size_t i, j;
	size_t end_cond = length % 4 == 0 ? length / 4 : length / 4 + 1;
	for (i = 0, j = 0; i < end_cond; i++) {
		for (j = 0; j < 4 && i * 4 + j < length; j++) {
			if (data[i * 4 + j] <= 0xF)
				fprintf(fp, "0%x ", data[i * 4 + j]);
			else
				fprintf(fp, "%x ", data[i * 4 + j]);
		}
		if (i == end_cond - 1)
			continue;
		fprintf(fp, "\n");
	}
}

void *ubx_malloc(size_t size)
{
	void *p;
	p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "Cannot malloc: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return p;
}

void ubx_free(void *ptr)
{
	free(ptr);
}

FILE *ubx_fopen(const char *filename, const char *mode)
{
	FILE *fp = fopen(filename, mode);
	if (fp == NULL) {
		fprintf(stderr, "Cannot fopen %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return fp;
}

void ubx_fclose(FILE *stream)
{
	if (fclose(stream) == EOF) {
		fprintf(stderr, "Cannot fclose: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void ubx_fseek(FILE *stream, long offset, int whence)
{
	if (fseek(stream, offset, whence) == -1) {
		fprintf(stderr, "Cannot fseek: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

size_t ubx_fread(void *ptr, size_t size, size_t nitems, FILE *stream)
{
	size_t n;
	n = fread(ptr, size, nitems, stream);
	if (n < nitems && ferror(stream)) {
		fprintf(stderr, "Cannot fread: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return n;
}