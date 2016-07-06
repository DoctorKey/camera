#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"


#define On      0
#define Off     1
#define LED0(x) (x?(GPIO_SetBits(GPIOB,GPIO_Pin_9)):(GPIO_ResetBits(GPIOB,GPIO_Pin_9)))

void LED_GPIO_Conf(void);

#endif
