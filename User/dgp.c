#include "dgp.h"
#include "include.h"
#include "ov7670.h"

//u32 jpeg_buf[jpeg_buf_size];
u8 ov_frame=0;  						//帧率
u8 frame_count=0;//控制帧率
u16 over_count=0;
//DCMI中断服务函数
void DCMI_IRQHandler(void)
{
		if(DCMI_GetITStatus(DCMI_IT_FRAME)==SET)//捕获到一帧图像
		{
				jpeg_data_process(); 	//jpeg数据处理	
				DCMI_ClearITPendingBit(DCMI_IT_FRAME);//清除帧中断
				ov_frame++;	
		}
		if(DCMI_GetITStatus(DCMI_IT_OVF)==SET)//溢出中断
		{
				over_count++;				
				DCMI_ClearITPendingBit(DCMI_IT_OVF);
		}
} 

volatile u32 jpeg_data_len=0; 			//buf中的JPEG有效数据长度 
volatile u8 jpeg_data_ok=0;				//JPEG数据采集完成标志 
										//0,数据没有采集完;
										//1,数据采集完了,但是还没处理;
										//2,数据已经处理完成了,可以开始下一帧接收
										
//处理JPEG数据
//当采集完一帧JPEG数据后,调用此函数,切换JPEG BUF.开始下一帧采集.
void jpeg_data_process(void)
{
		if(jpeg_data_ok==0)	//jpeg数据还未采集完?
		{
			DMA_Cmd(DMA2_Stream1, DISABLE);//停止当前传输 
			while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}//等待DMA2_Stream1可配置  
			jpeg_data_len=jpeg_buf_size-DMA_GetCurrDataCounter(DMA2_Stream1);//得到此次数据传输的长度
				
			jpeg_data_ok=1; 				//标记JPEG数据采集完按成,等待其他函数处理
		}
		if(jpeg_data_ok==2)	//上一次的jpeg数据已经被处理了
		{
			DMA2_Stream1->NDTR=jpeg_buf_size;	
			DMA_SetCurrDataCounter(DMA2_Stream1,jpeg_buf_size);//传输长度为jpeg_buf_size*4字节
			DMA_Cmd(DMA2_Stream1, ENABLE);			//重新传输
			jpeg_data_ok=0;						//标记数据未采集
		}
} 
