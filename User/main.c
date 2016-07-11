
/* ------------------------------------------������ͷ�ļ�-----------------------------------------------*/
#include "stm32f4xx.h"
#include "init.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "ov7670.h"
#include "pwm_out.h"
#include "ctrl.h"
#include "usmart.h"
#include "dgp.h"

u8 Init_Finish = 0;
/*************************************************************************************
  * �������ƣ�main()
  * ����    ��void
  * ����ֵ  ��void
  * ����    �����������main����
  *************************************************************************************/
int main(void)
{ 
	u8 *p;
	u32 i;
	
	Init_Finish=All_Init();

  delay_ms(100);
	ctrl_pwm(CH);
	i=jpeg_buf_size;
  	while(1)
	{
		if(jpeg_data_ok==1)	//�Ѿ��ɼ���һ֡ͼ����
		{ 			
//			i=jpeg_data_len*4;
			i=jpeg_buf_size*4;
			p=(u8*)jpeg_buf;
			LED0(On);
			USART_SendString_bysize(USART2,p,i);
//			USART_SendData(USART2,255);
			delay_ms(300);
			LED0(Off);
			jpeg_data_ok=2;	//���jpeg���ݴ�������,������DMAȥ�ɼ���һ֡��.
		}		
//		p=(u8*)jpeg_buf;
//			LED0(On);
//			USART_SendString_bysize(USART2,p,i*4);
//			USART_SendData(USART2,255);
//			delay_ms(300);
//			LED0(Off);
//		DCMI_Start();
//		delay_ms(2000);
//		DCMI_Stop();
		LED0(Off);	
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

