#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int get2com(uint32_t x)
{
	uint32_t y;
	int32_t result;
	if (y = x >> 23)
	{
		result = ~(x - 1) & 0xFFFFFF | y << 31;
	}
	else
	{
		result = x;
	}
	return result;
}

double Raw2Data(int32_t p, int16_t data_type)
{
	double float_data;
	int32_t resultTwo = 0, tempRes = 1;
	for (size_t i = 0; i < 24; i++)
	{
		resultTwo = resultTwo + ((p >> i) & 0x01) *tempRes;
		tempRes = tempRes * 2;
	}
	//24位变换方式
		if (data_type == 05 | data_type == 13 | data_type == 14)
		{
			float_data = resultTwo *1.0 / 4096.0;				//zyx gyroscope angular rate  deg/s
		}
		else if (data_type >= 16 & data_type <= 18) {
			float_data = resultTwo *1.0 / 1024.0;				//xyz accelermoter specific force  m/s^2
		}
		else if(data_type==12)
		{
			float_data = resultTwo *1.0 / 500.0;
		}
		else if (data_type == 11)
		{
			float_data = resultTwo * 1.0 /1000.0;
		}
	return float_data;
}
void Rawdata2Detials(uint32_t  r, int16_t data_type, double *p) 
{
	double float_data = 0;
	int32_t resultOne = 0;
	resultOne = get2com(r);
	float_data = Raw2Data(resultOne, data_type);
	*p = float_data;
	//return p;
}
