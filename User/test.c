#include "test.h"
#include "dgp.h"
#include "include.h"

void im_send(u8* im)
{
	u32 i;
	i=PIC_COL*PIC_ROW;
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void matlab_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u8 *p;
	i=jpeg_buf_size*4;
	p=(u8*)jpeg_buf;
	LED0(On);
	USART_SendString_bysize(USART2,p,i);
	LED0(Off);
}
void R_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getR(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void G_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getG(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void B_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getB(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void H_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getH(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void H_test_op1(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getH_op1(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void Y_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getY(jpeg,im);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
R_info info;
void D_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getH_op1_getR(jpeg,im,&info);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void D0_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	getH_D(jpeg,im,&info);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
void D2_test(u32* jpeg_buf,u8* im)
{
	u32 i;
	u16 *jpeg;
	i=PIC_COL*PIC_ROW;
	jpeg=(u16*)jpeg_buf;
	get_target(jpeg,im,&info);
	LED0(On);
	USART_SendString_bysize(USART2,im,i);
	USART_SendData(USART2,255);
	LED0(Off);
}
char mode='Y';
void test_mode(u8 command)
{
	switch(command)
	{
		case 1:mode='M';
			break;
		case 2:mode='R';
			break;
		case 3:mode='G';
			break;
		case 4:mode='B';
			break;
		case 5:mode='H';
			break;
		case 6:mode='Y';
			break;
		case 7:mode='D';
			break;
		case 8:mode='h';
			break;
		case 9:mode='d';
			break;
		case 10:mode='e';
			break;
	}
}

