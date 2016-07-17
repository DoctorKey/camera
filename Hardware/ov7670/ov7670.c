#include "ov7670.h"
#include "delay.h"
#include "dgp.h"
#include "ov7670cfg.h"

__align(4) u32 jpeg_buf[jpeg_buf_size];
__align(1) u8 im[PIC_ROW*PIC_COL];

//DCMI DMA配置
//DMA_Memory0BaseAddr:存储器地址    将要存储摄像头数据的内存地址(也可以是外设地址)
//DMA_BufferSize:存储器长度    0~65535
//DMA_MemoryDataSize:存储器位宽  
//DMA_MemoryDataSize:存储器位宽    @defgroup DMA_memory_data_size :DMA_MemoryDataSize_Byte/DMA_MemoryDataSize_HalfWord/DMA_MemoryDataSize_Word
//DMA_MemoryInc:存储器增长方式  @defgroup DMA_memory_incremented_mode  /** @defgroup DMA_memory_incremented_mode : DMA_MemoryInc_Enable/DMA_MemoryInc_Disable
void DCMI_DMA_Init(u32 DMA_Memory0BaseAddr,u16 DMA_BufferSize,u32 DMA_MemoryDataSize,u32 DMA_MemoryInc)
{ 
	DMA_InitTypeDef  DMA_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
	DMA_DeInit(DMA2_Stream1);
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}//等待DMA2_Stream1可配置 
	
  /* 配置 DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  //通道1 DCMI通道 
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;//外设地址为:DCMI->DR
  DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设到存储器模式
  DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;//数据传输量 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc;//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//外设数据长度:32位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize;//存储器数据长度 
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用循环模式 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//高优先级
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable; //FIFO模式        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;//使用全FIFO 
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//外设突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//存储器突发单次传输
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);//初始化DMA Stream
	
} 
void Cam_Init()
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	DCMI_InitTypeDef DCMI_InitStructure;
	  DCMI_CROPInitTypeDef DCMI_CROPInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);//DCMI 
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//DMA2
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                           RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);//使能DCMI的GPIO时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);//MCO1:PA8
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  	GPIO_Init(GPIOA, &GPIO_InitStructure);	     
    RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);//25MHz

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PE5:PWRDOWN
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);//power on
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_7);//reset

	delay_ms(10);
	OV7670_RST(0);	//复位OV7670
	delay_ms(10);
	OV7670_RST(1);	//结束复位 

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);//DCMI_HSYNC 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_PIXCLK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D5 			  
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);//DCMI_VSYNC 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);//DCMI_D6 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D7 			  
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D0 
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);//DCMI_D1 			  
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);//DCMI_D2 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);//DCMI_D3 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);//DCMI_D4 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6; 
    GPIO_Init(GPIOE, &GPIO_InitStructure);     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);		 

		DCMI_CROPInitStructure.DCMI_CaptureCount=319;
		DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount=1;
		DCMI_CROPInitStructure.DCMI_VerticalLineCount=119;
		DCMI_CROPInitStructure.DCMI_VerticalStartLine=1;
		DCMI_CROPConfig(&DCMI_CROPInitStructure);
		DCMI_CROPCmd(ENABLE);
		
  	DCMI_InitStructure.DCMI_CaptureMode =DCMI_CaptureMode_Continuous;// DCMI_CaptureMode_SnapShot;//DCMI_CaptureMode_Continuous;
  	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
  	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
  	DCMI_Init(&DCMI_InitStructure); 
		
		DCMI_ITConfig(DCMI_IT_FRAME,ENABLE);//开启帧中断 
	
		DCMI_Cmd(ENABLE);	//DCMI使能
	
		DCMI_DMA_Init((u32)&jpeg_buf,jpeg_buf_size,DMA_MemoryDataSize_Word,DMA_MemoryInc_Enable);
			
		NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=NVIC_DCMI_P;//抢占优先级1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =NVIC_DCMI_S;		//子优先级2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}

u8 OV7670_Init(void)
{
  	u8 i,id;
 	Cam_Init();
	SCCB_Init();
	OV_Reset();
	delay_ms(5);
	id=OV_ReadID();
//  	for(i=0;i<sizeof(OV7670_reg)/sizeof(OV7670_reg[0]);i++)
//  	{
//    	if(OV_WriteReg(OV7670_reg[i][0],OV7670_reg[i][1]))return 1;
//  	}
		for(i=0;i<sizeof(ov7670_init_reg_tbl)/sizeof(ov7670_init_reg_tbl[0]);i++)
		{
	   	OV_WriteReg(ov7670_init_reg_tbl[i][0],ov7670_init_reg_tbl[i][1]);
  	}

		OV7670_config_window(184+80*2,10+60*2,161,121);
		
	return 0; 
}
//DCMI,启动传输
void DCMI_Start(void)
{  
	DMA_Cmd(DMA2_Stream1, ENABLE);//开启DMA2,Stream1
	delay_ms(100);
	DCMI_CaptureCmd(ENABLE);//DCMI捕获使能  
}
//DCMI,关闭传输
void DCMI_Stop(void)
{ 
  DCMI_CaptureCmd(DISABLE);//DCMI捕获使关闭	
	
	while(DCMI->CR&0X01);		//等待传输结束 
	 	
	DMA_Cmd(DMA2_Stream1,DISABLE);//关闭DMA2,Stream1
} 
void OV7670_config_window(u16 startx,u16 starty,u16 width, u16 height)
{
	u16 endx=(startx+width*2)%784;
	u16 endy=(starty+height*2);
	u8 x_reg, y_reg;
	u8 temp;
	
	OV_ReadReg(0x32, &x_reg );
	x_reg &= 0xC0;
	OV_ReadReg(0x03, &y_reg );
	y_reg &= 0xF0;
	
	//HREF
	temp = x_reg|((endx&0x7)<<3)|(startx&0x7);
	OV_WriteReg(0x32, temp );
	temp = (startx&0x7F8)>>3;
	OV_WriteReg(0x17, temp );
	temp = (endx&0x7F8)>>3;
	OV_WriteReg(0x18, temp );
	//VREF
	temp = y_reg|((endy&0x3)<<2)|(starty&0x3);
	OV_WriteReg(0x03, temp );
	temp = (starty&0x3FC)>>2;
	OV_WriteReg(0x19, temp );
	temp = (endy&0x3FC)>>2;
	OV_WriteReg(0x1A, temp );
}		
void OV_Reset(void)
{
	OV_WriteReg(0x12,0x80);
}

u8 OV_ReadID(void)
{
	u8 temp;
	OV_ReadReg(0x0b,&temp);
  	return temp;
}
/////////////////////////////////////
void SCCB_Init(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  //SCCB_SIC:PB10
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			  //SCCB_SID:PB11
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCCB_SID_OUT(void)//设置SCCB_SID为输出
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void SCCB_SID_IN(void)//设置SCCB_SID为输入
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCCB_Start(void)
{
    SCCB_SID_H();     //数据线高电平
    delay_us(50);
    SCCB_SIC_H();	   //在时钟线高的时候数据线由高至低
    delay_us(50);
    SCCB_SID_L();
    delay_us(50);
    SCCB_SIC_L();	 //数据线恢复低电平，单操作函数必要
    delay_us(50);
}

void SCCB_Stop(void)
{
    SCCB_SID_L();
    delay_us(50);
    SCCB_SIC_H();	
    delay_us(50);  
    SCCB_SID_H();	
    delay_us(50);  
}

void noAck(void)
{	
	SCCB_SID_H();	
	delay_us(50);	
	SCCB_SIC_H();	
	delay_us(50);	
	SCCB_SIC_L();	
	delay_us(50);	
	SCCB_SID_L();	
	delay_us(50);
}

u8 SCCB_Write(u8 m_data)
{
	u8 j,tem;

	for(j=0;j<8;j++) //循环8次发送数据
	{
		if(m_data&0x80)SCCB_SID_H();//(m_data<<j)
		else SCCB_SID_L();
		m_data<<=1;
		delay_us(50);
		SCCB_SIC_H();	
		delay_us(50);
		SCCB_SIC_L();	
		delay_us(50);
	}
	delay_us(10);
	SCCB_DATA_IN;
	delay_us(50);
	SCCB_SIC_H();	
	delay_us(10);
	if(SCCB_SID_STATE)tem=1;//SDA=1发送失败
	else tem=0;//SDA=0发送成功，返回1
	SCCB_SIC_L();	
	delay_us(50);	
    SCCB_DATA_OUT;
	return tem;  //false 1,success 0
}

//SCCB 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
u8 SCCB_Read(void)
{
	u8 read,j;
	read=0x00;
	
	SCCB_DATA_IN;
	delay_us(50);
	for(j=8;j>0;j--) //循环8次接收数据
	{		     
		delay_us(50);
		SCCB_SIC_H();
		//delay_us(50);
		read=read<<1;
		if(SCCB_SID_STATE)read++; 
		delay_us(50);
		SCCB_SIC_L();	
	}	
    SCCB_DATA_OUT;
	return read;
}

//写OV7670寄存器
u8 OV_WriteReg(u8 regID, u8 regDat)
{
	SCCB_Start();//发送SCCB 总线开始传输命令
	if(SCCB_Write(0x42))//写地址
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 1;//错误返回
	}
	delay_us(10);
  	if(SCCB_Write(regID))//寄存器ID
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 2;//错误返回
	}
	delay_us(10);
  	if(SCCB_Write(regDat))//写数据到积存器
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 3;//错误返回
	}
  	SCCB_Stop();//发送SCCB 总线停止传输命令	
  	return 0;//成功返回
}

//读OV7660寄存器
u8 OV_ReadReg(u8 regID, u8 *regDat)
{
	//通过写操作设置寄存器地址
	SCCB_Start();
	if(SCCB_Write(0x42))//写地址
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 1;//错误返回
	}
	delay_us(10);
  	if(SCCB_Write(regID))//积存器ID
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 2;//错误返回
	}
	SCCB_Stop();//发送SCCB 总线停止传输命令	
	delay_us(10);	
	//设置寄存器地址后，才是读
	SCCB_Start();
	if(SCCB_Write(0x43))//读地址
	{
		SCCB_Stop();//发送SCCB 总线停止传输命令
		return 3;//错误返回
	}
	delay_us(10);
  	*regDat=SCCB_Read();//返回读到的值
  	noAck();//发送NACK命令
  	SCCB_Stop();//发送SCCB 总线停止传输命令
  	return 0;//成功返回
}


