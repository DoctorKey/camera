#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

void TIM3_Int_Init(u16 arr,u16 psc);
uint32_t GetSysTime_us(void);

#endif
