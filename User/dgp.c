#include "dgp.h"
#include "include.h"
#include "ov7670.h"

//u32 jpeg_buf[jpeg_buf_size];
u8 ov_frame=0;  						//֡��
u8 frame_count=0;//����֡��
u16 over_count=0;
//DCMI�жϷ�����
void DCMI_IRQHandler(void)
{
		if(DCMI_GetITStatus(DCMI_IT_FRAME)==SET)//����һ֡ͼ��
		{
				jpeg_data_process(); 	//jpeg���ݴ���	
				DCMI_ClearITPendingBit(DCMI_IT_FRAME);//���֡�ж�
				ov_frame++;	
		}
		if(DCMI_GetITStatus(DCMI_IT_OVF)==SET)//����ж�
		{
				over_count++;				
				DCMI_ClearITPendingBit(DCMI_IT_OVF);
		}
} 

volatile u32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ��� 
volatile u8 jpeg_data_ok=0;				//JPEG���ݲɼ���ɱ�־ 
										//0,����û�вɼ���;
										//1,���ݲɼ�����,���ǻ�û����;
										//2,�����Ѿ����������,���Կ�ʼ��һ֡����
										
//����JPEG����
//���ɼ���һ֡JPEG���ݺ�,���ô˺���,�л�JPEG BUF.��ʼ��һ֡�ɼ�.
void jpeg_data_process(void)
{
		if(jpeg_data_ok==0)	//jpeg���ݻ�δ�ɼ���?
		{
//			while (DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1)!=RESET)
//				delay_ms(10);
//			printf("�������\r\n");
//			DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);
			DMA_Cmd(DMA2_Stream1, DISABLE);//ֹͣ��ǰ���� 
			while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}//�ȴ�DMA2_Stream1������  
			jpeg_data_len=jpeg_buf_size-DMA_GetCurrDataCounter(DMA2_Stream1);//�õ��˴����ݴ���ĳ���
				
			jpeg_data_ok=1; 				//���JPEG���ݲɼ��갴��,�ȴ�������������
		}
		if(jpeg_data_ok==2)	//��һ�ε�jpeg�����Ѿ���������
		{
			DMA2_Stream1->NDTR=jpeg_buf_size;	
			DMA_SetCurrDataCounter(DMA2_Stream1,jpeg_buf_size);//���䳤��Ϊjpeg_buf_size*4�ֽ�
			DMA_Cmd(DMA2_Stream1, ENABLE);			//���´���
			jpeg_data_ok=0;						//�������δ�ɼ�
		}
} 
