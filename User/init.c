#include "init.h"
#include "include.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//中断优先级组别设置
	
  SystemInit();			                      //初始化系统时钟，设置时钟为168Mhz
	
  LED_GPIO_Conf();												//初始化LED的GPIO配置
	
  SysTick_Init();
	
//USART1_Conf();
	
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//初始化PWM输出功能
	
	return (1);
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
