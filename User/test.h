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
void D0_test(u32* jpeg_buf,u8* im);//���Ż�H���Һ����㷨
void D_test(u32* jpeg_buf,u8* im);//�Ż�H���Һ����㷨
void D2_test(u32* jpeg_buf,u8* im);//�Լ���Ȩ�㷨
void D3_test(u32* jpeg_buf,u8* im);//��ѵ��ֵ�㷨
void line_test(u32* jpeg_buf,u8* im);//Ѱ���㷨
void test_mode(u8 command);

extern char mode;

#endif

