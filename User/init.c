#include "init.h"
#include "include.h"
#include "usmart.h"
#include "delay.h"
#include "timer.h"
#include "ov7670.h"
#include "led.h"

u8 All_Init()
{
	NVIC_PriorityGroupConfig(NVIC_GROUP);		//中断优先级组别设置
	
  SystemInit();			                      //初始化系统时钟，设置时钟为168Mhz
	
  LED_GPIO_Conf();												//初始化LED的GPIO配置
	
  SysTick_Init();
		
	Usart2_Init(115200);
	
	PWM_Out_Init(50);				//初始化PWM输出功能,50Hz
	
	uart_init(115200);
	
	TIM3_Int_Init(10000-1,8400-1);//10Khz计数,1秒钟中断一次
	
	usmart_dev.init(84);
	
	if(OV7670_Init())
	{
		ov7670_error();
	}

	delay_ms(1000);
	
	DCMI_Start();
	
	return (1);
}
