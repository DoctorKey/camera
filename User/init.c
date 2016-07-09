#include "init.h"
#include "include.h"
#include "usmart.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//�ж����ȼ��������
	
  SystemInit();			                      //��ʼ��ϵͳʱ�ӣ�����ʱ��Ϊ168Mhz
	
  LED_GPIO_Conf();												//��ʼ��LED��GPIO����
	
  SysTick_Init();
	
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//��ʼ��PWM�������
	
	uart_init(115200);
	
	usmart_dev.init(84);
	
	return (1);
}
