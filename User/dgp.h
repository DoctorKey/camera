#ifndef _DGP_H_
#define _DGP_H_
#include "stm32f4xx.h"

void jpeg_data_process(void);

extern volatile u8 jpeg_data_ok;
extern volatile u32 jpeg_data_len;
#endif

