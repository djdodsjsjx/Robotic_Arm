#include "mearm.h"
u8 MEARM_state=0;
float l1=108,l2=140,speed=100.0;
MEARM_XYZ mearm_xyz;
MEARM_Angle mearm_action_angle;
MEARM_Angle mearm_init_angle;

void mearm_control(void)
{
	mearm_init_angle.alfa=80;
	mearm_init_angle.beta=100;
	mearm_init_angle.gamma=88;
	mearm_init_angle.pliers=90;		
	if(MEARM_state==1)
	{
		position(2,mearm_init_angle.alfa);
		position(1,mearm_init_angle.beta);
		position(3,mearm_init_angle.gamma);
		position(0,mearm_init_angle.pliers);
	}
	else if(MEARM_state==0)
	{
		pliers_servo(0);
		trajectory(80,100,-10);
		pliers_servo(1);
		trajectory(80,100,50);
		trajectory(30,-100,100);
	}
}
void trajectory(float mearm_goal_x,float mearm_goal_y,float mearm_goal_z)
{
	float bia_x,bia_y,bia_z;
	bia_x=(mearm_goal_x-mearm_xyz.x)/speed;
	bia_y=(mearm_goal_y-mearm_xyz.y)/speed;
	bia_z=(mearm_goal_z-mearm_xyz.z)/speed;
	while(!((ABS(mearm_xyz.x-mearm_goal_x)<2)&&(ABS(mearm_xyz.y-mearm_goal_y)<2)&&(ABS(mearm_xyz.z-mearm_goal_z)<2)))
	{
		mearm_xyz.x+=bia_x;
		mearm_xyz.y+=bia_y;
		mearm_xyz.z+=bia_z;
		Inverse_Kinematics();
		mearm_servo_output();
	}
}
void Inverse_Kinematics(void)
{
	float l3;
	l3=sqrt(my_pow(mearm_xyz.x)+my_pow(mearm_xyz.y)+my_pow(mearm_xyz.z));
	if(mearm_xyz.z>0)
		mearm_action_angle.alfa=acos((my_pow(l1)+my_pow(l3)-my_pow(l2))/(2*l1*l3))-atan(sqrt(my_pow(mearm_xyz.x)+my_pow(mearm_xyz.y))/mearm_xyz.z);
	if(mearm_xyz.z==0)
		mearm_action_angle.alfa=acos((my_pow(l1)+my_pow(l3)-my_pow(l2))/(2*l1*l3))-MY_PI/2;
	if(mearm_xyz.z<0)
		mearm_action_angle.alfa=acos((my_pow(l1)+my_pow(l3)-my_pow(l2))/(2*l1*l3))-atan(sqrt(my_pow(mearm_xyz.x)+my_pow(mearm_xyz.y))/mearm_xyz.z)-MY_PI;
	mearm_action_angle.beta=atan(mearm_xyz.z/sqrt(my_pow(mearm_xyz.x)+my_pow(mearm_xyz.y)))-acos((my_pow(l2)+my_pow(l3)-my_pow(l1))/(2*l2*l3));
	mearm_action_angle.gamma=atan(mearm_xyz.y/mearm_xyz.x);
	mearm_action_angle.alfa=180*mearm_action_angle.alfa/MY_PI;
	mearm_action_angle.beta=180*mearm_action_angle.beta/MY_PI;
	mearm_action_angle.gamma=180*mearm_action_angle.gamma/MY_PI;
}

void mearm_servo_output(void)
{
	position(2,mearm_init_angle.alfa-mearm_action_angle.alfa);
	position(1,mearm_init_angle.beta+mearm_action_angle.beta);
	position(3,mearm_init_angle.gamma+mearm_action_angle.gamma);
	Delay_ms(10);
}

void pliers_servo(u8 a)
{
	if(a==1)
	{
		Delay_ms(1000);
		position(0,mearm_init_angle.gamma-60);    //钳子张开
		Delay_ms(1000);
	}
	else if(a==0)
	{
		Delay_ms(1000);
		position(0,mearm_init_angle.gamma+20);    //钳子闭合
		Delay_ms(1000);
	}
}

void position(u8 cmd,u16 value)
{
	value = (uint16_t)(500 + value * 100/9.0);
	switch(cmd)
	{
		case 0:TIM_SetCompare1(TIM2,value); break;
		case 1:TIM_SetCompare2(TIM2,value); break;
		case 2:TIM_SetCompare3(TIM2,value); break;
		case 3:TIM_SetCompare4(TIM2,value); break;
	}
}
