#ifndef _DGP_H_
#define _DGP_H_

#include "stm32f4xx.h"


void matlab_test(u32* jpeg_buf,u8* im);
void R_test(u32* jpeg_buf,u8* im);
void G_test(u32* jpeg_buf,u8* im);
void B_test(u32* jpeg_buf,u8* im);
void H_test(u32* jpeg_buf,u8* im);
void Y_test(u32* jpeg_buf,u8* im);
void test_mode(char command);

extern char mode;

#endif

