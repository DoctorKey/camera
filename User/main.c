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
#include "test.h"

u8 Init_Finish = 0;
extern char mode;
/*************************************************************************************
  * 函数名称：main()
  * 参数    ：void
  * 返回值  ：void
  * 描述    ：程序主入口main函数
  *************************************************************************************/
int main(void)
{ 
	
	Init_Finish=All_Init();

  delay_ms(100);
	ctrl_pwm(CH);
  	while(1)
	{
		if(jpeg_data_ok==1)	//已经采集完一帧图像了
		{ 	
				switch(mode){
					case 'M':matlab_test(jpeg_buf,im);
						break;
					case 'R':R_test(jpeg_buf,im);
						break;
					case 'G':G_test(jpeg_buf,im);
						break;
					case 'B':B_test(jpeg_buf,im);
						break;
					case 'H':H_test(jpeg_buf,im);
						break;
					case 'h':H_test_op1(jpeg_buf,im);
						break;
					case 'Y':Y_test(jpeg_buf,im);
						break;
					case 'D':D_test(jpeg_buf,im);
						break;
					case 'd':D2_test(jpeg_buf,im);
						break;
					case 'e':D0_test(jpeg_buf,im);
						break;
				}
			jpeg_data_ok=2;	//标记jpeg数据处理完了,可以让DMA去采集下一帧了.
		}		
//		im_send(im);
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

