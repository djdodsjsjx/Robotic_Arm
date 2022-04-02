#include "opmv_linetracking.h"

float head_servo_output=0;
u8 CONFIRM_TIMES=2,confirm_cnt;

float avg_angle,avg_deviation;
	
void LTracking_Ctrl(void)
{
	if(opmv.lt.sta==1)
	{
		if((opmv.lt.angle>40)&&ABS((opmv.lt.deviation)<20))             //左顺转
		{
			turn_left(1);
		}
		if((opmv.lt.angle<-40)&&(ABS(opmv.lt.deviation)<20))            //右顺转
		{
			turn_right(1);
		}
		if(opmv.lt.deviation>40)         //右移
		{
			right_shift(1);
		}
		if(opmv.lt.deviation<-40)			 //左移
		{
			left_shift(1);
		}
		else                             //正常前进
		{
			forward(5,-10);
		}
	}
	else if(opmv.lt.sta==2)           //直角左转
	{
		turn_left(5);
	}
	else if(opmv.lt.sta==3)           //直角右转
	{
		turn_left(5);
	}
	else															//停止
	{
		stand();
	}
	
}



void error_confirm(void)
{
	if(confirm_cnt<CONFIRM_TIMES)
	{
		confirm_cnt++;
	}
	else
	{
		confirm_cnt=0;
	}
}

void head_servo_task(void)
{
	WritePos(13,init_head_servo+20,0,500);
	Delay_ms(1000);
	WritePos(13,init_head_servo-20,0,500);
	Delay_ms(1000);
	WritePos(13,init_head_servo,0,500);
	Delay_ms(2000);
	
}

void average(void)
{
	avg_angle=sum_angle/opmv_t;
	avg_deviation=sum_deviation/opmv_t;
	opmv_t=0;
	sum_angle=0;
	sum_deviation=0;
	
}

