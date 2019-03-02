#ifndef _WRITE_DETAILS_H_
#define _WRITE_DETAILS_H_

#include <stdlib.h>
#include <stdint.h>

void write_esf_ins_payload(uint8_t *payload, uint16_t data_length);
void write_nav_pvt_payload(uint8_t *payload, uint16_t data_length);

void write_rxm_rawx_payload(uint8_t *payload, uint16_t data_length);
void write_esf_means_payload(uint8_t * payload, uint16_t data_length);
void write_nav_pvt(uint8_t * payload, uint16_t data_length);      
#endif