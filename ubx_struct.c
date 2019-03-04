#include <stdio.h>
#include "ubx_struct.h"
#include "ubx_util.h"
#include "write_detials.h"



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

void fprint_esf_means(FILE *fp,uint32_t timeTag,uint16_t data_type,double float_data)
{
	fprintf(fp, "%u,%d,%lf",timeTag, data_type, float_data);
	fprintf(fp, "\n");
}

//void fprintf_nav_pvt(FILE *fp ,uint_16t );pPVT,UBX_NAV_PVT1.iTOW,dataPrint
void fprint_nav_pvt(FILE *fp,uint32_t iTOW,int32_t PrintLon, int32_t PrintLat, int32_t PrintHei, int32_t PrintVelN, int32_t PrintVelE, int32_t PrintVelD)
{
	
	fprintf(fp, "%u,%d,%d,%d,%d,%d,%d", iTOW, PrintLon, PrintLat, PrintHei, PrintVelN, PrintVelE, PrintVelD);
	//fprintf(fp, "%f",float_data);
	fprintf(fp, "\n");
}


void fpring_float_data(FILE *p, double float_data)
{
	fprintf(p, "%f\n",float_data);
	fclose(p);
}



/*
///////////////////////////////////////////////
双精度(64位)浮点数的结构与单精度相仿

名称                                           长度        比特位置
符号位    Sign  （S）             : 1bit        （b63）
指数部分Exponent （E）     : 11bit      （b62-b52）
尾数部分Mantissa   （M）   : 52bit      （b51-b0）
双精度的指数部分（E）采用的偏置码为1023
求值方法:(-1)^S*(1.M)*2^(E-1023)
/////////////////////////////////////
---------------------
*/

void ubx2p754(uint64_t p,double *tm)
{
	double tempNum;
	double ResTem = 1.0;
	uint64_t Epart = (p & 0x7FF0000000000000) >> 52;
	uint64_t Mpart = ((p << 12) >> 12) ;
	uint8_t Spart = (p & 0x80000000000000)*(-1);
	
	for (int8_t i = 0; i < 52; i++)
	{
		ResTem += (Mpart & (0x4000000000000 >> i)) >> (51 - i) * pow(2, (-(i+1)));
	}

	tempNum = pow(-1, Spart) * ResTem * pow(2, (Epart - 1023));
	*tm = tempNum;
};

