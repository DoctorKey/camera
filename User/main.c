
/* ------------------------------------------包含的头文件-----------------------------------------------*/
#include "stm32f4xx.h"
#include "init.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "ov7670.h"
#include "pwm_out.h"

volatile u32 jpeg_data_len=0; 			//buf中的JPEG有效数据长度 
u8 Init_Finish = 0;
/*************************************************************************************
  * 函数名称：main()
  * 参数    ：void
  * 返回值  ：void
  * 描述    ：程序主入口main函数
  *************************************************************************************/
int main(void)
{ 
	u8 *p;
	int i;
	int16_t pwm[4]={200,400,800,1200};
	u8 data_to_send[2]={1,2};
	Init_Finish=All_Init();

  delay_ms(100);
	SetPwm(pwm,400,2000);
	USART_SendString(USART2,data_to_send);
	USART_SendData(USART2,10);
//	Usart2_Send(data_to_send,2);
	if(OV7670_Init())
	{
		USART_SendData(USART2,00);
		while(1)
		{
			LED0(On);
			delay_ms(300);
			LED0(Off);
			delay_ms(300);	
			USART_SendData(USART2,00);			
		}
	}
//	OV7670_Init();
	delay_ms(1000);
	Cam_Start();
  	while(1)
	{
		USART_SendData(USART2,255);
		p=(u8*)jpeg_buf;
		jpeg_data_len=jpeg_buf_size-DMA_GetCurrDataCounter(DMA2_Stream1);
		jpeg_data_len=2048;//160*120;//160*120
//			for(i=0;i<jpeg_data_len*4;i++)		//dma传输1次等于4字节,所以乘以4.
//			{
////        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);	//循环发送,直到发送完毕  		
//				USART_SendData(USART2,p[i]); 
//			} 
		USART_SendString(USART2,p);
		LED0(On);
		delay_ms(300);
		LED0(Off);
//		delay_ms(300);
		
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

