#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include "stm32f4xx.h"
#include "led.h"
#include "usart.h"
#include "pwm_out.h"

/***************�ж����ȼ�******************/
#define NVIC_GROUP NVIC_PriorityGroup_3		//�жϷ���ѡ�� 0~7��ռ 0~1��Ӧ
#define NVIC_PWMIN_P			1		//���ջ��ɼ�
#define NVIC_PWMIN_S			1

#define NVIC_TIM3_P       1		//��δʹ��
#define NVIC_TIM3_S       3

#define NVIC_DCMI_P       1		//DCMI�ж�
#define NVIC_DCMI_S       2

#define NVIC_UART1_P			7		//����1�ж�
#define NVIC_UART1_S			1

#define NVIC_UART2_P			2		//����2�ж�
#define NVIC_UART2_S			0
/***********************************************/

/***************picture******************/
#define PIC_ROW 120
#define PIC_COL 160
#define jpeg_buf_size (PIC_ROW*PIC_COL/2)
/***********************************************/

/***************ctrl******************/
#define CH_NUM 4
#define PWM_MIN 0
#define PWM_MAX 1000
/***********************************************/

#endif

