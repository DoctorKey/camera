#include "init.h"
#include "include.h"
#include "usmart.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//中断优先级组别设置
	
  SystemInit();			                      //初始化系统时钟，设置时钟为168Mhz
	
  LED_GPIO_Conf();												//初始化LED的GPIO配置
	
  SysTick_Init();
	
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//初始化PWM输出功能
	
	uart_init(115200);
	
	usmart_dev.init(84);
	
	return (1);
}
