#include "dgp.h"
#include "include.h"
#include "ov7670.h"

u8 ov_frame=0;  						//帧率

//DCMI中断服务函数
void DCMI_IRQHandler(void)
{
		if(DCMI_GetITStatus(DCMI_IT_FRAME)==SET)//捕获到一帧图像
		{
				jpeg_data_process(); 	//jpeg数据处理	
				DCMI_ClearITPendingBit(DCMI_IT_FRAME);//清除帧中断
				ov_frame++;	
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
			*(R+i*PIC_COL+j)=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;
		}
	}
}
void getG(u16 *jpeg,u8 *G)
{
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			*(G+i*PIC_COL+j)=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;
		}
	}
}
void getB(u16 *jpeg,u8 *B)
{
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			*(B+i*PIC_COL+j)=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;
		}
	}
}
void getY(u16 *jpeg,u8 *Y)//获得亮度
{
	u8 R,G,B;
	float y_tmp;
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
			
			y_tmp=0.3*R+0.59*G+0.11*B;
			
			*(Y+i*PIC_COL+(j+158)%PIC_COL)=y_tmp;
		}
	}
}
void getH(u16 *jpeg,u8 *H)
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
			
			if		 (R>B&&B>G){
				h_tmp=(float)((G-B)/(R-G))*PI_3_40;
			}
			else if(R>G&&G>B){
				h_tmp=(float)((G-B)/(R-B))*PI_3_40;
			}
			else if(G>R&&R>B){
				h_tmp=(float)((B-R)/(G-B)+2)*PI_3_40;
			}
			else if(G>B&&B>R){
				h_tmp=(float)((B-R)/(G-R)+2)*PI_3_40;
			}
			else if(B>R&&R>G){
				h_tmp=(float)((R-G)/(B-G)+4)*PI_3_40;
			}
			else if(B>G&&G>R){
				h_tmp=(float)((R-G)/(B-R)+4)*PI_3_40;
			}
					
			if(h_tmp<0)
			{
				h_tmp += TWO_PI*40;
			}
			
			*(H+i*PIC_COL+j)=h_tmp;
		}
	}
}
void getH_D(u16 *jpeg,u8 *H,R_info *info)
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j,count_x=0,count_y=0;
	u32 x=0,y=0;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
			
			if		 (R>B&&B>G){
				h_tmp=(float)((G-B)/(R-G))*PI_3_40;
			}
			else if(R>G&&G>B){
				h_tmp=(float)((G-B)/(R-B))*PI_3_40;
			}
			else if(G>R&&R>B){
				h_tmp=(float)((B-R)/(G-B)+2)*PI_3_40;
			}
			else if(G>B&&B>R){
				h_tmp=(float)((B-R)/(G-R)+2)*PI_3_40;
			}
			else if(B>R&&R>G){
				h_tmp=(float)((R-G)/(B-G)+4)*PI_3_40;
			}
			else if(B>G&&G>R){
				h_tmp=(float)((R-G)/(B-R)+4)*PI_3_40;
			}
					
			if(h_tmp<0)
			{
				h_tmp += TWO_PI*40;
			}
			
			if(h_tmp>166)
			{
				x+=i; //row
				count_x++;
				y+=j; //col
//				count_y++;
			}
			
//			*(H+i*PIC_COL+j)=h_tmp;
		}
	}
	
	info->x = x/count_x;
	info->y = y/count_x;
	info->ratio = (float)count_x/(PIC_ROW*PIC_COL);
	
	j=info->y;
	for(i=info->x-3;i<info->x+4;i++)
	{
		*(H+i*PIC_COL+j)=254;
	}

	i=info->x;
	for(j=info->y-3;j<info->y+4;j++)
	{
		*(H+i*PIC_COL+j)=254;
	}
}
void getH_op1(u16 *jpeg,u8 *H)//去掉MAX=B的情况，去掉H<0的情况
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
			
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
void getH_op1_getR(u16 *jpeg,u8 *H,R_info *info)//去掉MAX=B的情况，去掉H<0的情况
{
	u8 R,G,B;
	float h_tmp;
	u16 i,j,count_x=0,count_y=0;
	u32 x=0,y=0;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
					
			h_tmp=TWO_PI;
			if		 (R>B&&B>G){
				h_tmp=(float)((G-B)/(R-G))*PI_3_40;
			}
			else if(R>G&&G>B){
				h_tmp=(float)((G-B)/(R-B))*PI_3_40;
			}
			else if(G>B&&B>R){
				h_tmp=(float)((B-R)/(G-R)+2)*PI_3_40;
			}
			else if(G>R&&R>B){
				h_tmp=(float)((B-R)/(G-B)+2)*PI_3_40;
			}
					
			if(h_tmp<HIGH_THRESHOLD&&h_tmp>LOW_THRESHOLD)
			{
				x+=i; //row
				count_x++;
				y+=j; //col
				count_y++;
			}
			*(H+i*PIC_COL+j)=h_tmp;
		}
	}
	
	info->x = x/count_x;
	info->y = y/count_y;
	info->ratio = (float)count_x/(PIC_ROW*PIC_COL);
	
	j=info->y;
	for(i=info->x-3;i<info->x+4;i++)
	{
		*(H+i*PIC_COL+j)=254;
	}

	i=info->x;
	for(j=info->y-3;j<info->y+4;j++)
	{
		*(H+i*PIC_COL+j)=254;
	}

}
void get_target(u16 *jpeg,u8 *H,R_info *info)
{
	u8 R,G,B;
	u32 h_tmp;
	u16 i,j,count_x=0,count_y=0;
	u32 x=0,y=0;
	for(i=0;i<PIC_ROW;i++)
	{
		for(j=0;j<PIC_COL;j++)
		{
			R=((*(jpeg+i*PIC_COL+j))&0x1f)<<3;//R
			G=((*(jpeg+i*PIC_COL+j))&0x7e0)>>3;//G
			B=((*(jpeg+i*PIC_COL+j))&0xf800)>>8;//B
					
			h_tmp = (u32) B*2 - G*2 + R;

			if( h_tmp > 255)
			{
				h_tmp = 254;
				x+=i; //row
				count_x++;
				y+=j; //col
				count_y++;
			}
			*(H+i*PIC_COL+j)=h_tmp;
		}
	}
	
	info->x = x/count_x;
	info->y = y/count_y;
	info->ratio = (float)count_x/(PIC_ROW*PIC_COL);
	
	j=info->y;
	for(i=info->x-3;i<info->x+4;i++)
	{
		*(H+i*PIC_COL+j)=0;
	}
	i=info->x;
	for(j=info->y-3;j<info->y+4;j++)
	{
		*(H+i*PIC_COL+j)=0;
	}
}