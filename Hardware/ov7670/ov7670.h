#ifndef __DCMI_H
#define __DCMI_H

#include "stm32f4xx_conf.h"
#include "include.h"

#define DCMI_DR_ADDRESS       	0x50050028   

#define SCCB_SIC_H()     GPIOB->BSRRL = GPIO_Pin_10
#define SCCB_SIC_L()     GPIOB->BSRRH = GPIO_Pin_10
#define SCCB_SID_H()     GPIOB->BSRRL = GPIO_Pin_11
#define SCCB_SID_L()     GPIOB->BSRRH = GPIO_Pin_11
#define SCCB_DATA_IN      SCCB_SID_IN()
#define SCCB_DATA_OUT     SCCB_SID_OUT()
#define SCCB_SID_STATE	 GPIOB->IDR&0x0800

#define OV7670_PWDN(x)  	(x?(GPIO_SetBits(GPIOA,GPIO_Pin_7)):(GPIO_ResetBits(GPIOA,GPIO_Pin_7)))			//POWER DOWN控制信号 
#define OV7670_RST(x)  	(x?(GPIO_SetBits(GPIOD,GPIO_Pin_7)):(GPIO_ResetBits(GPIOD,GPIO_Pin_7)))			//复位控制信号 

void DCMI_DMA_Init(u32 DMA_Memory0BaseAddr,u16 DMA_BufferSize,u32 DMA_MemoryDataSize,u32 DMA_MemoryInc);
void Cam_Init();
u8 OV7670_Init(void);
void OV7670_HW(u16 hstart,u16 vstart,u16 hstop,u16 vstop);
void SCCB_Init(void);
void SCCB_SID_OUT(void);
void SCCB_SID_IN(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void noAck(void);
u8 SCCB_Write(u8 m_data);
u8 SCCB_Read(void);
u8 OV_WriteReg(u8 regID, u8 regDat);
u8 OV_ReadReg(u8 regID, u8 *regDat);
void OV_Reset(void);
u8 OV_ReadID(void);

void DCMI_Start(void);
void DCMI_Stop(void);

extern u32 jpeg_buf[jpeg_buf_size];

#endif 

