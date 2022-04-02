#include "gait_task.h"

float step_t,forward_t,back_t,turn_left_t,turn_right_t,left_shift_t,right_shift_t;
u8 start_flag;

void step(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (step_t>=Ts)
			{
				step_t=0;
				break;
			}
			else
			{
				step_t=step_t+trot_speed;
				if(faai==0.5)
				{
					xf_1=0;   xs_1=0; 
					xf_2=0;   xs_2=0; 
					xf_3=0;   xs_3=0; 
					xf_4=0;   xs_4=0; 
					trot_XZ(step_t,0); 
				}
				else if(faai==0.25)
				{
					xf_1=0;   xs_1=0; 
					xf_2=0;   xs_2=0; 
					xf_3=0;   xs_3=0; 
					xf_4=0;   xs_4=0; 
					walk_XZ(step_t);
				}
			}
		}
	}
}

void forward(s16 a,float rol)
{
	while(a--)
	{
		while(1)
		{
			if (forward_t>=Ts)
			{
				forward_t=0;
				average();
				break;
			}
			else
			{
				forward_t=forward_t+trot_speed;
				if(faai==0.5)
				{
					xf_1=10;   xs_1=-30; 
					xf_2=10;   xs_2=-30; 
					xf_3=0;   xs_3=-40; 
					xf_4=0;   xs_4=-40;
//					yf_1=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_1=0; 
//					yf_2=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_2=0; 
//					yf_3=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_3=0; 
//					yf_4=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_4=0;
					
					
					yf_1=0;    ys_1=0; 
					yf_2=0;    ys_2=0; 
					yf_3=0;   ys_3=0; 
					yf_4=0;   ys_4=0;
					trot_XZ(forward_t,rol);  
				}
				else if(faai==0.25)
				{
					xf_1=0;   xs_1=-60; 
					xf_2=0;   xs_2=-60; 
					xf_3=-10;   xs_3=-80; 
					xf_4=-10;   xs_4=-80;	
					walk_XZ(forward_t);
				}
			}
		}
//		printf("a:%d\n",a);
	}
}



void back(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (back_t>=Ts)
			{
				back_t=0;
				break;
			}
			else
			{
				back_t=back_t+trot_speed;
				if(faai==0.5)
				{
					xs_1=10;   xf_1=-30; 
					xs_2=10;   xf_2=-30; 
					xs_3=0;   xf_3=-40; 
					xs_4=0;   xf_4=-40; 
					yf_1=0;    ys_1=0; 
					yf_2=0;    ys_2=0; 
					yf_3=0;   ys_3=0; 
					yf_4=0;   ys_4=0;
					trot_XZ(back_t,0);
				}
				else if(faai==0.25)
				{
					xf_1=-40;   xs_1=0; 
					xf_2=-40;   xs_2=0; 
					xf_3=-40;   xs_3=0; 
					xf_4=-40;   xs_4=0;  	
					walk_XZ(back_t);
				}
			}
		}
	}
}

void turn_left(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (turn_left_t>=Ts)
			{
				turn_left_t=0;
				break;
			}
			else
			{
				turn_left_t=turn_left_t+turn_speed;
				if(faai==0.5)
				{
					yf_1=10;   ys_1=-10;   
					yf_2=10;   ys_2=-10;
					yf_3=-10;   ys_3=10;
					yf_4=-10;   ys_4=10;
					trot_YZ(turn_left_t);
				}
				else if(faai==0.25)
				{
					yf_1=l3+15;   ys_1=l3-15;   
					yf_2=l3+15;   ys_2=l3-15;
					yf_3=l3-15;   ys_3=l3+15;
					yf_4=l3-15;   ys_4=l3+15;	
					walk_YZ(turn_left_t);
				}
			}
		}
	}
}

void turn_right(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (turn_right_t>=Ts)
			{
				turn_right_t=0;
				break;
			}
			else
			{
				turn_right_t=turn_right_t+turn_speed;
				if(faai==0.5)
				{
					yf_1=-10;   ys_1=10;   
					yf_2=-10;   ys_2=10;
					yf_3=10;   ys_3=-10;
					yf_4=10;   ys_4=-10;
					trot_YZ(turn_right_t);
				}
				else if(faai==0.25)
				{
					yf_1=l3-15;   ys_1=l3+15;   
					yf_2=l3-15;   ys_2=l3+15;
					yf_3=l3+15;   ys_3=l3-15;
					yf_4=l3+15;   ys_4=l3-15;	
					walk_YZ(turn_right_t);
				}
			}
		}
	}
}
	
void left_shift(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (left_shift_t>=Ts)
			{
				left_shift_t=0;
				break;
			}
			else
			{
				left_shift_t=left_shift_t+turn_speed;
				if(faai==0.5)
				{
					yf_1=10;   ys_1=-10;    
					yf_2=10;   ys_2=-10; 
					yf_3=10;   ys_3=-10; 	
					yf_4=10;   ys_4=-10; 
					trot_YZ(left_shift_t);
				}
				else if(faai==0.25)
				{
					yf_1=l3+10;   ys_1=l3-10;    
					yf_2=l3+10;   ys_2=l3-10; 
					yf_3=l3+10;   ys_3=l3-10; 	
					yf_4=l3+10;   ys_4=l3-10; 	
					walk_YZ(left_shift_t);
				}
			}
		}
	}
}

void right_shift(s16 a)
{
	while(a--)
	{
		while(1)
		{
			if (right_shift_t>=Ts)
			{
				right_shift_t=0;
				break;
			}
			else
			{
				right_shift_t=right_shift_t+turn_speed;
				if(faai==0.5)
				{
					yf_1=-10;   ys_1=10;   
					yf_2=-10;   ys_2=10;
					yf_3=-10;   ys_3=10;
					yf_4=-10;   ys_4=10;
					trot_YZ(right_shift_t);  
				}
				else if(faai==0.25)
				{
					yf_1=l3-10;   ys_1=l3+10;   
					yf_2=l3-10;   ys_2=l3+10;
					yf_3=l3-10;   ys_3=l3+10;
					yf_4=l3-10;   ys_4=l3+10; 	
					walk_YZ(right_shift_t);
				}
			}
		}
	}
}

void dog_start(void)
{
	
	stand();
//	Delay_ms(1000);
//	head_servo_task();

	
	start_flag=1;
}

void shang_po(s16 a,float rol)
{
	while(a--)
	{
		while(1)
		{
			if (forward_t>=Ts)
			{
				forward_t=0;
				average();
				break;
			}
			else
			{
				forward_t=forward_t+trot_speed;
					xf_1=40;   xs_1=0; 
					xf_2=40;   xs_2=0; 
					xf_3=-30;   xs_3=-70; 
					xf_4=-30;   xs_4=-70;
					yf_1=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_1=0; 
					yf_2=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_2=0; 
					yf_3=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_3=0; 
					yf_4=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_4=0;
//					yf_1=0.3*avg_angle-0.2*avg_deviation;    ys_1=0; 
//					yf_2=0.3*avg_angle-0.2*avg_deviation;    ys_2=0; 
//					yf_3=-0.3*avg_angle-0.2*avg_deviation;   ys_3=0; 
//					yf_4=-0.3*avg_angle-0.2*avg_deviation;   ys_4=0;
					trot_XZ(forward_t,rol); 
			}
		}
	}
}

void po_1(s16 a,float rol)
{
	while(a--)
	{
		while(1)
		{
			if (forward_t>=Ts)
			{
				forward_t=0;
				average();
				break;
			}
			else
			{
				forward_t=forward_t+trot_speed;
					xf_1=30;   xs_1=-10; 
					xf_2=30;   xs_2=-10; 
					xf_3=-30;   xs_3=-70; 
					xf_4=-30;   xs_4=-70;
					yf_1=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_1=0; 
					yf_2=0.3*opmv.lt.angle-0.2*opmv.lt.deviation;    ys_2=0; 
					yf_3=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_3=0; 
					yf_4=-0.3*opmv.lt.angle-0.2*opmv.lt.deviation;   ys_4=0;
//					yf_1=0.3*avg_angle-0.2*avg_deviation;    ys_1=0; 
//					yf_2=0.3*avg_angle-0.2*avg_deviation;    ys_2=0; 
//					yf_3=-0.3*avg_angle-0.2*avg_deviation;   ys_3=0; 
//					yf_4=-0.3*avg_angle-0.2*avg_deviation;   ys_4=0;
					trot_XZ(forward_t,rol); 
			}
		}
	}
}


void po_2(s16 a,float rol)
{
	while(a--)
	{
		while(1)
		{
			if (forward_t>=Ts)
			{
				forward_t=0;
				average();
				break;
			}
			else
			{
				forward_t=forward_t+trot_speed;
					xf_1=20;   xs_1=-20; 
					xf_2=20;   xs_2=-20; 
					xf_3=-30;   xs_3=-70; 
					xf_4=-30;   xs_4=-70;
					yf_1=0.4*opmv.lt.angle-0.1*opmv.lt.deviation;    ys_1=0; 
					yf_2=0.4*opmv.lt.angle-0.1*opmv.lt.deviation;    ys_2=0; 
					yf_3=-0.4*opmv.lt.angle-0.1*opmv.lt.deviation;   ys_3=0; 
					yf_4=-0.4*opmv.lt.angle-0.1*opmv.lt.deviation;   ys_4=0;
//					yf_1=0.3*avg_angle-0.2*avg_deviation;    ys_1=0; 
//					yf_2=0.3*avg_angle-0.2*avg_deviation;    ys_2=0; 
//					yf_3=-0.3*avg_angle-0.2*avg_deviation;   ys_3=0; 
//					yf_4=-0.3*avg_angle-0.2*avg_deviation;   ys_4=0;
					trot_XZ(forward_t,rol); 
			}
		}
	}
}

void po_3(s16 a,float rol)
{
	while(a--)
	{
		while(1)
		{
			if (forward_t>=Ts)
			{
				forward_t=0;
				average();
				break;
			}
			else
			{
				forward_t=forward_t+trot_speed;
					xf_1=25;   xs_1=-15; 
					xf_2=25;   xs_2=-15; 
					xf_3=-35;   xs_3=-75; 
					xf_4=-35;   xs_4=-75;
					yf_1=0.4*opmv.lt.angle-0.1*opmv.lt.deviation;    ys_1=0; 
					yf_2=0.4*opmv.lt.angle-0.1*opmv.lt.deviation;    ys_2=0; 
					yf_3=-0.4*opmv.lt.angle-0.1*opmv.lt.deviation;   ys_3=0; 
					yf_4=-0.4*opmv.lt.angle-0.1*opmv.lt.deviation;   ys_4=0;
//					yf_1=0.3*avg_angle-0.2*avg_deviation;    ys_1=0; 
//					yf_2=0.3*avg_angle-0.2*avg_deviation;    ys_2=0; 
//					yf_3=-0.3*avg_angle-0.2*avg_deviation;   ys_3=0; 
//					yf_4=-0.3*avg_angle-0.2*avg_deviation;   ys_4=0;
					trot_XZ(forward_t,rol); 
			}
		}
	}
}
