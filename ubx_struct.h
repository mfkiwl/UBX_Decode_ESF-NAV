#ifndef _UBX_HEADER_H_
#define _UBX_HEADER_H_

#include <stdint.h>
#include <stdio.h>

#define UBX_SYNC_1           0xB5
#define UBX_SYNC_2           0x62
#define UBX_NAV_CLASS        0x01
#define UBX_NAV_AOPSTATUS    0x60

#define HEADER_LENGTH        6
#define SYNC_LENGTH          2
#define CHECKSUM_LENGTH      2

/* UBX protocol header struct. No alignment gaps. */
struct ubx_header {
	uint8_t sync[2];
	uint8_t klass;
	uint8_t id;
	uint16_t length;
};

/* UBX packet struct. Pointer members. */
struct ubx_packet {
	struct ubx_header *header;
	uint8_t *payload;
	uint8_t *checksum;
};

void compute_checksum(struct ubx_header *header, uint8_t *payload, int length, uint8_t results[CHECKSUM_LENGTH]);
int is_ubx(struct ubx_header *header);
int is_checksum_equal(uint8_t checksum[CHECKSUM_LENGTH], uint8_t results[CHECKSUM_LENGTH]);
void fprint_header(FILE *fp, struct ubx_header *header);
void fprint_payload(FILE *fp, uint8_t *payload, uint16_t length);
void fprint_checksum(FILE *fp, uint8_t checksum[CHECKSUM_LENGTH]);
void fprint_esf_means(FILE *fp, uint32_t timeTag, uint16_t data_type, float float_data);
void fpring_float_data(FILE *p, double float_data);
void fprint_nav_pvt(FILE *fp, uint32_t iTOW, int32_t dataPrint);
void ubx2p754(uint64_t *p, double *tempNum);

#endif