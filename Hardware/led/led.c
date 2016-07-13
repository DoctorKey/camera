#include "led.h"
#include "delay.h"

void LED_GPIO_Conf(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;		                            //定义GPIO初始化结构体
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			  			//使能GPIOB的AHP1时钟
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;										  //设置初始化模式为输出模式
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;										  //设置输出类型为推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;									  //设置输出速度为100Mhz
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;										  
   GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_9);								  //定义初始化的管脚为Pin9
   GPIO_Init(GPIOB, &GPIO_InitStructure);												  //初始化GPIOB的Pin_9管脚
   GPIO_SetBits(GPIOB,GPIO_Pin_9);														  //使GPIOB的Pin_9输出高电平
}
void LED_SET(u8 mode)
{
	if(mode)
		LED0(0);
	else
		LED0(1);
}
void ov7670_error(void)
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
