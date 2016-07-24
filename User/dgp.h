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

void set_rgb_threshold(u8 R,u8 G,u8 B);
void set_line_threshold(u8 r,u8 g,u8 b);
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
void get_target2(u16 *jpeg,u8 *H,R_info *info);
void get_line(u16 *jpeg,u8 *H,R_info *info);

extern volatile u8 jpeg_data_ok;
extern volatile u32 jpeg_data_len;

extern u8 R_threshold;
extern u8 G_threshold;
extern u8 B_threshold;

#endif

