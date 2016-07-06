#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "stm32f4xx.h"
#include "led.h"
#include "usart.h"
#include "pwm_out.h"

/***************�ж����ȼ�******************/
#define NVIC_GROUP NVIC_PriorityGroup_3		//�жϷ���ѡ��
#define NVIC_PWMIN_P			1		//���ջ��ɼ�
#define NVIC_PWMIN_S			1
#define NVIC_TIME_P       2		//��δʹ��
#define NVIC_TIME_S       0
#define NVIC_UART_P				5		//��δʹ��
#define NVIC_UART_S				1
#define NVIC_UART2_P			3		//����2�ж�
#define NVIC_UART2_S			1
/***********************************************/

/***************picture******************/
#define jpeg_buf_size 160*120
/***********************************************/
#endif