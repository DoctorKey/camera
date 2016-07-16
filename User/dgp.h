#ifndef _DGP_H_
#define _DGP_H_
#include "stm32f4xx.h"

#define PI_3 1.0472
#define TWO_PI 6.2832
#define PI_3_40 41.888 //  pi/3*40

typedef struct{
	u8 x;
	u8 y;
	float ratio;
}R_info;

void jpeg_data_process(void);
void getR(u16 *jpeg,u8 *R);
void getG(u16 *jpeg,u8 *G);
void getB(u16 *jpeg,u8 *B);
void getY(u16 *jpeg,u8 *Y);//ªÒµ√¡¡∂»
void getH(u16 *jpeg,u8 *H);
void getH_D(u16 *jpeg,u8 *H,R_info *info);
void getH_op1(u16 *jpeg,u8 *H);
void getH_op1_getR(u16 *jpeg,u8 *H,R_info *info);
void get_target(u16 *jpeg,u8 *H,R_info *info);

extern volatile u8 jpeg_data_ok;
extern volatile u32 jpeg_data_len;

#endif

