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
	
	TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
	
	usmart_dev.init(84);
	
	if(OV7670_Init())
	{
		while(1)
		{
			LED0(On);
			delay_ms(300);
			LED0(Off);
			delay_ms(300);	
			USART_SendData(USART2,00);			
		}
	}

	delay_ms(1000);
	
	DCMI_Start();
	
	return (1);
}
