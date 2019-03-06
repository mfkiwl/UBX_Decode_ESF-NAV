#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ubx_struct.h"
#include "ubx_util.h"
#include "ubx_protocol.h"
#include "write_detials.h"
#include "convert.h"
#define MAXPATH              1024


int main(int argc, char *argv[])
{
	char path[MAXPATH];
	char protocol_name_buf[MAX_PROTOCOL_NAME];
	uint8_t header_buf[BUFSIZ];
	uint8_t checksum[CHECKSUM_LENGTH];
	uint8_t computed_checksum[CHECKSUM_LENGTH];
	uint8_t *payload;
	uint16_t timeTag=0;              //create personal timetag
	struct ubx_header *header;
	FILE *data_fp;

	FILE *log;
	//FILE *write;
	

	printf("UBX file path: ");
	scanf("%s", path);
	data_fp = ubx_fopen(path, "rb");
	log = ubx_fopen("log.txt", "w");
	//write = ubx_fopen("esf.txt", "a+");

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
		sprintf(protocol_name_buf, "%s", protocol_name(header));
		if (!is_checksum_equal(checksum, computed_checksum)) { /* rewind to SYNC[1] if checksum failed */
			fprintf(log, "Wrong checksum, discard one %s\n\n", protocol_name_buf);
			ubx_free(payload);
			ubx_fseek(data_fp, -(HEADER_LENGTH + header->length + CHECKSUM_LENGTH - 1), SEEK_CUR);
			continue;
		}
		fprintf(log, "%s\n", protocol_name_buf);
		fprint_header(log, header);
		fprint_payload(log, payload, header->length);
		fprint_checksum(log, checksum);
		fprintf(log, "\n");
	
		if (is_ubx_esf_meas(header)) {
			write_esf_means_payload(payload, header->length);
			ubx_free(payload);
			//timeTag=timeTag+1;
		}
		/*	/*
		if (is_ubx_esf_raw(header)) {
			write_esf_raw_payload(payload, header->length);
			ubx_free(payload);
		}
		
		if (is_ubx_nav_pvt(header)) {//UBX_NAV_PVT
			write_nav_pvt_payload(payload, header->length);
			ubx_free(payload);
		}

		
		/*
		if (is_ubx_rxm_rawx(header)) {//UBX_RXM_RAWX
			write_rxm_rawx_payload(payload, header->length);
			ubx_free(payload);
		}*/
		/*
		if (header->klass == 0x13 && header->id == 0x00) {//MGA_GPS_EPH
			write_MAG_GPS_EPH(payload, header->length);
			ubx_free(payload);
		}
		if (header->klass == 0x02 && header->id == 0x13) {//RXM_SFRBX
			write_RXM_SFRBX(payload, header->length);
			ubx_free(payload);
		}
		*/

	}
	ubx_fclose(log);
	//ubx_fclose(write);
	ubx_fclose(data_fp);
	system("pause");
	exit(EXIT_SUCCESS);
}