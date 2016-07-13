#include "dgp.h"
#include "include.h"
#include "ov7670.h"

u8 ov_frame=0;  						//֡��

//DCMI�жϷ�����
void DCMI_IRQHandler(void)
{
		if(DCMI_GetITStatus(DCMI_IT_FRAME)==SET)//����һ֡ͼ��
		{
				jpeg_data_process(); 	//jpeg���ݴ���	
				DCMI_ClearITPendingBit(DCMI_IT_FRAME);//���֡�ж�
				ov_frame++;	
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
void getRGB(u16 jpeg,u8 **rgb)
{
	*(rgb[0])=jpeg&0x1f;//R
	*(rgb[1])=(jpeg&0x7e0)>>5;//G
	*(rgb[2])=(jpeg&0xf800)>>11;//B
}	
void getR(u16 *jpeg,u8 *R)
{
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			*(R+i*PIC_COL+j)=((*(jpeg+i*PIC_COL+j))&0x1f)*8;
		}
	}
}
void getG()
{}
void getB()
{}
void getH(u16 *jpeg,u8 *H)
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=(*(jpeg+i*PIC_COL+j))&0x1f;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>5;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>11;//B
			
			R=R*8;
			B=B*8;
			G=G*4;
			
			if		 (R>B&&B>G){
				h_tmp=((G-B)/(R-G))*PI_3;
			}
			else if(G>B&&B>R){
				h_tmp=((B-R)/(G-R)+2)*PI_3;
			}
			else if(B>R&&R>G){
				h_tmp=((R-G)/(B-G)+4)*PI_3;
			}
			else if(G>R&&R>B){
				h_tmp=((B-R)/(G-B)+2)*PI_3;
			}
			else if(B>G&&G>R){
				h_tmp=((R-G)/(B-R)+4)*PI_3;
			}
			else if(R>G&&G>B){
				h_tmp=((G-B)/(R-B))*PI_3;
			}

//			H=(u8)((h_tmp<0?h_tmp+TWO_PI:h_tmp)*40);			
			*(H+i*PIC_COL+j)=((h_tmp<0?h_tmp+TWO_PI:h_tmp)*40);
		}
	}
}

void getH_op1(u16 *jpeg,u8 *H)//ȥ��MAX=B�������ȥ��H<0�����
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=(*(jpeg+i*PIC_COL+j))&0x1f;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>5;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>11;//B
			
			R=R*8;
			B=B*8;
			G=G*4;
			
			h_tmp=TWO_PI;
			if		 (R>B&&B>G){
				h_tmp=((G-B)/(R-G))*PI_3;
			}
			else if(R>G&&G>B){
				h_tmp=((G-B)/(R-B))*PI_3;
			}
			else if(G>B&&B>R){
				h_tmp=((B-R)/(G-R)+2)*PI_3;
			}
			else if(G>R&&R>B){
				h_tmp=((B-R)/(G-B)+2)*PI_3;
			}
						
			*(H+i*PIC_COL+j)=(h_tmp*40);
		}
	}
}
