#include "glcd.h"
/*******************液晶屏硬件连接**********************

PD14 -----FSMC_D0  ----D0
PD15 -----FSMC_D1  ----D1
PD0   -----FSMC_D2  ----D2
PD1   -----FSMC_D3  ----D3
PE7    -----FSMC_D4  ---D4
PE8    -----FSMC_D5  ---D5
PE9    -----FSMC_D6  ---D6
PE10  -----FSMC_D7   ----D7
PE11  -----FSMC_D8   ----D8
PE12  -----FSMC_D9   ----D9
PE13  -----FSMC_D10   ----D10
PE14  -----FSMC_D11   ----D11
PE15  -----FSMC_D12   ----D12
PD8   -----FSMC_D13   ----D13
PD9   -----FSMC_D14   ----D14
PD10 -----FSMC_D15   ----D15
PD4   -----FSMC_NOE -----RD
PD5   -----FSMC_NWE ----WR
PD7    -----FSMC_NE1  ----CS
PD11 -----FSMC_A16   ----RS

PB5-------------------LCD_BL

/*液晶屏的前景色和背景色*/
static __IO uint16_t TextColor = 0x0000, BackColor = 0xFFFF;
/**************************************************************************************************************
 * 函数名：GPIO_AF_FSMC_Config()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：配置LCD连接的GPIO复用连接到FSMC
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void GPIO_AF_FSMC_Config(void)
{
  /*配置GPIOD相应的管脚复用连接到FSMC*/
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);	        //配置GPIOD的Pin0复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);			//配置GPIOD的Pin1复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);			//配置GPIOD的Pin4复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);			//配置GPIOD的Pin5复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);			//配置GPIOD的Pin7复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);			//配置GPIOD的Pin8复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);			//配置GPIOD的Pin9复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);		//配置GPIOD的Pin10复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);		//配置GPIOD的Pin11复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);		//配置GPIOD的Pin14复用连接到FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);		//配置GPIOD的Pin15复用连接到FSMC
   /*配置GPIOE相应的管脚复用连接到FSMC*/
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);			//配置GPIOE的Pin7复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);			//配置GPIOE的Pin8复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);			//配置GPIOE的Pin9复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);		//配置GPIOE的Pin10复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);		//配置GPIOE的Pin11复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);		//配置GPIOE的Pin12复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);	    //配置GPIOE的Pin13复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);		//配置GPIOE的Pin14复用连接到FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);		//配置GPIOE的Pin15复用连接到FSMC
}
/**************************************************************************************************************
 * 函数名：LCD_GPIO_Config()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：配置LCD的GPIO管脚与FSMC连接
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;		                                              //定义GPIO初始化结构体
     
    /* 使能FSMC的AHB3时钟，这里注意，不同芯片总线会不同 */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
    
    /* 使能GPIOB，GPIOD，GPIOE的AHB1时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE , ENABLE);
   	 /*配置液晶屏的背光控制管脚*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;											  //设置管脚模式为输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										  //设置翻转速度为100Mhz，M4就是快啊
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;											  //设置输出类型为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;												  //设置管脚为Pin_5,根据自己液晶接法设置
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;										  //设置上/下拉电阻为无上拉下拉电阻		
    GPIO_Init(GPIOB, &GPIO_InitStructure);													  //初始化GPIOB的Pin_5
    		   
    /* 配置基于FSMC的液晶屏的数据线
	 * 液晶屏数据线：FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10
	 */	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										  //设置翻转速度为100Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;											  //设置管脚模式为复用模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);													  //初始化GPIOB的Pin_0，Pin_，Pin_2，
	                                                                    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    /* 配置基于FSMC的液晶屏控制线
	 * PD4-FSMC_NOE  :LCD-RD
   * PD5-FSMC_NWE  :LCD-WR
	 * PD7-FSMC_NE1  :LCD-CS
   * PD11-FSMC_A16 :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    GPIO_AF_FSMC_Config();				             //在F407中必须加上这个复用连接配置，否则不能连接到FSMC
    GPIO_SetBits(GPIOB, GPIO_Pin_5);			 
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		  
    GPIO_SetBits(GPIOD, GPIO_Pin_5);		 
    GPIO_SetBits(GPIOD, GPIO_Pin_7);		 
   
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    GPIO_SetBits(GPIOD, GPIO_Pin_6); 	
}

/**************************************************************************************************************
 * 函数名：LCD_FSMC_Config()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：配置LCD的FSMC
 * 调用  ：内部调用        
 *****************************************************************************************************************/
static void LCD_FSMC_Config(void)
{    
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;
	  LCD_GPIO_Config();                                                     //LCD管脚配置
  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;                                           //地址建立时间
  	p.FSMC_AddressHoldTime = 0;                                            //地址保持时间
  	p.FSMC_DataSetupTime = 9;                                              //数据建立时间
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;                                  // 用模式A控制LCD
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
/**************************************************************************************************************
 * 函数名：GLCD_WriteReg()
 * 输入  ：uint8_t LCD_Reg 寄存器地址, uint16_t LCD_RegValue 寄存器的值
 * 输出  ：void
 * 描述  ：写LCD寄存器函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /*写寄存器地址*/
  LCD_REG = LCD_Reg;
  /*写入寄存器值*/
  LCD_RAM = LCD_RegValue;
}
/**************************************************************************************************************
 * 函数名：LCD_ReadReg()
 * 输入  ：uint8_t LCD_Reg 需要读取的寄存器地址
 * 输出  ：uint16_t 寄存器的值
 * 描述  ：读取LCD寄存器的值
 * 调用  ：外部调用        
 *****************************************************************************************************************/
uint16_t GLCD_ReadReg(uint8_t LCD_Reg)
{
  /*写寄存器地址*/
  LCD_REG = LCD_Reg;
  /*读出寄存器值并返回*/
  return (LCD_RAM);
}
/**************************************************************************************************************
 * 函数名：GLCD_WriteRAM_Start()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：开始写LCD的RAM
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_WriteRAM_Start(void)
{
  LCD_REG = 0x22;
}

/**************************************************************************************************************
 * 函数名：GLCD_WriteRAM()
 * 输入  ：uint16_t RGB_data  16bit颜色数据
 * 输出  ：void
 * 描述  ：向LCD的RAM写数据
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_WriteRAM(uint16_t RGB_data)
{
  /*向LCD的RAM写数据*/
  LCD_RAM = RGB_data;
}

/**************************************************************************************************************
 * 函数名：LCD_ReadRAM()
 * 输入  ：void
 * 输出  ：uint16_t  16bit颜色值
 * 描述  ：读取LCD的RAM数据
 * 调用  ：外部调用        
 *****************************************************************************************************************/
uint16_t GLCD_ReadRAM(void)
{ 
	uint16_t dumry;
  LCD_REG = 0x22; /*选择RAM寄存器*/
	dumry=LCD_RAM;   /*假读*/
  /*读取16bit RAM值*/
  return LCD_RAM;
}

/**************************************************************************************************************
 * 函数名：LCD_DisplayOn()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD打开显示
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DisplayOn(void)
{
  /*打开显示 */
  GLCD_WriteReg(0x07, 0x0173); /*设置LCD为262K色并打开显示*/
}

/**************************************************************************************************************
 * 函数名：LCD_DisplayOff()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD关闭显示
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DisplayOff(void)
{
  /*关闭显示*/
  GLCD_WriteReg(0x07, 0x0); 
}
/**************************************************************************************************************
 * 函数名：LCD_Init()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD初始化函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_Init(void)
{ 
  	u32 lcdid=0;

   	LCD_FSMC_Config();
  	delay_nms(5); 
  	lcdid=GLCD_ReadReg(0x00);  
  	if(lcdid == 0x9320)
  	{
		GLCD_WriteReg(0xE5,0x8000);
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0700);
		GLCD_WriteReg(0x03,0x1030);
		GLCD_WriteReg(0x04,0x0000);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x09,0x0000);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x0B,0x0000);
		GLCD_WriteReg(0x0C,0x0000);
		GLCD_WriteReg(0x0F,0x0000);
		GLCD_WriteReg(0x10,0x0000);
		GLCD_WriteReg(0x11,0x0000);
		GLCD_WriteReg(0x12,0x0000);
		GLCD_WriteReg(0x13,0x0000);
		delay_nms(20);
		GLCD_WriteReg(0x10,0x17B0);
		GLCD_WriteReg(0x11,0x0137);
		delay_nms(5);
		GLCD_WriteReg(0x12,0x0139);
		delay_nms(5);
		GLCD_WriteReg(0x13,0x1d00);
		GLCD_WriteReg(0x29,0x0013);
		delay_nms(5);
		GLCD_WriteReg(0x20,0x0000);
		GLCD_WriteReg(0x21,0x0000);
		GLCD_WriteReg(0x30,0x0006);
		GLCD_WriteReg(0x31,0x0101);
		GLCD_WriteReg(0x32,0x0003);
		GLCD_WriteReg(0x35,0x0106);
		GLCD_WriteReg(0x36,0x0b02);
		GLCD_WriteReg(0x37,0x0302);
		GLCD_WriteReg(0x38,0x0707);
		GLCD_WriteReg(0x39,0x0007);
		GLCD_WriteReg(0x3C,0x0600);
		GLCD_WriteReg(0x3D,0x020b);
		GLCD_WriteReg(0x50,0x0000);
		GLCD_WriteReg(0x51,0x00EF);
		GLCD_WriteReg(0x52,0x0000);
		GLCD_WriteReg(0x53,0x013F);
		GLCD_WriteReg(0x60,0x2700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x6A,0x0000);
		GLCD_WriteReg(0x80,0x0000);
		GLCD_WriteReg(0x81,0x0000);
		GLCD_WriteReg(0x82,0x0000);
		GLCD_WriteReg(0x83,0x0000);
		GLCD_WriteReg(0x84,0x0000);
		GLCD_WriteReg(0x85,0x0000);
		GLCD_WriteReg(0x90,0x0010);
		GLCD_WriteReg(0x92,0x0000);
		GLCD_WriteReg(0x93,0x0003);
		GLCD_WriteReg(0x95,0x0110);
		GLCD_WriteReg(0x97,0x0000);
		GLCD_WriteReg(0x98,0x0000);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x07,0x0173); 
  	}
  	else if(lcdid == 0x9325)
  	{
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0700);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x04,0x0000);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x09,0x0000);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x0C,0x0000);
		GLCD_WriteReg(0x0D,0x0000);
		GLCD_WriteReg(0x0F,0x0000);
		GLCD_WriteReg(0x10,0x0000);
		GLCD_WriteReg(0x11,0x0000);
		GLCD_WriteReg(0x12,0x0000);
		GLCD_WriteReg(0x13,0x0000);
		delay_nms(20);
		GLCD_WriteReg(0x10,0x17B0);
		GLCD_WriteReg(0x11,0x0137);
		delay_nms(5);
		GLCD_WriteReg(0x12,0x0139);
		delay_nms(5);
		GLCD_WriteReg(0x13,0x1d00);
		GLCD_WriteReg(0x29,0x0013);
		delay_nms(5);
		GLCD_WriteReg(0x20,0x0000);
		GLCD_WriteReg(0x21,0x0000);
		GLCD_WriteReg(0x30,0x0007);
		GLCD_WriteReg(0x31,0x0302);
		GLCD_WriteReg(0x32,0x0105);
		GLCD_WriteReg(0x35,0x0206);
		GLCD_WriteReg(0x36,0x0808);
		GLCD_WriteReg(0x37,0x0206);
		GLCD_WriteReg(0x38,0x0504);
		GLCD_WriteReg(0x39,0x0007);
		GLCD_WriteReg(0x3C,0x0105);
		GLCD_WriteReg(0x3D,0x0808);
		GLCD_WriteReg(0x50,0x0000);
		GLCD_WriteReg(0x51,0x00EF);
		GLCD_WriteReg(0x52,0x0000);
		GLCD_WriteReg(0x53,0x013F);
		GLCD_WriteReg(0x60,0xA700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x6A,0x0000);
		GLCD_WriteReg(0x80,0x0000);
		GLCD_WriteReg(0x81,0x0000);
		GLCD_WriteReg(0x82,0x0000);
		GLCD_WriteReg(0x83,0x0000);
		GLCD_WriteReg(0x84,0x0000);
		GLCD_WriteReg(0x85,0x0000);
		GLCD_WriteReg(0x90,0x0010);
		GLCD_WriteReg(0x92,0x0000);
		GLCD_WriteReg(0x93,0x0003);
		GLCD_WriteReg(0x95,0x0110);
		GLCD_WriteReg(0x97,0x0000);
		GLCD_WriteReg(0x98,0x0000);
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x07,0x0133);
  	}
  	else if(lcdid==0x4531)
  	{		
		GLCD_WriteReg(0x00,0x0001);
		GLCD_WriteReg(0x10,0x0628);
		GLCD_WriteReg(0x12,0x0006);
		GLCD_WriteReg(0x13,0x0A32);
		GLCD_WriteReg(0x11,0x0040);
		GLCD_WriteReg(0x15,0x0050);
		GLCD_WriteReg(0x12,0x0016);
		delay_nms(15);
		GLCD_WriteReg(0x10,0x5660);
		delay_nms(15);
		GLCD_WriteReg(0x13,0x2A4E);
		GLCD_WriteReg(0x01,0x0100);
		GLCD_WriteReg(0x02,0x0300);	
		GLCD_WriteReg(0x03,0x1018);
		GLCD_WriteReg(0x08,0x0202);
		GLCD_WriteReg(0x0A,0x0000);
		GLCD_WriteReg(0x30,0x0000);
		GLCD_WriteReg(0x31,0x0402);
		GLCD_WriteReg(0x32,0x0106);
		GLCD_WriteReg(0x33,0x0700);
		GLCD_WriteReg(0x34,0x0104);
		GLCD_WriteReg(0x35,0x0301);
		GLCD_WriteReg(0x36,0x0707);
		GLCD_WriteReg(0x37,0x0305);
		GLCD_WriteReg(0x38,0x0208);
		GLCD_WriteReg(0x39,0x0F0B);
		delay_nms(15);
		GLCD_WriteReg(0x41,0x0002);
		GLCD_WriteReg(0x60,0x2700);
		GLCD_WriteReg(0x61,0x0001);
		GLCD_WriteReg(0x90,0x0119);
		GLCD_WriteReg(0x92,0x010A);
		GLCD_WriteReg(0x93,0x0004);
		GLCD_WriteReg(0xA0,0x0100);
		delay_nms(15);
		delay_nms(15);
		GLCD_WriteReg(0x07,0x0133);
		delay_nms(15);
		GLCD_WriteReg(0xA0,0x0000);
		delay_nms(20);
  	} 
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GLCD_Clear(BLUE);
	GLCD_SetMode(4);							 
}
/**************************************************************************************************************
 * 函数名：LCD_SetMode()
 * 输入  ：uint8_t mode 设置屏幕刷屏模式
 * 输出  ：void
 * 描述  ：设置LCD刷屏模式
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetMode(uint8_t mode)
{
	switch(mode)//常用4(横屏)和7(竖屏)
	{
		case 1:GLCD_WriteReg(0x03,0x1000);break;//向左向上:←↖
		case 2:GLCD_WriteReg(0x03,0x1008);break;//向上向左:↑↖
		case 3:GLCD_WriteReg(0x03,0x1010);break;//向右向上:→↗
		case 4:GLCD_WriteReg(0x03,0x1018);break;//向上向右:↑↗
		case 5:GLCD_WriteReg(0x03,0x1020);break;//向左向下:←↙
		case 6:GLCD_WriteReg(0x03,0x1028);break;//向下向左:↓↙
		case 7:GLCD_WriteReg(0x03,0x1030);break;//向右向下:→↘
		case 8:GLCD_WriteReg(0x03,0x1038);break;//向下向右:↓↘
	}
}
/**************************************************************************************************************
 * 函数名：LCD_Clear()
 * 输入  ：void
 * 输出  ：void
 * 描述  ：LCD清屏函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_Clear(uint16_t Color)
{
  uint32_t index = 0;
  
  GLCD_SetCursor(0,319); 
  GLCD_WriteRAM_Start(); /*开始写GRAM */
  for(index = 0; index < 76800; index++)
  {
    LCD_RAM = Color;
  }  
}

/**************************************************************************************************************
 * 函数名：GLCD_SetCursor()
 * 输入  ：uint16_t Xpos, uint16_t Ypos 设定的屏幕的X值和Y值
 * 输出  ：void
 * 描述  ：LCD设置光标位置函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
  GLCD_WriteReg(0x20, Ypos);
  GLCD_WriteReg(0x21, 319-Xpos);
}
/**************************************************************************************************************
 * 函数名：LCD_SetWindow()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width 区域的起点，宽和高
 * 输出  ：void
 * 描述  ：设置某个特定的填充区域
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  /*设置水平方向X开始坐标*/
  if(Xpos >= Height)
  {
    GLCD_WriteReg(0x50, (Xpos - Height + 1));
  }
  else
  {
    GLCD_WriteReg(0x50, 0);
  }
  /*设置水平方向X结束坐标*/
  GLCD_WriteReg(0x51, Xpos);
  /*设置竖直方向Y开始坐标*/
  if(Ypos >= Width)
  {
    GLCD_WriteReg(0x52, (Ypos - Width + 1));
  }  
  else
  {
    GLCD_WriteReg(0x52, 0);
  }
  /*设置竖直方向Y结束坐标*/
  GLCD_WriteReg(0x53, Ypos);
  GLCD_SetCursor(Xpos, Ypos);
}
/**************************************************************************************************************
 * 函数名：LCD_SetColors()
 * 输入  ：_TextColor 前景色,_BackColor 背景色
 * 输出  ：void
 * 描述  ：设置LCD的前景色和背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetColors(__IO uint16_t _TextColor, __IO uint16_t _BackColor)
{
  TextColor = _TextColor; 
  BackColor = _BackColor;
}
/**************************************************************************************************************
 * 函数名：LCD_GetColors()
 * 输入  ：*_TextColor 前景色的指针,*_BackColor 背景色的指针
 * 输出  ：void
 * 描述  ：获取LCD的前景色和背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_GetColors(__IO uint16_t *_TextColor, __IO uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}
/**************************************************************************************************************
 * 函数名：LCD_SetTextColor()
 * 输入  ：uint16_t Color 前景色
 * 输出  ：void
 * 描述  ：设置LCD的前景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetTextColor(__IO uint16_t Color)
{
  TextColor = Color;
}


/**************************************************************************************************************
 * 函数名：LCD_SetBackColor()
 * 输入  ：uint16_t Color 背景色
 * 输出  ：void
 * 描述  ：设置LCD的背景色
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_SetBackColor(__IO uint16_t Color)
{
  BackColor = Color;
}


/**************************************************************************************************************
 * 函数名：GLCD_DrawHLine()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Length 起点X和Y坐标及长度
 * 输出  ：void
 * 描述  ：画水平线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
  GLCD_SetCursor(Xpos, Ypos);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    for(i = 0; i < Length; i++)
    {
      GLCD_WriteRAM(TextColor);
    }
}
/**************************************************************************************************************
 * 函数名：GLCD_DrawVLine()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Length 起点X和Y坐标及长度
 * 输出  ：void
 * 描述  ：画垂直线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
	uint32_t i = 0;
  GLCD_SetCursor(Xpos, Ypos);
    for(i = 0; i < Length; i++)
    {
      GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
      GLCD_WriteRAM(TextColor);
      Ypos++;
      GLCD_SetCursor(Xpos, Ypos);
    }
}
/**************************************************************************************************************
 * 函数名：LCD_DrawRect()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height 矩形左上角点的坐标及宽和高
 * 输出  ：void
 * 描述  ：画矩形函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint8_t Height)
{
  GLCD_DrawHLine(Xpos, Ypos, Width);
  GLCD_DrawHLine(Xpos, Ypos+ Height, Width); 
  GLCD_DrawVLine(Xpos, Ypos, Height);
  GLCD_DrawVLine(Xpos+ Width,Ypos, Height);
}
/**************************************************************************************************************
 * 函数名：LCD_DrawCircle()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Radius 圆心坐标点及半径
 * 输出  ：void
 * 描述  ：画圆函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;/* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    GLCD_SetCursor(Xpos + CurX, Ypos + CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurX, Ypos - CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurX, Ypos + CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurX, Ypos - CurY);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurY, Ypos + CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos + CurY, Ypos - CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurY, Ypos + CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    GLCD_SetCursor(Xpos - CurY, Ypos - CurX);
    GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
    GLCD_WriteRAM(TextColor);
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}
/**************************************************************************************************************
 * 函数名：LCD_DrawMonoPict()
 * 输入  ：const uint32_t *Pict 画一个全屏单色的取膜数据
 * 输出  ：void
 * 描述  ：画一个单色的全屏图片函数
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawMonoPict(const uint32_t *Pict)
{
  uint32_t index = 0, i = 0;
  GLCD_SetCursor(0, (LCD_PIXEL_WIDTH - 1)); 
  GLCD_WriteRAM_Start(); /* Prepare to write GRAM */
  for(index = 0; index < 2400; index++)
  {
    for(i = 0; i < 32; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00)
      {
        GLCD_WriteRAM(BackColor);
      }
      else
      {
        GLCD_WriteRAM(TextColor);
      }
    }
  }
}
/**************************************************************************************************************
 * 函数名：LCD_FillRect()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height 填充矩形左上角点、宽和高
 * 输出  ：void
 * 描述  ：画一个填充的矩形
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{ 
	uint16_t tempcolor;
  GLCD_SetTextColor(TextColor);
  GLCD_DrawHLine(Xpos, Ypos, Width);
  GLCD_DrawHLine(Xpos, Ypos+ Height, Width);
  
  GLCD_DrawVLine(Xpos, Ypos, Height);
  GLCD_DrawVLine(Xpos+Width, Ypos, Height);

  Width --;
  Height-=2;
  Xpos++;
  tempcolor=TextColor;
  GLCD_SetTextColor(BackColor);

  while(Height--)
  {
    GLCD_DrawHLine(Xpos, ++Ypos, Width);    
  }

  GLCD_SetTextColor(tempcolor);
}
/**************************************************************************************************************
 * 函数名：LCD_FillCircle()
 * 输入  ：uint16_t Xpos, uint16_t Ypos, uint16_t Radius 填充圆的圆心和半径
 * 输出  ：void
 * 描述  ：画一个填充圆
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;    /* Decision Variable */ 
  uint32_t  CurX;/* Current X Value */
  uint32_t  CurY;/* Current Y Value */ 
  uint16_t tempcolor;
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  tempcolor=TextColor;
  GLCD_SetTextColor(BackColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      GLCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY);
      GLCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      GLCD_DrawHLine(Xpos - CurX, Ypos -CurY, 2*CurX);
      GLCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  GLCD_SetTextColor(tempcolor);
  GLCD_DrawCircle(Xpos, Ypos, Radius);
}
/**************************************************************************************************************
 * 函数名：LCD_DrawUniLine()
 * 输入  ：uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 起始点坐标和终点坐标
 * 输出  ：void
 * 描述  ：画任意方向的直线
 * 调用  ：外部调用        
 *****************************************************************************************************************/
void GLCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    GDrawPixel(x, y);             /* Draw the current pixel */
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}
/**************************************************************************************************************
 * 函数名：DrawPixel()
 * 输入  ：int16_t x, int16_t y  点的坐标
 * 输出  ：void
 * 描述  ：画一个象素点
 * 调用  ：外部调用        
 *****************************************************************************************************************/
static void GDrawPixel(uint16_t x, uint16_t y)
{ 
  if(x < 0 || x > LCD_XMAX || y < 0 || y > LCD_YMAX)
  {
    return;  
  }
  GLCD_DrawHLine(x, y, 1);
}


void GLCD_Char(u16 Xpos, u16 Ypos, u8 Ascii, u16 color)
{
	const u16 *c;
  	u16 Xaddr=0; 
  	u32 index=0,i=0;
					 
  	Xaddr=Xpos;
	c=&Efont->table[(Ascii-32)*Efont->Height]; 
  	GLCD_SetCursor(Xaddr, Ypos);  
  	for(index=0;index<Efont->Height;index++)
  	{
    	LCD_REG=0x22;//WriteRAM_Prepare
    	for(i=0;i<Efont->Width;i++)
    	{  
			if((((c[index]&((0x80<<((Efont->Width/12)*8))>>i))==0x00)&&(Efont->Width<=12))
			||(((c[index]&(0x1<<i))==0x00)&&(Efont->Width>12)))GLCD_WriteRAM(BLUE);
      		else GLCD_WriteRAM(color); 	  
    	}
    	Xaddr++;
    	GLCD_SetCursor(Xaddr, Ypos);
  	}
}


void GLCD_String(u16 xpos, u16 ypos, u8 *ptr, u16 color)
{
  	u16 refypos=LCD_XMAX-xpos;

  	while((*ptr!=0)&(((refypos+1)&0xFFFF)>=Efont->Width))
  	{
    	GLCD_Char(ypos,refypos,*ptr,color);
    	refypos-=Efont->Width;
    	ptr++;
  	}
}
