#include "servo.h"
u16 frompos[4],topos[4]={90,90,90,90},outpos[4];
u16 pos_min[4]={25,35,45,20},pos_max[4]={100,120,160,160};

void pwm_servo_init(void)
{
	TIM2_PWM_Init(SERVO_TIM_ARR,SERVO_TIM_PSC);
}


void servo_demo(void)
{
	for(u8 topos=5;topos<175;topos++)
	{
		servo_output();
	}
	for(u8 topos=175;topos>5;topos--)
	{
		servo_output();
	}
}

void PS2_servo_control(void)
{
	PS2_ClearData();   //Çå³ý»º´æ
	PS2_ReadData();	   //¶ÁÊý¾Ý
	if(PS2_AnologData(PSS_LX)>200)
	{
		topos[0] = frompos[0]+3;
	}
	if(PS2_AnologData(PSS_LX)<50)
	{
		topos[0] = frompos[0]-3;
	}
	if(PS2_AnologData(PSS_LY)>200)
	{
		topos[1] = frompos[1]-3;
	}
	if(PS2_AnologData(PSS_LY)<50)
	{
		topos[1] = frompos[1]+3;
	}
	if(PS2_AnologData(PSS_RX)>200)
	{
		topos[2] = frompos[2]+3;
	}
	if(PS2_AnologData(PSS_RX)<50)
	{
		topos[2] = frompos[2]-3;
	}
	if(PS2_AnologData(PSS_RY)>200)
	{
		topos[3] = frompos[3]+3;
	}
	if(PS2_AnologData(PSS_RY)<50)
	{
		topos[3] = frompos[3]-3;
	}
	servo_output();
	Delay_ms(20);
}


void servo_output(void)
{
	u16 pulse[4];
	for(u8 i=0;i<4;i++)
	{
		outpos[i]=frompos[i];
		if(topos[i] <= pos_min[i])
			topos[i] = pos_min[i];
		if(topos[i] >= pos_max[i])
			topos[i] = pos_max[i]; 
		while(outpos[i]>topos[i])
		{
			outpos[i]-=1;
			pulse[i] = (uint16_t)(500 + outpos[i] * 100/9.0); 
			position(i,pulse[i]);
			Delay_ms(2);
		}
		while(outpos[i]<topos[i])
		{
			outpos[i]+=1;
			pulse[i] = (uint16_t)(500 + outpos[i] * 100/9.0); 
			position(i,pulse[i]);
			Delay_ms(2);
		}
		frompos[i]=topos[i];
	}
}



