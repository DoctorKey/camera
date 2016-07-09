#ifndef _PWM_OUT_H_
#define _PWM_OUT_H_

#include "stm32f4xx.h"

u8 PWM_Out_Init(uint16_t hz);
void SetPwm_1(int16_t pwm[],s16 min,s16 max);
void SetPwm_5(int16_t pwm_3,int16_t pwm_4,s16 min,s16 max);

#endif

