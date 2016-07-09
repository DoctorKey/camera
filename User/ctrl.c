#include "ctrl.h"
#include "pwm_out.h"
#include "include.h"

pid_group pid_camera;
void pid_set()
{
	pid_camera.p=1;
	pid_camera.i=1;
	pid_camera.d=1;
}

/*
		
*/
int16_t pwm[4]={200,400,800,1200};
int16_t CH[CH_NUM]={0,0,0,0};//1000~2000
void ctrl_pwm(int16_t CH[CH_NUM])
{
	int i;
	pwm[0]=200;
	pwm[1]=300;
	pwm[2]=400;
	pwm[3]=500;
	for(i=0;i<15;i++){
		pwm[0]=pwm[0]+100;
		pwm[1]=pwm[0]+100;
		pwm[2]=pwm[0]+100;
		pwm[3]=pwm[0]+100;
		SetPwm(pwm,PWM_MIN,PWM_MAX);
	}
	
}

//void Control_Land()
//{
//	
//	if(Get_Height() > 28)
//	{
//		Height_Target = Get_Height() - 5;
//		Control_Heigh(Height_Target);
//	}
//	if(Get_Height() <= 28)
//	{
//		Control_Heigh(23.0);
//		if(Get_Height() <= 16.0)
//		{
//			Motor_RateFlash(18000, 18000, 18000, 18000);
//			delay_s(1);
//			Motor_RateFlash(0, 0, 0, 0);
//		}
//	}
//}

//void Control_Free_Land()
//{
//	R_TAU0_Channel5_Stop();
//	MOTO_THRESHOLD = 0;
//	Motor_RateFlash(0, 0, 0, 0);
//	MOTO1 = 0; MOTO2 = 0; MOTO3 = 0; MOTO4 = 0;
//	TDR01 = 2000; TDR02 = 2000; TDR03 = 2000; TDR04 = 2000;
//}