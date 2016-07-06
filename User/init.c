#include "init.h"
#include "include.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//�ж����ȼ��������
	
  SystemInit();			                      //��ʼ��ϵͳʱ�ӣ�����ʱ��Ϊ168Mhz
	
  LED_GPIO_Conf();												//��ʼ��LED��GPIO����
	
  SysTick_Init();
	
//USART1_Conf();
	
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//��ʼ��PWM�������
	
	return (1);
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
