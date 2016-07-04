
/* ------------------------------------------������ͷ�ļ�-----------------------------------------------*/
#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "ov7670.h"
#include "pwm_out.h"

volatile u32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ��� 
/*************************************************************************************
  * �������ƣ�main()
  * ����    ��void
  * ����ֵ  ��void
  * ����    �����������main����
  *************************************************************************************/
int main(void)
{ 
	u8 *p;
	int i;
  	SystemInit();			                                   //��ʼ��ϵͳʱ�ӣ�����ʱ��Ϊ168Mhz
  	LED_GPIO_Conf();										   //��ʼ��LED��GPIO����
  	SysTick_Init();
  	USART1_Conf();
		PWM_Out_Init(400);				//��ʼ������������
//  	LCD_Init();
  	delay_ms(100);

	USART_SendData(USART1,10);
	if(OV7670_Init())
	{
		USART_SendData(USART1,00);
		while(1)
		{
			LED0(On);
			delay_ms(300);
			LED0(Off);
			delay_ms(300);	
			USART_SendData(USART1,00);			
		}
	}
//	OV7670_Init();
	delay_ms(1000);
	Cam_Start();
  	while(1)
	{
		USART_SendData(USART1,255);
		p=(u8*)jpeg_buf;
		jpeg_data_len=jpeg_buf_size-DMA_GetCurrDataCounter(DMA2_Stream1);
		jpeg_data_len=160*120;//160*120
			for(i=0;i<jpeg_data_len*4;i++)		//dma����1�ε���4�ֽ�,���Գ���4.
			{
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);	//ѭ������,ֱ���������  		
				USART_SendData(USART1,p[i]); 
			} 
//		LED1(On);
		delay_ms(300);
//		LED1(Off);
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

