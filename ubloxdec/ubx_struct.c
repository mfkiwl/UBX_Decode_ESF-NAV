#include "ubx_struct.h"
#include "ubx_util.h"

int is_ubx(struct ubx_header *header)
{
	if (header->sync[0] == UBX_SYNC_1 && header->sync[1] == UBX_SYNC_2)
		return 1;
	return 0;
}

void compute_checksum(struct ubx_header *header, uint8_t *payload, int length, uint8_t results[2])
{
	uint8_t ck_a = 0, ck_b = 0;
	int i;
	ck_a += header->klass;
	ck_b += ck_a;
	ck_a += header->id;
	ck_b += ck_a;
	ck_a += (uint8_t)(header->length & 0x00FF);
	ck_b += ck_a;
	ck_a += (uint8_t)((header->length & 0xFF00) >> 8);
	ck_b += ck_a;
	for (i = 0; i < length; i++) {
		ck_a += payload[i];
		ck_b += ck_a;
	}
	results[0] = ck_a;
	results[1] = ck_b;
}

int is_checksum_equal(uint8_t checksum[2], uint8_t results[2])
{
	if (checksum[0] == results[0] && checksum[1] == results[1])
		return 1;
	return 0;
}

void fprint_header(FILE *fp, struct ubx_header *header)
{
	fprintf(fp, "SYNC  CLASS  ID  LENGTH\n");
	fprint_hex(fp, header->sync[0]);
	fprintf(fp, " ");
	fprint_hex(fp, header->sync[1]);
	fprintf(fp, " ");
	fprint_hex(fp, header->klass);
	fprintf(fp, "     ");
	fprint_hex(fp, header->id);
	fprintf(fp, "  ");
	fprint_hex(fp, (uint8_t)(header->length & 0x00FF));
	fprintf(fp, " ");
	fprint_hex(fp, (uint8_t)((header->length & 0xFF00) >> 8));
	fprintf(fp, " (%d)\n", header->length);
}

void fprint_payload(FILE *fp, uint8_t *payload, uint16_t length)
{
	fprintf(fp, "PAYLOAD\n");
	fprint_hexes(fp, payload, length);
	fprintf(fp, "\n");
}

void fprint_checksum(FILE *fp, uint8_t checksum[2])
{
	fprintf(fp, "CK_A  CK_B\n");
	fprint_hex(fp, checksum[0]);
	fprintf(fp, "   ");
	fprint_hex(fp, checksum[1]);
	fprintf(fp, "\n");
}