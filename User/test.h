#ifndef _DGP_H_
#define _DGP_H_

#include "stm32f4xx.h"
#include "dgp.h"

typedef struct{
	u8 x;
	u8 y;
	float ratio;
}R_info;

void im_send(u8* im);
void matlab_test(u32* jpeg_buf,u8* im);
void R_test(u32* jpeg_buf,u8* im);
void G_test(u32* jpeg_buf,u8* im);
void B_test(u32* jpeg_buf,u8* im);
void H_test(u32* jpeg_buf,u8* im);
void H_test_op1(u32* jpeg_buf,u8* im);
void Y_test(u32* jpeg_buf,u8* im);
void D0_test(u32* jpeg_buf,u8* im);
void D_test(u32* jpeg_buf,u8* im);
void test_mode(u8 command);

extern R_info info;
extern char mode;

#endif

