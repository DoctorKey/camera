#include "init.h"
#include "include.h"
#include "usmart.h"
#include "delay.h"
#include "timer.h"
#include "ov7670.h"
#include "led.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//�ж����ȼ��������
	
  SystemInit();			                      //��ʼ��ϵͳʱ�ӣ�����ʱ��Ϊ168Mhz
	
  LED_GPIO_Conf();												//��ʼ��LED��GPIO����
	
  SysTick_Init();
		
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//��ʼ��PWM�������,50Hz
	
	uart_init(115200);
	
	TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
	
	usmart_dev.init(84);
	
	if(OV7670_Init())
	{
		ov7670_error();
	}

	delay_ms(1000);
	
	DCMI_Start();
	
	return (1);
}
