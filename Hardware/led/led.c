#include "led.h"

/******************************************************************************************
*函数名：LED_GPIO_Conf()
* 参数：void
* 返回值：void
* 功能：LED的管脚配置
*********************************************************************************************/
void LED_GPIO_Conf(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;		                                              //定义GPIO初始化结构体
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			  					  //使能GPIOB的AHP1时钟
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;										  //设置初始化模式为输出模式
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;										  //设置输出类型为推挽输出
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;									  //设置输出速度为100Mhz
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;										  
   GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_14|GPIO_Pin_15);								  //定义初始化的管脚为Pin14	Pin15
   GPIO_Init(GPIOB, &GPIO_InitStructure);												  //初始化GPIOB的Pin_14管脚
   GPIO_SetBits(GPIOB,GPIO_Pin_14);														  //使GPIOB的Pin_14输出高电平
   GPIO_SetBits(GPIOB,GPIO_Pin_15);														  //使GPIOB的Pin_15输出高电平
}
