#include <stdio.h>
#include "write_detials.h"
#include "convert.h"
#include "ubx_struct.h"
uint32_t temp_u_long = 0;
uint16_t temp_u_short = 0;
uint8_t temp_u_char = 0;

int32_t temp_s_long = 0;
int16_t temp_s_short = 0;
int8_t temp_s_char = 0;
int32_t rxmN = 0;
uint64_t double754;
////////////using for bit datau

int16_t count = 0;
FILE *p_esf = NULL;
FILE *p_rxm = NULL;
FILE *pPVT = NULL;
FILE *p;


struct UBX_ESF_INS
{
	uint32_t  iTow;
	int32_t	xAngRate;
	int32_t	yAngRate;
	int32_t	zAngRate;
	int32_t	xAccel;
	int32_t	yAccel;
	int32_t	zAccel;
}UBX_ESF_INS1;

struct UBX_ESF_MEANS
{
	uint32_t  timeTag;				//4bytes
	int16_t flags;					//2bytes
	uint16_t id;					//2bytes
	uint32_t flWheelTicks;
	int32_t gyroscope_t;
	int32_t speed;
	int32_t	xAngRate;
	int32_t	yAngRate;
	int32_t	zAngRate;
	int32_t	xAccel;
	int32_t	yAccel;
	int32_t	zAccel;
}UBX_ESF_MEANS1;


struct UBX_MGA_GPS
{
	uint8_t type;			//Message type (0x01 for this type)
	uint8_t version;
	uint8_t svID;
	uint8_t reserved1;
	uint8_t fitInterval;
	uint8_t uraIndex;
	uint8_t scHealth;
	int8_t tgd;
	uint16_t iodc;		//2 bytes
	uint8_t reserved2;
	int8_t af2;
	int16_t af1;			//2 bytes
	int32_t af0;			//4 bytes
	int16_t crs;			//2 bytes
	int16_t deltaN;		//2 bytes Mean motion difference from computed value
	int32_t m0;				//4 bytes Mean anomaly at reference time
	int16_t cuc;			//2 bytes Amplitude of cosine harmonic correction term to argument of latitude
	int16_t cus;			//2 bytes Amplitude of sine harmonic correction term to argument of latitude
	uint32_t e;			//4 bytes Eccentricity
	uint32_t sqrtA;		//4 bytes m^0.5 Square root of the semi-major axis
	uint16_t toe;			//2 bytes Reference time of ephemeris
	int16_t cic;			//2 bytes Amplitude of cos harmonic correction term to angle of inclination
	int32_t omega0;			//4 bytes Longitude of ascending node of orbit plane at weekly epoch
	int16_t cis;			//2 bytes  Amplitude of sine harmonic correction term to angle of inclination
	int16_t crc;			//2 bytes 50-51 Amplitude of cosine harmonic correction term to orbit radius
	int32_t i0;				//4 bytes 52-55 Inclination angel at reference time
	int32_t omega;			//4 bytes 56-59 Argument of perigee
	int32_t omegaDot;		//4 bytes 60-63 Rate of right ascension
	int16_t idot;			//2 bytes 64-65 Rate of inclination angle
	uint8_t reserved3;	//reserved

}UBX_MGA_GPS1;

struct UBX_NAV_PVT
{
	uint32_t iTOW;				//4 bytes			0.0,
	uint16_t year;			//2 bytes
	uint8_t month;				//1 byte
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t valid;
	uint32_t tAcc;				//4 bytes
	int32_t  nano;				//4 bytes
	uint8_t fixType;
	uint8_t flags;
	uint8_t flags2;
	uint8_t numSV;
	int32_t lon;				//4 bytes 24-27
	int32_t lat;				//4 bytes 28-31
	int32_t height;				//4 bytes 32-35
	int32_t hMSL;				//4 bytes 36-39
	uint32_t hAcc;				//40-43
	uint32_t vAcc;				//44-47
	int32_t velN;				//48-51
	int32_t velE;
	int32_t velD;
	int32_t gSpeed;
	int32_t headMot;
	uint32_t sAcc;
	uint32_t headAcc;
	uint16_t pDOP;
	uint8_t reserved1[6];
	int32_t headVeh;
	int16_t magDec;
	uint16_t magACC;
}UBX_NAV_PVT1;

struct UBX_ESF_RAW
{
	uint32_t  reserved;				//4byte reserved
	int32_t	xAngRate1;
	int32_t	yAngRate1;
	int32_t	zAngRate1;
	int32_t	xAccel1;
	int32_t	yAccel1;
	int32_t	zAccel1;
}UBX_ESF_RAW1;

struct UBX_RXM_RAWX
{
	int64_t rcvTow;
	uint16_t week;
	int16_t leapS;
	uint16_t munMeas;
	uint16_t recStat;
	uint16_t reserved1;
	int32_t prMes[30];
	int32_t cpMes[30];
	int32_t doMEs[30];
	uint16_t gnssId[30];
	uint16_t svId[30];
	uint16_t reserved2[30];
	uint16_t freqId[30];
	uint16_t locktime[30];
	uint16_t cno[30];
	uint16_t prStdev[30];
	uint16_t cpStdev[30];
	uint16_t doStdev[30];
	uint16_t trkStat[30];
	uint16_t reserved3[30];
}UBX_RXM_RAWX1[100000];

void write_esf_ins_payload(uint8_t * payload, uint16_t data_length)
{
	//size_t *payload = payload;
	temp_s_char = temp_s_char & 0;
	temp_s_long = temp_s_long & 0;
	temp_s_short = temp_s_short & 0;
	temp_u_char = temp_u_char & 0;
	temp_u_short = temp_u_short & 0;
	temp_u_long = temp_u_char & 0;

	p_esf = fopen("esf.txt", "a+");
	fseek(p_esf, 0, SEEK_END);

	int i = 8;
	for (i = 8; i<36; i++) {
		temp_u_long = (temp_u_long << 8) | payload[i];
		temp_s_long = (temp_s_long << 8) | payload[i];
		if (i == 12) {
			UBX_ESF_INS1.iTow = temp_u_long;
		}
		//temp_s_long = (temp_s_long << 8) | payload[i];
		if (i == 16) {
			UBX_ESF_INS1.xAngRate = temp_s_long;
		}
		if (i == 20) {
			UBX_ESF_INS1.yAngRate = temp_s_long;
		}
		if (i == 24) {
			UBX_ESF_INS1.zAngRate = temp_s_long;
		}
		if (i == 28) {
			UBX_ESF_INS1.xAccel = temp_s_long;
		}
		if (i == 32) {
			UBX_ESF_INS1.yAccel = temp_s_long;
		}
		if (i == 36) {
			UBX_ESF_INS1.zAccel = temp_s_long;
		}
	}
	//write esf detials to esf.txt

	fseek(p_esf, 0, SEEK_END);
	fprintf(p_esf, "%x;%x;%x;%x;%x;%x\n", UBX_ESF_INS1.xAngRate, UBX_ESF_INS1.yAngRate, UBX_ESF_INS1.zAngRate, UBX_ESF_INS1.xAccel, UBX_ESF_INS1.yAccel, UBX_ESF_INS1.zAccel);

	fclose(p_esf);
}
void write_nav_pvt_payload(uint8_t * payload, uint16_t data_length,uint16_t timeTag)
{
	//clear temp
	//typedef UBX_ESF_MEANS1 *RecPointer;
	//RecPointer r;
	uint16_t data_type = 0;
	uint32_t data_detials = 0;
	int32_t dataPrint[6];
	double float_data;
	temp_s_long = temp_s_long & 0;
	temp_u_long = temp_u_long & 0;
	temp_u_char = temp_u_char & 0;
	temp_u_short = temp_u_short & 0;
	count = 0;
	pPVT = fopen("pvt.txt", "a+");
	//UTC TIME
	temp_u_long = temp_u_long | (0x0FF & payload[0]) << 0 | (0x0FF & payload[1]) << 8 | (0x0FF & payload[2]) << 16 | (0x0FF & payload[3]) << 24;
	UBX_NAV_PVT1.iTOW = temp_u_long;
	UBX_NAV_PVT1.year = (0x0FF & payload[4]) << 0 | (0x0FF & payload[5]) << 8;
	UBX_NAV_PVT1.month = 0xFF & payload[6];
	UBX_NAV_PVT1.day = 0xFF & payload[7];
	UBX_NAV_PVT1.hour = 0xFF & payload[8];
	UBX_NAV_PVT1.min = 0xFF & payload[9];
	UBX_NAV_PVT1.sec = 0xFF & payload[10];
	UBX_NAV_PVT1.valid = 0xFF & payload[11];
	UBX_NAV_PVT1.tAcc = (0x0FF & payload[12]) << 0 | (0x0FF & payload[13]) << 8 | (0x0FF & payload[14]) << 16 | (0x0FF & payload[15]) << 24;
	UBX_NAV_PVT1.nano = (0x0FF & payload[16]) << 0 | (0x0FF & payload[17]) << 8 | (0x0FF & payload[18]) << 16 | (0x0FF & payload[19]) << 24;

	// ¾­Î³¸ß
	UBX_NAV_PVT1.lon = (0x0FF & payload[24]) << 0 | (0x0FF & payload[25]) << 8 | (0x0FF & payload[26]) << 16 | (0x0FF & payload[27]) << 24;
	UBX_NAV_PVT1.lat = (0x0FF & payload[28]) << 0 | (0x0FF & payload[29]) << 8 | (0x0FF & payload[30]) << 16 | (0x0FF & payload[31]) << 24;
	UBX_NAV_PVT1.height = (0x0FF & payload[32]) << 0 | (0x0FF & payload[33]) << 8 | (0x0FF & payload[34]) << 16 | (0x0FF & payload[35]) << 24;
	UBX_NAV_PVT1.hMSL = (0x0FF & payload[36]) << 0 | (0x0FF & payload[37]) << 8 | (0x0FF & payload[38]) << 16 | (0x0FF & payload[39]) << 24;
	UBX_NAV_PVT1.hAcc = (0x0FF & payload[40]) << 0 | (0x0FF & payload[41]) << 8 | (0x0FF & payload[42]) << 16 | (0x0FF & payload[43]) << 24;
	UBX_NAV_PVT1.vAcc = (0x0FF & payload[44]) << 0 | (0x0FF & payload[45]) << 8 | (0x0FF & payload[46]) << 16 | (0x0FF & payload[47]) << 24;
	UBX_NAV_PVT1.velN = (0x0FF & payload[48]) << 0 | (0x0FF & payload[49]) << 8 | (0x0FF & payload[50]) << 16 | (0x0FF & payload[51]) << 24;
	UBX_NAV_PVT1.velE = (0x0FF & payload[52]) << 0 | (0x0FF & payload[53]) << 8 | (0x0FF & payload[54]) << 16 | (0x0FF & payload[55]) << 24;
	UBX_NAV_PVT1.velD = (0x0FF & payload[56]) << 0 | (0x0FF & payload[57]) << 8 | (0x0FF & payload[58]) << 16 | (0x0FF & payload[59]) << 24;
	UBX_NAV_PVT1.gSpeed = (0x0FF & payload[60]) << 0 | (0x0FF & payload[61]) << 8 | (0x0FF & payload[62]) << 16 | (0x0FF & payload[63]) << 24;
	dataPrint[0]=UBX_NAV_PVT1.lon;
	dataPrint[1]=UBX_NAV_PVT1.lat;
	dataPrint[2]=UBX_NAV_PVT1.height;
	dataPrint[3]=UBX_NAV_PVT1.velN;
	dataPrint[4]=UBX_NAV_PVT1.velE;
	dataPrint[5]=UBX_NAV_PVT1.velD;
	fprint_nav_pvt(pPVT,UBX_NAV_PVT1.iTOW,dataPrint);
	
	
	fclose(p);

}
/*
void write_rxm_rawx_payload(uint8_t * payload, uint16_t data_length)
{
	//clear temp
	//typedef UBX_ESF_MEANS1 *RecPointer;
	//RecPointer r;
	uint16_t data_type = 0;
	uint32_t data_detials = 0;
	double tempNum;
	double float_data;
	temp_s_long = temp_s_long & 0;
	temp_u_long = temp_u_long & 0;
	temp_u_char = temp_u_char & 0;
	temp_u_short = temp_u_short & 0;
	count = 0;
	p_rxm = fopen("rxm.txt", "a+");
	//_mkdir("esf.m");
	double754 = (0x0FF & payload[0]) << 0 | (0x0FF & payload[1]) << 8 | (0x0FF & payload[2]) << 16 | (0x0FF & payload[3]) << 24 | (0x0FF & payload[4]) << 32 | (0x0FF & payload[5]) << 40 | (0x0FF & payload[6]) << 48 | (0x0FF & payload[7]) << 56;
	
	UBX_RXM_RAWX1[rxmN].rcvTow = ubx2p754(double754, &tempNum);
	
	UBX_RXM_RAWX1[rxmN].week = (0x0FF & payload[8]) << 0 | (0x0FF & payload[9]) << 8;
	UBX_RXM_RAWX1[rxmN].leapS = 0x0FF & payload[10];
	UBX_RXM_RAWX1[rxmN].munMeas = (0x0FF & payload[11]);
	int16_t cN = 16;
	for (size_t i = 0; i < UBX_RXM_RAWX1[rxmN].munMeas ; i++)
	{
		UBX_RXM_RAWX1[rxmN].prMes[i] = (0x0FF & payload[cN]) << 0 | (0x0FF & payload[cN + 1]) << 8 | (0x0FF & payload[cN + 2]) << 16 | (0x0FF & payload[cN + 3]) << 24 | (0x0FF & payload[cN + 4]) << 32 | (0x0FF & payload[cN + 5]) << 40 | (0x0FF & payload[cN + 6]) << 48 | (0x0FF & payload[cN + 7]) << 56;
		cN = cN + 8;
		UBX_RXM_RAWX1[rxmN].cpMes[i] = (0x0FF & payload[cN]) << 0 | (0x0FF & payload[cN + 1]) << 8 | (0x0FF & payload[cN + 2]) << 16 | (0x0FF & payload[cN + 3]) << 24 | (0x0FF & payload[cN + 4]) << 32 | (0x0FF & payload[cN + 5]) << 40 | (0x0FF & payload[cN + 6]) << 48 | (0x0FF & payload[cN + 7]) << 56;
		cN = cN + 8;
		UBX_RXM_RAWX1[rxmN].doMEs[i] = (0x0FF & payload[cN]) << 0 | (0x0FF & payload[cN + 1]) << 8 | (0x0FF & payload[cN + 2]) << 16 | (0x0FF & payload[cN + 3]) << 24;
		cN = cN + 4;
		UBX_RXM_RAWX1[rxmN].gnssId[i] = 0x0FF & payload[cN++];
		UBX_RXM_RAWX1[rxmN].svId[i] = 0x0FF & payload[cN++];
		cN = cN + 2;
		UBX_RXM_RAWX1[rxmN].locktime[i] == 0x0FF & payload[cN++] << 0 | 0x0FF & payload[cN++] << 8;
		UBX_RXM_RAWX1[rxmN].cno[i] = 0x0FF & payload[cN++];
		UBX_RXM_RAWX1[rxmN].prStdev[i] = 0x0FF & payload[cN++];
		UBX_RXM_RAWX1[rxmN].cpStdev[i] = 0x0FF & payload[cN++];
		UBX_RXM_RAWX1[rxmN].doStdev[i] = 0x0FF & payload[cN++];
	}
	rxmN = rxmN + 1;
	fclose(p_rxm);
}
*/
void write_esf_raw_payload(uint8_t * payload, uint16_t data_length, uint16_t PtimeTag)
{
	int32_t len = (data_length - 8) / 56;
	for (size_t i = 0; i < len; i++)
	{
		write_esf_means_payload(payload, data_length, PtimeTag);
	}
}

void write_esf_means_payload(uint8_t * payload, uint16_t data_length, uint16_t PtimeTag) {
	//clear temp
	//typedef UBX_ESF_MEANS1 *RecPointer;
	//RecPointer r;
	uint16_t data_type = 0;
	uint32_t data_detials = 0;
	double float_data;
	double IMUdata[6];
	temp_s_long = temp_s_long & 0;
	temp_u_long = temp_u_long & 0;
	temp_u_char = temp_u_char & 0;
	temp_u_short = temp_u_short & 0;
	count = 0;
	p_esf = fopen("esf.txt", "a+");
	//_mkdir("esf.m");
	//p = fopen("esf.m","a+");
	temp_u_long = temp_u_long | (0x0FF & payload[0]) << 0 | (0x0FF & payload[1]) << 8 | (0x0FF & payload[2]) << 16 | (0x0FF & payload[3]) << 24;
	UBX_ESF_MEANS1.timeTag = temp_u_long;
	temp_u_char = (0x0FF & payload[4]) << 8 | (0x0FF & payload[5]);
	UBX_ESF_MEANS1.flags = 0x07 & temp_u_char;   //3 bits is useful
	temp_u_short = (0x0FF & payload[6]) << 8 | (0x0FF & payload[7]);
	UBX_ESF_MEANS1.id = temp_s_short;
	temp_u_long = temp_u_long & 0x0;
	for (size_t i = 8; i < (data_length); i = i + 4)
	{
		temp_u_long = (temp_u_long | (0xFF & payload[i])) << 0 | (0xFF & payload[i + 1]) << 8 | (0xFF & payload[i + 2]) << 16 | (0xFF & payload[i + 3]) << 24;
		//temp_s_long = ( temp_s_long | ( 0x0F & payload[i+1]) )<< 8;
		//temp_s_long = ( temp_s_long | ( 0x0F & payload[i+2]) )<< 8;
		//temp_s_long = ( temp_s_long | ( 0x0F & payload[i+3]) );
		data_type = payload[i + 3];//(temp_u_long  & 0x3F000000)>>24;
		/*data_detials = temp_u_long & 0xFFFFFF;
		//if data_type is in need       
		switch(data_type)
		{
			case'14':
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[0]=float_data;
			}
			case'13':
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[1]=float_data;
			}
			case'5' :
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[2]=float_data;
			}
			case'16':
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[3]=float_data;
			}
			case'17':
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[4]=float_data;
			}
			case'18':
			{
				data_detials=temp_u_long & 0xFFFFFF;
				Rawdata2Detials(data_detials, data_type, &float_data);
				IMUdata[5]=float_data;
			}
		}
		fprint_esf_means(p_esf, UBX_ESF_MEANS1.timeTag,data_type,IMUdata);*/
		
		if (data_type == 0x05 | (data_type<=0x0e & data_type>=0x0b)|( data_type<=0x12 & data_type>=0x010) )
		{
			data_detials = temp_u_long & 0xFFFFFF;
			Rawdata2Detials(data_detials, data_type, &float_data);
			//fpring_float_data(p,float_data);
			fprint_esf_means(p_esf, UBX_ESF_MEANS1.timeTag, data_type, float_data);
		}
		else continue;
		
	}
	//free(r);
	fclose(p_esf);
}


int usigned_long(uint8_t *payload) {
	uint32_t temp_u_long = 0;
	for (size_t i = 0; i < 4; i++)
	{
		temp_u_long = (temp_u_long << 8) | payload[i];
	}
	return temp_u_long;
}
int usigned_short(uint8_t *payload) {
	uint32_t temp_u_short = 0;
	for (size_t i = 0; i < 2; i++)
	{
		temp_u_short = (temp_u_short << 8) | payload[i];
	}
	return temp_u_short;
}

int signed_long(uint8_t *payload) {
	int32_t temp_s_long = 0;
	for (size_t i = 0; i < 4; i++)
	{
		temp_s_long = (temp_s_long << 8) | payload[i];
	}
	return temp_s_long;
}

int signed_short(uint8_t *payload) {
	uint32_t temp_s_short = 0;
	for (size_t i = 0; i < 2; i++)
	{
		temp_s_short = (temp_s_short << 8) | payload[i];
	}
	return temp_s_short;
}
