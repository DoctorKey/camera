#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "stm32f4xx.h"
#include "led.h"
#include "usart.h"
#include "pwm_out.h"

/***************中断优先级******************/
#define NVIC_GROUP NVIC_PriorityGroup_3		//中断分组选择
#define NVIC_PWMIN_P			1		//接收机采集
#define NVIC_PWMIN_S			1
#define NVIC_TIME_P       2		//暂未使用
#define NVIC_TIME_S       0
#define NVIC_UART_P				5		//暂未使用
#define NVIC_UART_S				1
#define NVIC_UART2_P			3		//串口2中断
#define NVIC_UART2_S			1
/***********************************************/

/***************picture******************/
#define PIC_ROW 120
#define PIC_COL 320
#define jpeg_buf_size (PIC_ROW*PIC_COL/2)
/***********************************************/
/***************ctrl******************/
#define CH_NUM 4
#define PWM_MIN 0
#define PWM_MAX 1000
/***********************************************/
#endif