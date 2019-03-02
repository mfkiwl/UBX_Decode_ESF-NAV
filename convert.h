#pragma once
#include <stdint.h>
#include <stdio.h>
int get2com(uint32_t *x);
double Raw2Data(uint32_t p, int16_t data_type);

void Rawdata2Detials(uint32_t  r, int16_t data_type, double *p);