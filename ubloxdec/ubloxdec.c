#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ubx_struct.h"
#include "ubx_util.h"
#include "ubx_protocol.h"

#define MAXPATH              1024

int main(int argc, char *argv[])
{
	char path[MAXPATH];
	char protocol_name[MAX_PROTOCOL_NAME];
	uint8_t header_buf[BUFSIZ];
	uint8_t checksum[CHECKSUM_LENGTH];
	uint8_t computed_checksum[CHECKSUM_LENGTH];
	uint8_t *payload;
	struct ubx_header *header;
	FILE *data_fp;
	FILE *log;
	
	printf("UBX file path: ");
	scanf("%s", path);
	data_fp = ubx_fopen(path, "rb");
	log = ubx_fopen("log.txt", "w");

	while (!feof(data_fp)) {
		ubx_fread_in_loop(header_buf, SYNC_LENGTH, 1, data_fp);
		header = (struct ubx_header *)header_buf;
		if (!is_ubx(header)) { /* rewind one byte if cannot recongnize two bytes as SYNC */
			ubx_fseek(data_fp, -(SYNC_LENGTH - 1), SEEK_CUR);
			continue;
		}

		ubx_fread_in_loop(header_buf + SYNC_LENGTH, HEADER_LENGTH - SYNC_LENGTH, 1, data_fp);
		payload = (uint8_t *)ubx_malloc(header->length);
		ubx_fread_in_loop(payload, header->length, 1, data_fp);
		ubx_fread_in_loop(checksum, CHECKSUM_LENGTH, 1, data_fp);
		compute_checksum(header, payload, header->length, computed_checksum);

		sprint_protocol_name(protocol_name, header);
		if (!is_checksum_equal(checksum, computed_checksum)) { /* rewind to SYNC[1] if checksum failed */
			fprintf(log, "Wrong checksum, discard one %s\n\n", protocol_name);
			ubx_free(payload);
			ubx_fseek(data_fp, -(HEADER_LENGTH + header->length + CHECKSUM_LENGTH - 1), SEEK_CUR);
			continue;
		}
		fprintf(log, "%s\n", protocol_name);
		fprint_header(log, header);
		fprint_payload(log, payload, header->length);
		fprint_checksum(log, checksum);
		fprintf(log, "\n");
		ubx_free(payload);
	}

	ubx_fclose(log);
	ubx_fclose(data_fp);
	system("pause");
	exit(EXIT_SUCCESS);
}