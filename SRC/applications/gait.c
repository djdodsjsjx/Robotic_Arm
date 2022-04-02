#include "gait.h" 

float sigma,zep,xep_b,xep_z,xep_z1,xep_z2,xep_z3,yep_b,yep_z,yep_z1,yep_z2,yep_z3,
			xep_b_1,xep_b_2,xep_z_1,xep_z_2,xep_b_3,xep_b_4,xep_z_3,xep_z_4,
			yep_b_1,yep_b_2,yep_z_1,yep_z_2,yep_b_3,yep_b_4,yep_z_3,yep_z_4;
float x_S,y_S,z_S;


void walk_XZ(float t)
{	
	y=0;
	if (t<=Ts*faai)
	{
//		if(t==trot_speed)
//		{
//			Delay_ms(1000);
//		}
		POS_Adjust(-5,40,0,0);
//		if(ABS(PIT_S-40)<5)
//		{
			sigma=2*MY_PI*t/(faai*Ts);
			xep_b=(xf_1-xs_1)*((sigma-sin(sigma))/(2*MY_PI))+xs_1;
			xep_z1=((xs_4-xf_4)/3)*((sigma-sin(sigma))/(2*MY_PI))+xf_4;
			xep_z2=((xs_3-xf_3)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xf_3+xs_3)/3; 
			xep_z3=((xs_2-xf_2)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xs_2+xf_2)/3;
			zep=h*(1-cos(sigma))/2;

			contorl_1_leg(xep_b, y,z+zep);
			contorl_2_leg(xep_z3,y,z);
			contorl_3_leg(xep_z2,y,z);
			contorl_4_leg(xep_z1,y,z);
//		}
//		else
//		{
//			t=t-trot_speed;
//		}
	}

	if (t>Ts*faai && t<Ts/2)
	{
//		if((t-Ts*faai)<=trot_speed)
//		{
//			Delay_ms(1000);
//		}
		POS_Adjust(-5,-40,0,0);
//		if(ABS(PIT_S+40)<5)
//		{
			sigma=2*MY_PI*(t-Ts*faai)/(faai*Ts);
			xep_b=(xf_2-xs_2)*((sigma-sin(sigma))/(2*MY_PI))+xs_2;
			xep_z1=((xs_1-xf_1)/3)*((sigma-sin(sigma))/(2*MY_PI))+xf_1;
			xep_z2=((xs_4-xf_4)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xf_4+xs_4)/3; 
			xep_z3=((xs_3-xf_3)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xs_3+xf_3)/3;
			zep=h*(1-cos(sigma))/2;
		

			contorl_1_leg(xep_z1,y,z);
			contorl_2_leg(xep_b, y,z+zep);
			contorl_3_leg(xep_z3,y,z);
			contorl_4_leg(xep_z2,y,z);
//		}
//		else
//		{
//			t=t-trot_speed;
//		}
		

	}

	if (t>Ts/2 && t<Ts*3/4)
	{
//		if((t-Ts/2)<=trot_speed)
//		{
//			Delay_ms(1000);
//		}
		POS_Adjust(-5,-40,0,0);
//		if(ABS(PIT_S+20)<5)
//		{
			sigma=2*MY_PI*(t-Ts/2)/(faai*Ts);
			xep_b=(xf_3-xs_3)*((sigma-sin(sigma))/(2*MY_PI))+xs_3;
			xep_z1=((xs_2-xf_2)/3)*((sigma-sin(sigma))/(2*MY_PI))+xf_2;
			xep_z2=((xs_1-xf_1)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xf_1+xs_1)/3; 
			xep_z3=((xs_4-xf_4)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xs_4+xf_4)/3;
			zep=h*(1-cos(sigma))/2;
		
			contorl_1_leg(xep_z2,y,z);
			contorl_2_leg(xep_z1,y,z);
			contorl_3_leg(xep_b, y,z+zep);
			contorl_4_leg(xep_z3,y,z);
//	  }
//		else
//		{
//			t=t-trot_speed;
//		}
    
	}

	if (t>Ts*3/4 && t<Ts)
	{
//		if((t-Ts*3/4)<=trot_speed)
//		{
//			Delay_ms(1000);
//		}
		POS_Adjust(-5,40,0,0);
//		if(ABS(PIT_S-40)<2)
//		{
			sigma=2*MY_PI*(t-Ts*3/4)/(faai*Ts);
			xep_b=(xf_4-xs_4)*((sigma-sin(sigma))/(2*MY_PI))+xs_4;
			xep_z1=((xs_3-xf_3)/3)*((sigma-sin(sigma))/(2*MY_PI))+xf_3;
			xep_z2=((xs_2-xf_2)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xf_2+xs_2)/3; 
			xep_z3=((xs_1-xf_1)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*xs_1+xf_1)/3;
			zep=h*(1-cos(sigma))/2;
			
			contorl_1_leg(xep_z3,y,z);
			contorl_2_leg(xep_z2,y,z);
			contorl_3_leg(xep_z1,y,z);
			contorl_4_leg(xep_b, y,z+zep);
//		}
//		else
//		{
//			t=t-trot_speed;
//		}
	}
	
	//========   步态融合+逆解   ========
		Get_Position();
		
		//=========   舵机输出   ==========
		dog_control();
 
}




//void trot_XZ(float t,float rol)
//{
//y=0;
//POS_Adjust(rol,0,0,0);
//if (t<=Ts*faai)
//{
////		if(ABS(t)==trot_speed)
////		{
////			Delay_ms(400);
////		}
//	sigma=2*3.14*t/(faai*Ts);
//	zep=h*(1-cos(sigma))/2;
//	xep_b_1=(xf_1-xs_1)*((sigma-sin(sigma))/(2*MY_PI))+xs_1;
//	xep_z_1=(xs_1-xf_1)*((sigma-sin(sigma))/(2*MY_PI))+xf_1;
//	xep_b_2=(xf_2-xs_2)*((sigma-sin(sigma))/(2*MY_PI))+xs_2;
//	xep_z_2=(xs_2-xf_2)*((sigma-sin(sigma))/(2*MY_PI))+xf_2;
//	xep_b_3=(xf_3-xs_3)*((sigma-sin(sigma))/(2*MY_PI))+xs_3;
//	xep_z_3=(xs_3-xf_3)*((sigma-sin(sigma))/(2*MY_PI))+xf_3;
//	xep_b_4=(xf_4-xs_4)*((sigma-sin(sigma))/(2*MY_PI))+xs_4;
//	xep_z_4=(xs_4-xf_4)*((sigma-sin(sigma))/(2*MY_PI))+xf_4;

//	contorl_1_leg(xep_b_1,y,z+zep);
//	contorl_2_leg(xep_z_2,y,z);
//	contorl_3_leg(xep_b_3,y+5,z+zep);
//	contorl_4_leg(xep_z_4,y,z);

//	
//}
//if (t>Ts*faai && t<Ts)
//{
////		if(ABS(t-Ts*faai)<=trot_speed)
////		{
////			Delay_ms(400);
////		}
//	sigma=2*MY_PI*(t-Ts*faai)/(faai*Ts);
//	zep=h*(1-cos(sigma))/2;
//	
//	xep_b_1=(xf_1-xs_1)*((sigma-sin(sigma))/(2*MY_PI))+xs_1;
//	xep_z_1=(xs_1-xf_1)*((sigma-sin(sigma))/(2*MY_PI))+xf_1;
//	xep_b_2=(xf_2-xs_2)*((sigma-sin(sigma))/(2*MY_PI))+xs_2;
//	xep_z_2=(xs_2-xf_2)*((sigma-sin(sigma))/(2*MY_PI))+xf_2;
//	xep_b_3=(xf_3-xs_3)*((sigma-sin(sigma))/(2*MY_PI))+xs_3;
//	xep_z_3=(xs_3-xf_3)*((sigma-sin(sigma))/(2*MY_PI))+xf_3;
//	xep_b_4=(xf_4-xs_4)*((sigma-sin(sigma))/(2*MY_PI))+xs_4;
//	xep_z_4=(xs_4-xf_4)*((sigma-sin(sigma))/(2*MY_PI))+xf_4;
//	
//	contorl_1_leg(xep_z_1,y,z);
//	contorl_2_leg(xep_b_2,y,z+zep);
//	contorl_3_leg(xep_z_3,y+5,z);
//	contorl_4_leg(xep_b_4,y,z+zep);


//}

////========   步态融合+逆解   ========
//	Get_Position();
//	
//	//=========   舵机输出   ==========
//	dog_control();
//}



void trot_XZ(float t,float rol)
{
	y=0;
	POS_Adjust(rol,0,0,0);
	if (t<=Ts*faai)
	{
//		if(ABS(t)==trot_speed)
//		{
//			Delay_ms(350);
//		}
		sigma=2*3.14*t/(faai*Ts);
		zep=h*(1-cos(sigma))/2;
		xep_b_1=(xf_1-xs_1)*((sigma-sin(sigma))/(2*MY_PI))+xs_1;
		xep_z_1=(xs_1-xf_1)*((sigma-sin(sigma))/(2*MY_PI))+xf_1;
		xep_b_2=(xf_2-xs_2)*((sigma-sin(sigma))/(2*MY_PI))+xs_2;
		xep_z_2=(xs_2-xf_2)*((sigma-sin(sigma))/(2*MY_PI))+xf_2;
		xep_b_3=(xf_3-xs_3)*((sigma-sin(sigma))/(2*MY_PI))+xs_3;
		xep_z_3=(xs_3-xf_3)*((sigma-sin(sigma))/(2*MY_PI))+xf_3;
		xep_b_4=(xf_4-xs_4)*((sigma-sin(sigma))/(2*MY_PI))+xs_4;
		xep_z_4=(xs_4-xf_4)*((sigma-sin(sigma))/(2*MY_PI))+xf_4;
		
		yep_b_1=(yf_1-ys_1)*((sigma-sin(sigma))/(2*MY_PI))+ys_1;
		yep_z_1=(ys_1-yf_1)*((sigma-sin(sigma))/(2*MY_PI))+yf_1;
		yep_b_2=(yf_2-ys_2)*((sigma-sin(sigma))/(2*MY_PI))+ys_2;
		yep_z_2=(ys_2-yf_2)*((sigma-sin(sigma))/(2*MY_PI))+yf_2;
		yep_b_3=(yf_3-ys_3)*((sigma-sin(sigma))/(2*MY_PI))+ys_3;
		yep_z_3=(ys_3-yf_3)*((sigma-sin(sigma))/(2*MY_PI))+yf_3;
		yep_b_4=(yf_4-ys_4)*((sigma-sin(sigma))/(2*MY_PI))+ys_4;
		yep_z_4=(ys_4-yf_4)*((sigma-sin(sigma))/(2*MY_PI))+yf_4;

		contorl_1_leg(xep_b_1,yep_b_1,z+zep);
		contorl_2_leg(xep_z_2,yep_z_2,z);
		contorl_3_leg(xep_b_3,yep_b_3,z+zep);
		contorl_4_leg(xep_z_4,yep_z_4,z);

		
	}
	if (t>Ts*faai && t<Ts)
	{
//		if(ABS(t-Ts*faai)<=trot_speed)
//		{
//			Delay_ms(350);
//		}
		sigma=2*MY_PI*(t-Ts*faai)/(faai*Ts);
		zep=h*(1-cos(sigma))/2;
		
		xep_b_1=(xf_1-xs_1)*((sigma-sin(sigma))/(2*MY_PI))+xs_1;
		xep_z_1=(xs_1-xf_1)*((sigma-sin(sigma))/(2*MY_PI))+xf_1;
		xep_b_2=(xf_2-xs_2)*((sigma-sin(sigma))/(2*MY_PI))+xs_2;
		xep_z_2=(xs_2-xf_2)*((sigma-sin(sigma))/(2*MY_PI))+xf_2;
		xep_b_3=(xf_3-xs_3)*((sigma-sin(sigma))/(2*MY_PI))+xs_3;
		xep_z_3=(xs_3-xf_3)*((sigma-sin(sigma))/(2*MY_PI))+xf_3;
		xep_b_4=(xf_4-xs_4)*((sigma-sin(sigma))/(2*MY_PI))+xs_4;
		xep_z_4=(xs_4-xf_4)*((sigma-sin(sigma))/(2*MY_PI))+xf_4;
		
		yep_b_1=(yf_1-ys_1)*((sigma-sin(sigma))/(2*MY_PI))+ys_1;
		yep_z_1=(ys_1-yf_1)*((sigma-sin(sigma))/(2*MY_PI))+yf_1;
		yep_b_2=(yf_2-ys_2)*((sigma-sin(sigma))/(2*MY_PI))+ys_2;
		yep_z_2=(ys_2-yf_2)*((sigma-sin(sigma))/(2*MY_PI))+yf_2;
		yep_b_3=(yf_3-ys_3)*((sigma-sin(sigma))/(2*MY_PI))+ys_3;
		yep_z_3=(ys_3-yf_3)*((sigma-sin(sigma))/(2*MY_PI))+yf_3;
		yep_b_4=(yf_4-ys_4)*((sigma-sin(sigma))/(2*MY_PI))+ys_4;
		yep_z_4=(ys_4-yf_4)*((sigma-sin(sigma))/(2*MY_PI))+yf_4;
		
		contorl_1_leg(xep_z_1,yep_z_1,z);
		contorl_2_leg(xep_b_2,yep_b_2,z+zep);
		contorl_3_leg(xep_z_3,yep_z_3,z);
		contorl_4_leg(xep_b_4,yep_b_4,z+zep);

	
	}
	
	//========   步态融合+逆解   ========
		Get_Position();
		
		//=========   舵机输出   ==========
		dog_control();
}


void walk_YZ(float t)
{	
	x=0;
	if (t<=Ts*faai)
	{		
		sigma=2*MY_PI*t/(faai*Ts);
		yep_b=(yf-ys)*((sigma-sin(sigma))/(2*MY_PI))+ys;
		yep_z1=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+yf;
		yep_z2=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*yf+ys)/3; 
		yep_z3=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*ys+yf)/3;
		zep=h*(1-cos(sigma))/2;
	
		trot_leg_XYZ.z[0]=z+zep;
		trot_leg_XYZ.z[1]=z;
		trot_leg_XYZ.z[2]=z;
		trot_leg_XYZ.z[3]=z;
		
		trot_leg_XYZ.y[0]=yep_b;
		trot_leg_XYZ.y[1]=yep_z2;
		trot_leg_XYZ.y[2]=yep_z3;
		trot_leg_XYZ.y[3]=yep_z1;
		
		trot_leg_XYZ.x[0]=x;
		trot_leg_XYZ.x[1]=x;
		trot_leg_XYZ.x[2]=x;
		trot_leg_XYZ.x[3]=x;
	}

	if (t>Ts*faai && t<Ts/2)
	{
		sigma=2*MY_PI*(t-Ts*faai)/(faai*Ts);
		yep_b=(yf-ys)*((sigma-sin(sigma))/(2*MY_PI))+ys;
		yep_z1=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+yf;
		yep_z2=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*yf+ys)/3; 
		yep_z3=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*ys+yf)/3;
		zep=h*(1-cos(sigma))/2;
	

		trot_leg_XYZ.z[0]=z;
		trot_leg_XYZ.z[1]=z;
		trot_leg_XYZ.z[2]=z+zep;
		trot_leg_XYZ.z[3]=z;
		
		trot_leg_XYZ.y[0]=yep_z1;
		trot_leg_XYZ.y[1]=yep_z3;
		trot_leg_XYZ.y[2]=yep_b;
		trot_leg_XYZ.y[3]=yep_z2;
		
		trot_leg_XYZ.x[0]=x;
		trot_leg_XYZ.x[1]=x;
		trot_leg_XYZ.x[2]=x;
		trot_leg_XYZ.x[3]=x;
	}

	if (t>Ts/2 && t<Ts*3/4)
	{
		sigma=2*MY_PI*(t-Ts/2)/(faai*Ts);
		yep_b=(yf-ys)*((sigma-sin(sigma))/(2*MY_PI))+ys;
		yep_z1=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+yf;
		yep_z2=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*yf+ys)/3; 
		yep_z3=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*ys+yf)/3;
		zep=h*(1-cos(sigma))/2;
	
		trot_leg_XYZ.z[0]=z;
		trot_leg_XYZ.z[1]=z+zep;
		trot_leg_XYZ.z[2]=z;
		trot_leg_XYZ.z[3]=z;
		
		trot_leg_XYZ.y[0]=yep_z2;
		trot_leg_XYZ.y[1]=yep_b;
		trot_leg_XYZ.y[2]=yep_z1;
		trot_leg_XYZ.y[3]=yep_z3;
		
		trot_leg_XYZ.x[0]=x;
		trot_leg_XYZ.x[1]=x;
		trot_leg_XYZ.x[2]=x;
		trot_leg_XYZ.x[3]=x;
		
		

	}

	if (t>Ts*3/4 && t<Ts)
	{
		sigma=2*MY_PI*(t-Ts*3/4)/(faai*Ts);
		yep_b=(yf-ys)*((sigma-sin(sigma))/(2*MY_PI))+ys;
		yep_z1=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+yf;
		yep_z2=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*yf+ys)/3; 
		yep_z3=((ys-yf)/3)*((sigma-sin(sigma))/(2*MY_PI))+(2*ys+yf)/3;
		zep=h*(1-cos(sigma))/2;
	
		trot_leg_XYZ.z[0]=z;
		trot_leg_XYZ.z[1]=z;
		trot_leg_XYZ.z[2]=z;
		trot_leg_XYZ.z[3]=z+zep;
		
		trot_leg_XYZ.y[0]=yep_z3;
		trot_leg_XYZ.y[1]=yep_z1;
		trot_leg_XYZ.y[2]=yep_z2;
		trot_leg_XYZ.y[3]=yep_b;
		
		trot_leg_XYZ.x[0]=x;
		trot_leg_XYZ.x[1]=x;
		trot_leg_XYZ.x[2]=x;
		trot_leg_XYZ.x[3]=x;
		
	}
	
}

void trot_YZ(float t)
{
	x=-20;
	if (t<=Ts*faai)
	{
		sigma=2*MY_PI*t/(faai*Ts);
		zep=50*(1-cos(sigma))/2;
		yep_b_1=(yf_1-ys_1)*((sigma-sin(sigma))/(2*MY_PI))+ys_1;
		yep_z_1=(ys_1-yf_1)*((sigma-sin(sigma))/(2*MY_PI))+yf_1;
		yep_b_2=(yf_2-ys_2)*((sigma-sin(sigma))/(2*MY_PI))+ys_2;
		yep_z_2=(ys_2-yf_2)*((sigma-sin(sigma))/(2*MY_PI))+yf_2;
		yep_b_3=(yf_3-ys_3)*((sigma-sin(sigma))/(2*MY_PI))+ys_3;
		yep_z_3=(ys_3-yf_3)*((sigma-sin(sigma))/(2*MY_PI))+yf_3;
		yep_b_4=(yf_4-ys_4)*((sigma-sin(sigma))/(2*MY_PI))+ys_4;
		yep_z_4=(ys_4-yf_4)*((sigma-sin(sigma))/(2*MY_PI))+yf_4;
	
		trot_leg_XYZ.z[0]=z+zep;
		trot_leg_XYZ.z[1]=z;
		trot_leg_XYZ.z[2]=z+zep;
		trot_leg_XYZ.z[3]=z;
		
		trot_leg_XYZ.y[0]=yep_b_1;
		trot_leg_XYZ.y[1]=yep_z_2;
		trot_leg_XYZ.y[2]=yep_b_3;
		trot_leg_XYZ.y[3]=yep_z_4;
	
		trot_leg_XYZ.x[0]=0;
		trot_leg_XYZ.x[1]=0;
		trot_leg_XYZ.x[2]=-20;
		trot_leg_XYZ.x[3]=-20;
		
	}
	if (t>Ts*faai && t<Ts)
	{
		sigma=2*MY_PI*(t-Ts*faai)/(faai*Ts);
		zep=50*(1-cos(sigma))/2;
		yep_b_1=(yf_1-ys_1)*((sigma-sin(sigma))/(2*MY_PI))+ys_1;
		yep_z_1=(ys_1-yf_1)*((sigma-sin(sigma))/(2*MY_PI))+yf_1;
		yep_b_2=(yf_2-ys_2)*((sigma-sin(sigma))/(2*MY_PI))+ys_2;
		yep_z_2=(ys_2-yf_2)*((sigma-sin(sigma))/(2*MY_PI))+yf_2;
		yep_b_3=(yf_3-ys_3)*((sigma-sin(sigma))/(2*MY_PI))+ys_3;
		yep_z_3=(ys_3-yf_3)*((sigma-sin(sigma))/(2*MY_PI))+yf_3;
		yep_b_4=(yf_4-ys_4)*((sigma-sin(sigma))/(2*MY_PI))+ys_4;
		yep_z_4=(ys_4-yf_4)*((sigma-sin(sigma))/(2*MY_PI))+yf_4;
		
		trot_leg_XYZ.z[0]=z;
		trot_leg_XYZ.z[1]=z+zep;
		trot_leg_XYZ.z[2]=z;
		trot_leg_XYZ.z[3]=z+zep;
		
		trot_leg_XYZ.y[0]=yep_z_1;
		trot_leg_XYZ.y[1]=yep_b_2;
		trot_leg_XYZ.y[2]=yep_z_3;
		trot_leg_XYZ.y[3]=yep_b_4;
	
		trot_leg_XYZ.x[0]=0;
		trot_leg_XYZ.x[1]=0;
		trot_leg_XYZ.x[2]=-20;
		trot_leg_XYZ.x[3]=-20;
	
	}
	
	//========   步态融合+逆解   ========
		Get_Position();
		
		//=========   舵机输出   ==========
		dog_control();
}


//坐标调节器
void XYZ_Adjust(float x_goal,float y_goal,float z_goal)
{
	
	if (x_S>x_goal)
		x_S=x_S-ABS(x_S-x_goal)*Kp_G;
	else if (x_S<x_goal)
		x_S=x_S+ABS(x_S-x_goal)*Kp_G;

	if (y_S>y_goal)
		y_S=y_S-ABS(y_S-y_goal)*Kp_G;
	else if (y_S<y_goal)
		y_S=y_S+ABS(y_S-y_goal)*Kp_G;
	
	if (z_S>z_goal)
		z_S=z_S-ABS(z_S-z_goal)*Kp_G;
	else if (y_S<z_goal)
		z_S=z_S+ABS(z_S-z_goal)*Kp_G;
}


void contorl_1_leg(float x,float y,float z)
{
	
	trot_leg_XYZ.z[0]=z;
	trot_leg_XYZ.x[0]=x;	
	trot_leg_XYZ.y[0]=y;

}

void contorl_2_leg(float x,float y,float z)
{
	
	trot_leg_XYZ.z[1]=z;
	trot_leg_XYZ.x[1]=x;	
	trot_leg_XYZ.y[1]=y;

}

void contorl_3_leg(float x,float y,float z)
{
	
	trot_leg_XYZ.z[2]=z;
	trot_leg_XYZ.x[2]=x;	
	trot_leg_XYZ.y[2]=y;

}

void contorl_4_leg(float x,float y,float z)
{
	
	trot_leg_XYZ.z[3]=z;
	trot_leg_XYZ.x[3]=x;	
	trot_leg_XYZ.y[3]=y;

}



//=============   站立   ============
void stand(void)
{
	contorl_1_leg(20,0,-90);
	contorl_2_leg(20,0,-90);
	contorl_3_leg(-20,0,-90);
	contorl_4_leg(-20,0,-90);

	POS_Adjust(0,0,0,0);
	//========   步态融合+逆解   ========
		Get_Position();
		
		//=========   舵机输出   ==========
		dog_control();
}

////============   深蹲   ============
//void squat(void)
//{
//	xf=0;
//	xs=0;
//	stand();
//	trot_speed=0.005;
//	if (trot_t>=Ts)
//	{
//		trot_t=0;
//	}
//	else 
//	{
//		trot_t=trot_t+trot_speed;
//		if (trot_t<=Ts*faai)
//		{
//			sigma=2*MY_PI*trot_t/(faai*Ts);
//			zep=h*(1-cos(sigma))/2;
//			xep_b=(xf-xs)*((sigma-sin(sigma))/(2*MY_PI))+xs;
//			contorl_4_legs(xep_b,y+zep);
//		}
//		if (trot_t>Ts*faai && trot_t<Ts)
//		{
//			sigma=2*MY_PI*(trot_t-Ts*faai)/(faai*Ts);
//			zep=h*(1-cos(sigma))/2;
//			xep_b=(xf-xs)*((sigma-sin(sigma))/(2*MY_PI))+xs;
//			contorl_4_legs(xep_b,y+zep);
//		}
//	}
//	trot_speed=0.025;
//}

////===========   跳跃   ==========
//void jump(void)
//{
//	stand();
//	trot_speed=0.25;
//	while(1)
//	{
//		if (trot_t>=(prep_time + launch_time + fall_time))
//		{
//			trot_t=0;
//			break;
//		}
//		else 
//		{
//			trot_t=trot_t+trot_speed;
//			if (trot_t<=prep_time)
//			{
//				contorl_4_legs(x_jump,stance_height);
//			}
//			else if (trot_t>prep_time && trot_t<=(prep_time+launch_time))
//			{
//				contorl_4_legs(x_jump,jump_extension);

//			}
//			else if (trot_t>(prep_time+launch_time)&&trot_t<=(prep_time+launch_time+fall_time))
//			{
//				contorl_4_legs(x_jump,fall_extension);
//			}
//		}
//	}
//}

