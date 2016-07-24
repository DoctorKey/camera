#ifndef _TEST_H_
#define _TEST_H_

#include "stm32f4xx.h"

void im_send(u8* im);
void matlab_test(u32* jpeg_buf,u8* im);
void R_test(u32* jpeg_buf,u8* im);
void G_test(u32* jpeg_buf,u8* im);
void B_test(u32* jpeg_buf,u8* im);
void H_test(u32* jpeg_buf,u8* im);
void H_test_op1(u32* jpeg_buf,u8* im);
void Y_test(u32* jpeg_buf,u8* im);
void D0_test(u32* jpeg_buf,u8* im);//不优化H的找红心算法
void D_test(u32* jpeg_buf,u8* im);//优化H的找红心算法
void D2_test(u32* jpeg_buf,u8* im);//自己加权算法
void D3_test(u32* jpeg_buf,u8* im);//孙训阈值算法
void line_test(u32* jpeg_buf,u8* im);//寻迹算法
void test_mode(u8 command);

extern char mode;

#endif

