#include "lcd.h"
#include "delay.h"


void LCD_LineConf(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB , ENABLE);

	/*配置液晶屏的背光控制管脚*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;											  //设置管脚模式为输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										  //设置翻转速度为100Mhz，M4就是快啊
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;											  //设置输出类型为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;												  //设置管脚为Pin_5,根据自己液晶接法设置
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;										  //设置上/下拉电阻为无上拉下拉电阻		
    GPIO_Init(GPIOB, &GPIO_InitStructure);													  //初始化GPIOB的Pin_5

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//(RS)
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);	   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//(CS) 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
}

void LCD_FSMCConf(void)
{
  	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;

  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;
  	p.FSMC_AddressHoldTime = 0;
  	p.FSMC_DataSetupTime = 9;
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void LCD_WriteReg(u8 Reg, u16 Value)
{
  	LCD_REG=Reg;
  	LCD_RAM=Value;
}

u16 LCD_ReadReg(u8 Reg)
{
  	LCD_REG=Reg;
  	return (LCD_RAM);
}

void LCD_WriteRAM(u16 RGB_Code)
{
  	LCD_RAM=RGB_Code;
}

u16 LCD_ReadRAM(void)
{
  	LCD_REG=0x22; 
  	return LCD_RAM;
}

void LCD_Init(void)
{ 
  	u32 lcdid=0;

   	LCD_LineConf();
  	LCD_FSMCConf();
  	delay_ms(5); 
  	lcdid=LCD_ReadReg(0x00);  
  	if(lcdid == 0x9320)
  	{
		LCD_WriteReg(0xE5,0x8000);
		LCD_WriteReg(0x00,0x0001);
		LCD_WriteReg(0x01,0x0100);
		LCD_WriteReg(0x02,0x0700);
		LCD_WriteReg(0x03,0x1030);
		LCD_WriteReg(0x04,0x0000);
		LCD_WriteReg(0x08,0x0202);
		LCD_WriteReg(0x09,0x0000);
		LCD_WriteReg(0x0A,0x0000);
		LCD_WriteReg(0x0B,0x0000);
		LCD_WriteReg(0x0C,0x0000);
		LCD_WriteReg(0x0F,0x0000);
		LCD_WriteReg(0x10,0x0000);
		LCD_WriteReg(0x11,0x0000);
		LCD_WriteReg(0x12,0x0000);
		LCD_WriteReg(0x13,0x0000);
		delay_ms(20);
		LCD_WriteReg(0x10,0x17B0);
		LCD_WriteReg(0x11,0x0137);
		delay_ms(5);
		LCD_WriteReg(0x12,0x0139);
		delay_ms(5);
		LCD_WriteReg(0x13,0x1d00);
		LCD_WriteReg(0x29,0x0013);
		delay_ms(5);
		LCD_WriteReg(0x20,0x0000);
		LCD_WriteReg(0x21,0x0000);
		LCD_WriteReg(0x30,0x0006);
		LCD_WriteReg(0x31,0x0101);
		LCD_WriteReg(0x32,0x0003);
		LCD_WriteReg(0x35,0x0106);
		LCD_WriteReg(0x36,0x0b02);
		LCD_WriteReg(0x37,0x0302);
		LCD_WriteReg(0x38,0x0707);
		LCD_WriteReg(0x39,0x0007);
		LCD_WriteReg(0x3C,0x0600);
		LCD_WriteReg(0x3D,0x020b);
		LCD_WriteReg(0x50,0x0000);
		LCD_WriteReg(0x51,0x00EF);
		LCD_WriteReg(0x52,0x0000);
		LCD_WriteReg(0x53,0x013F);
		LCD_WriteReg(0x60,0x2700);
		LCD_WriteReg(0x61,0x0001);
		LCD_WriteReg(0x6A,0x0000);
		LCD_WriteReg(0x80,0x0000);
		LCD_WriteReg(0x81,0x0000);
		LCD_WriteReg(0x82,0x0000);
		LCD_WriteReg(0x83,0x0000);
		LCD_WriteReg(0x84,0x0000);
		LCD_WriteReg(0x85,0x0000);
		LCD_WriteReg(0x90,0x0010);
		LCD_WriteReg(0x92,0x0000);
		LCD_WriteReg(0x93,0x0003);
		LCD_WriteReg(0x95,0x0110);
		LCD_WriteReg(0x97,0x0000);
		LCD_WriteReg(0x98,0x0000);
		LCD_WriteReg(0x03,0x1018);
		LCD_WriteReg(0x07,0x0173); 
  	}
  	else if(lcdid == 0x9325)
  	{
		LCD_WriteReg(0x00,0x0001);
		LCD_WriteReg(0x01,0x0100);
		LCD_WriteReg(0x02,0x0700);
		LCD_WriteReg(0x03,0x1018);
		LCD_WriteReg(0x04,0x0000);
		LCD_WriteReg(0x08,0x0202);
		LCD_WriteReg(0x09,0x0000);
		LCD_WriteReg(0x0A,0x0000);
		LCD_WriteReg(0x0C,0x0000);
		LCD_WriteReg(0x0D,0x0000);
		LCD_WriteReg(0x0F,0x0000);
		LCD_WriteReg(0x10,0x0000);
		LCD_WriteReg(0x11,0x0000);
		LCD_WriteReg(0x12,0x0000);
		LCD_WriteReg(0x13,0x0000);
		delay_ms(20);
		LCD_WriteReg(0x10,0x17B0);
		LCD_WriteReg(0x11,0x0137);
		delay_ms(5);
		LCD_WriteReg(0x12,0x0139);
		delay_ms(5);
		LCD_WriteReg(0x13,0x1d00);
		LCD_WriteReg(0x29,0x0013);
		delay_ms(5);
		LCD_WriteReg(0x20,0x0000);
		LCD_WriteReg(0x21,0x0000);
		LCD_WriteReg(0x30,0x0007);
		LCD_WriteReg(0x31,0x0302);
		LCD_WriteReg(0x32,0x0105);
		LCD_WriteReg(0x35,0x0206);
		LCD_WriteReg(0x36,0x0808);
		LCD_WriteReg(0x37,0x0206);
		LCD_WriteReg(0x38,0x0504);
		LCD_WriteReg(0x39,0x0007);
		LCD_WriteReg(0x3C,0x0105);
		LCD_WriteReg(0x3D,0x0808);
		LCD_WriteReg(0x50,0x0000);
		LCD_WriteReg(0x51,0x00EF);
		LCD_WriteReg(0x52,0x0000);
		LCD_WriteReg(0x53,0x013F);
		LCD_WriteReg(0x60,0xA700);
		LCD_WriteReg(0x61,0x0001);
		LCD_WriteReg(0x6A,0x0000);
		LCD_WriteReg(0x80,0x0000);
		LCD_WriteReg(0x81,0x0000);
		LCD_WriteReg(0x82,0x0000);
		LCD_WriteReg(0x83,0x0000);
		LCD_WriteReg(0x84,0x0000);
		LCD_WriteReg(0x85,0x0000);
		LCD_WriteReg(0x90,0x0010);
		LCD_WriteReg(0x92,0x0000);
		LCD_WriteReg(0x93,0x0003);
		LCD_WriteReg(0x95,0x0110);
		LCD_WriteReg(0x97,0x0000);
		LCD_WriteReg(0x98,0x0000);
		LCD_WriteReg(0x03,0x1018);
		LCD_WriteReg(0x07,0x0133);
  	}
  	else if(lcdid==0x4531)
  	{		
		LCD_WriteReg(0x00,0x0001);
		LCD_WriteReg(0x10,0x0628);
		LCD_WriteReg(0x12,0x0006);
		LCD_WriteReg(0x13,0x0A32);
		LCD_WriteReg(0x11,0x0040);
		LCD_WriteReg(0x15,0x0050);
		LCD_WriteReg(0x12,0x0016);
		delay_ms(15);
		LCD_WriteReg(0x10,0x5660);
		delay_ms(15);
		LCD_WriteReg(0x13,0x2A4E);
		LCD_WriteReg(0x01,0x0100);
		LCD_WriteReg(0x02,0x0300);	
		LCD_WriteReg(0x03,0x1018);
		LCD_WriteReg(0x08,0x0202);
		LCD_WriteReg(0x0A,0x0000);
		LCD_WriteReg(0x30,0x0000);
		LCD_WriteReg(0x31,0x0402);
		LCD_WriteReg(0x32,0x0106);
		LCD_WriteReg(0x33,0x0700);
		LCD_WriteReg(0x34,0x0104);
		LCD_WriteReg(0x35,0x0301);
		LCD_WriteReg(0x36,0x0707);
		LCD_WriteReg(0x37,0x0305);
		LCD_WriteReg(0x38,0x0208);
		LCD_WriteReg(0x39,0x0F0B);
		delay_ms(15);
		LCD_WriteReg(0x41,0x0002);
		LCD_WriteReg(0x60,0x2700);
		LCD_WriteReg(0x61,0x0001);
		LCD_WriteReg(0x90,0x0119);
		LCD_WriteReg(0x92,0x010A);
		LCD_WriteReg(0x93,0x0004);
		LCD_WriteReg(0xA0,0x0100);
		delay_ms(15);
		delay_ms(15);
		LCD_WriteReg(0x07,0x0133);
		delay_ms(15);
		LCD_WriteReg(0xA0,0x0000);
		delay_ms(20);
  	} 
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	LCD_Clear(BLUE);
	LCD_Font(&Font16x24);
	LCD_Mode(4);							 
}

void LCD_Font(sFONT *font)
{
  	Efont=font;
}

void LCD_Cursor(u16 Xpos, u16 Ypos)
{
  	LCD_WriteReg(0x20, Xpos);
  	LCD_WriteReg(0x21, Ypos);
}

//X,Y为窗口左下角座标,注意设置窗口后座标不要超出该范围
void LCD_Window(u16 Xpos, u16 Ypos, u16 Height, u16 Width)
{
  	if(Xpos>=Height)LCD_WriteReg(0x50,(Xpos-Height+1));
  	else LCD_WriteReg(0x50,0);
  	LCD_WriteReg(0x51,Xpos);
  	if(Ypos>=Width)LCD_WriteReg(0x52,(Ypos-Width+1)); 
  	else LCD_WriteReg(0x52,0);
  	LCD_WriteReg(0x53,Ypos);
  	LCD_Cursor(Xpos,Ypos);
}

//设置刷屏模式
void LCD_Mode(u8 mode)
{
	switch(mode)//常用4(横屏)和7(竖屏)
	{
		case 1:LCD_WriteReg(0x03,0x1000);break;//向左向上:←↖
		case 2:LCD_WriteReg(0x03,0x1008);break;//向上向左:↑↖
		case 3:LCD_WriteReg(0x03,0x1010);break;//向右向上:→↗
		case 4:LCD_WriteReg(0x03,0x1018);break;//向上向右:↑↗
		case 5:LCD_WriteReg(0x03,0x1020);break;//向左向下:←↙
		case 6:LCD_WriteReg(0x03,0x1028);break;//向下向左:↓↙
		case 7:LCD_WriteReg(0x03,0x1030);break;//向右向下:→↘
		case 8:LCD_WriteReg(0x03,0x1038);break;//向下向右:↓↘
	}
}

void LCD_Clear(u16 Color)
{
  	u32 index=0;
 
  	LCD_Cursor(0x00, 319); 
  	LCD_REG=0x22;//WriteRAM_Prepare 
  	for(index=0;index<76800;index++)LCD_RAM=Color;
}

void LCD_Point(u16 xpos, u16 ypos,u16 color)
{
	LCD_Cursor(xpos,ypos);
	LCD_REG=0x22;//WriteRAM_Prepare 
	LCD_RAM=color;
}

void LCD_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_Point(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}

void LCD_Rect(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	LCD_Line(x1,y1,x2,y1,color);
	LCD_Line(x1,y1,x1,y2,color);
	LCD_Line(x1,y2,x2,y2,color);
	LCD_Line(x2,y1,x2,y2,color);
}

void LCD_Circle(u16 Xpos, u16 Ypos, u16 Radius, u16 color)
{
  	s32  Dec;
  	u32  CurX;
  	u32  CurY;
	 
  	CurX=0;
  	CurY=Radius;   
  	Dec=3-(Radius<<1);
  	while(CurX<=CurY)
  	{
		LCD_Point(Xpos+CurX,Ypos+CurY,color);
		LCD_Point(Xpos+CurX,Ypos-CurY,color);
		LCD_Point(Xpos-CurX,Ypos+CurY,color);
		LCD_Point(Xpos-CurX,Ypos-CurY,color);
		LCD_Point(Xpos+CurY,Ypos+CurX,color);
		LCD_Point(Xpos+CurY,Ypos-CurX,color);
		LCD_Point(Xpos-CurY,Ypos+CurX,color);
		LCD_Point(Xpos-CurY,Ypos-CurX,color);
		if(Dec<0)Dec+=(CurX<<2)+6;
	    else
	    {
	      	Dec+=((CurX-CurY)<<2)+10;
	      	CurY--;
	    }
	    CurX++;
  	}
}


void LCD_Fill(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{          
	u16 i,j;
	u16 xlen=0;

	xlen=y2-y1+1;	   
	for(i=x1;i<=x2;i++)
	{
	 	LCD_Cursor(i,y2);
		LCD_REG=0x22;      	  
		for(j=0;j<xlen;j++)LCD_WriteRAM(color); 	  
	}						  	    
}  

void LCD_Char(u16 Xpos, u16 Ypos, u8 Ascii, u16 color)
{
	const u16 *c;
  	u16 Xaddr=0; 
  	u32 index=0,i=0;
					 
  	Xaddr=Xpos;
	c=&Efont->table[(Ascii-32)*Efont->Height]; 
  	LCD_Cursor(Xaddr, Ypos);  
  	for(index=0;index<Efont->Height;index++)
  	{
    	LCD_REG=0x22;//WriteRAM_Prepare
    	for(i=0;i<Efont->Width;i++)
    	{  
			if((((c[index]&((0x80<<((Efont->Width/12)*8))>>i))==0x00)&&(Efont->Width<=12))
			||(((c[index]&(0x1<<i))==0x00)&&(Efont->Width>12)))LCD_WriteRAM(BLUE);
      		else LCD_WriteRAM(color); 
    	}
    	Xaddr++;
    	LCD_Cursor(Xaddr, Ypos);
  	}
}

void LCD_String(u16 xpos, u16 ypos, u8 *ptr, u16 color)
{
  	u16 refypos=LCD_WIDTH-xpos;

  	while((*ptr!=0)&(((refypos+1)&0xFFFF)>=Efont->Width))
  	{
    	LCD_Char(ypos,refypos,*ptr,color);
    	refypos-=Efont->Width;
    	ptr++;
  	}
}

//m^n函数
u32 mypow(u8 m,u8 n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}			 
	 
void LCD_Num(u16 x, u16 y, s32 num, u8 len, u16 color)
{         	
	u8 t,temp;
	u8 enshow=0;
	t=0;
	if(num<0)
	{
		LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,'-',color);
		num=-num;
		t++;
	}						   
	for(;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,' ',color);
				continue;
			}else enshow=1; 		 	 
		}
	 	LCD_Char(y,LCD_WIDTH-x-(Efont->Width)*t,temp+'0',color); 
	}
} 

