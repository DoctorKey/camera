#include "test.h"
#include "dgp.h"
#include "include.h"

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
char mode='H';
void test_mode(char command)
{
	mode = command;
}

