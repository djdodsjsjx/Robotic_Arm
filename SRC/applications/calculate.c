#include "calculate.h"

//============   逆解   ==============
void caculate(void)
{
	
		//============  3自由度  ================
	float lxz[4],dyz[4],lyz[4];
		
	dyz[0]=sqrt(my_pow(mix_leg_XYZ.y[0])+my_pow(mix_leg_XYZ.z[0]));
	lyz[0]=sqrt(my_pow(dyz[0])-my_pow(l3));
	lxz[0]=sqrt(my_pow(lyz[0])+my_pow(mix_leg_XYZ.x[0]));
	leg_rotation_Angle.gamma [0]=atan(lyz[0]/l3)+atan(mix_leg_XYZ.z[0]/mix_leg_XYZ.y[0]);
	leg_rotation_Angle.beta [0]=MY_PI-acos((my_pow(l1)+my_pow(l2_12)-my_pow(lxz[0]))/(2*l1*l2_12));
	leg_rotation_Angle.alfa [0]=acos((my_pow(l1)+my_pow(lxz[0])-my_pow(l2_12))/(2*l1*lxz[0]))-atan(mix_leg_XYZ.x[0]/lyz[0]);
	leg_rotation_Angle.gamma [0]=180*leg_rotation_Angle.gamma [0]/MY_PI;
	leg_rotation_Angle.beta [0]=180*leg_rotation_Angle.beta [0]/MY_PI;
	leg_rotation_Angle.alfa [0]=180*leg_rotation_Angle.alfa [0]/MY_PI;
	
	dyz[1]=sqrt(my_pow(mix_leg_XYZ.y[1])+my_pow(mix_leg_XYZ.z[1]));
	lyz[1]=sqrt(my_pow(dyz[1])-my_pow(l3));
	lxz[1]=sqrt(my_pow(lyz[1])+my_pow(mix_leg_XYZ.x[1]));
	leg_rotation_Angle.gamma [1]=atan(lyz[1]/l3)+atan(mix_leg_XYZ.z[1]/mix_leg_XYZ.y[1]);
	leg_rotation_Angle.beta [1]=MY_PI-acos((my_pow(l1)+my_pow(l2_12)-my_pow(lxz[1]))/(2*l1*l2_12));
	leg_rotation_Angle.alfa [1]=acos((my_pow(l1)+my_pow(lxz[1])-my_pow(l2_12))/(2*l1*lxz[1]))-atan(mix_leg_XYZ.x[1]/lyz[1]);
	leg_rotation_Angle.gamma [1]=180*leg_rotation_Angle.gamma [1]/MY_PI;
	leg_rotation_Angle.beta [1]=180*leg_rotation_Angle.beta [1]/MY_PI;
	leg_rotation_Angle.alfa [1]=180*leg_rotation_Angle.alfa [1]/MY_PI;
	
	dyz[2]=sqrt(my_pow(mix_leg_XYZ.y[2])+my_pow(mix_leg_XYZ.z[2]));
	lyz[2]=sqrt(my_pow(dyz[2])-my_pow(l3));
	lxz[2]=sqrt(my_pow(lyz[2])+my_pow(mix_leg_XYZ.x[2]));
	leg_rotation_Angle.gamma [2]=atan(lyz[2]/l3)+atan(mix_leg_XYZ.z[2]/mix_leg_XYZ.y[2]);
	leg_rotation_Angle.beta [2]=MY_PI-acos((my_pow(l1)+my_pow(l2_34)-my_pow(lxz[2]))/(2*l1*l2_34));
	leg_rotation_Angle.alfa [2]=acos((my_pow(l1)+my_pow(lxz[2])-my_pow(l2_34))/(2*l1*lxz[2]))-atan(mix_leg_XYZ.x[2]/lyz[2]);
	leg_rotation_Angle.gamma [2]=180*leg_rotation_Angle.gamma [2]/MY_PI;
	leg_rotation_Angle.beta [2]=180*leg_rotation_Angle.beta [2]/MY_PI;
	leg_rotation_Angle.alfa [2]=180*leg_rotation_Angle.alfa [2]/MY_PI;
	
	dyz[3]=sqrt(my_pow(mix_leg_XYZ.y[3])+my_pow(mix_leg_XYZ.z[3]));
	lyz[3]=sqrt(my_pow(dyz[3])-my_pow(l3));
	lxz[3]=sqrt(my_pow(lyz[3])+my_pow(mix_leg_XYZ.x[3]));
	leg_rotation_Angle.gamma [3]=atan(lyz[3]/l3)+atan(mix_leg_XYZ.z[3]/mix_leg_XYZ.y[3]);
	leg_rotation_Angle.beta [3]=MY_PI-acos((my_pow(l1)+my_pow(l2_34)-my_pow(lxz[3]))/(2*l1*l2_34));
	leg_rotation_Angle.alfa [3]=acos((my_pow(l1)+my_pow(lxz[3])-my_pow(l2_34))/(2*l1*lxz[3]))-atan(mix_leg_XYZ.x[3]/lyz[3]);	
	leg_rotation_Angle.gamma [3]=180*leg_rotation_Angle.gamma [3]/MY_PI;
	leg_rotation_Angle.beta [3]=180*leg_rotation_Angle.beta [3]/MY_PI;
	leg_rotation_Angle.alfa [3]=180*leg_rotation_Angle.alfa [3]/MY_PI;
	
//	
//		
//	dyz[0]=sqrt(my_pow(mix_leg_XYZ.y[0])+my_pow(mix_leg_XYZ.z[0]));
//	lyz[0]=sqrt(my_pow(dyz[0])-my_pow(l3));
//	lxz[0]=sqrt(my_pow(lyz[0])+my_pow(mix_leg_XYZ.x[0]));
//	leg_rotation_Angle.gamma [0]=atan(lyz[0]/l3)+atan(mix_leg_XYZ.z[0]/mix_leg_XYZ.y[0]);
//	leg_rotation_Angle.beta [0]=MY_PI-acos((my_pow(l1)+my_pow(l2)-my_pow(lxz[0]))/(2*l1*l2));
//	leg_rotation_Angle.alfa [0]=acos((my_pow(l1)+my_pow(lxz[0])-my_pow(l2))/(2*l1*lxz[0]))-atan(mix_leg_XYZ.x[0]/lyz[0]);
//	leg_rotation_Angle.gamma [0]=180*leg_rotation_Angle.gamma [0]/MY_PI;
//	leg_rotation_Angle.beta [0]=180*leg_rotation_Angle.beta [0]/MY_PI;
//	leg_rotation_Angle.alfa [0]=180*leg_rotation_Angle.alfa [0]/MY_PI;
//	
//	dyz[1]=sqrt(my_pow(mix_leg_XYZ.y[1])+my_pow(mix_leg_XYZ.z[1]));
//	lyz[1]=sqrt(my_pow(dyz[1])-my_pow(l3));
//	lxz[1]=sqrt(my_pow(lyz[1])+my_pow(mix_leg_XYZ.x[1]));
//	leg_rotation_Angle.gamma [1]=atan(lyz[1]/l3)+atan(mix_leg_XYZ.z[1]/mix_leg_XYZ.y[1]);
//	leg_rotation_Angle.beta [1]=MY_PI-acos((my_pow(l1)+my_pow(l2)-my_pow(lxz[1]))/(2*l1*l2));
//	leg_rotation_Angle.alfa [1]=acos((my_pow(l1)+my_pow(lxz[1])-my_pow(l2))/(2*l1*lxz[1]))-atan(mix_leg_XYZ.x[1]/lyz[1]);
//	leg_rotation_Angle.gamma [1]=180*leg_rotation_Angle.gamma [1]/MY_PI;
//	leg_rotation_Angle.beta [1]=180*leg_rotation_Angle.beta [1]/MY_PI;
//	leg_rotation_Angle.alfa [1]=180*leg_rotation_Angle.alfa [1]/MY_PI;
//	
//	dyz[2]=sqrt(my_pow(mix_leg_XYZ.y[2])+my_pow(mix_leg_XYZ.z[2]));
//	lyz[2]=sqrt(my_pow(dyz[2])-my_pow(l3));
//	lxz[2]=sqrt(my_pow(lyz[2])+my_pow(mix_leg_XYZ.x[2]));
//	leg_rotation_Angle.gamma [2]=atan(lyz[2]/l3)+atan(mix_leg_XYZ.z[2]/mix_leg_XYZ.y[2]);
//	leg_rotation_Angle.beta [2]=MY_PI-acos((my_pow(l1)+my_pow(l2)-my_pow(lxz[2]))/(2*l1*l2));
//	leg_rotation_Angle.alfa [2]=acos((my_pow(l1)+my_pow(lxz[2])-my_pow(l2))/(2*l1*lxz[2]))-atan(mix_leg_XYZ.x[2]/lyz[2]);
//	leg_rotation_Angle.gamma [2]=180*leg_rotation_Angle.gamma [2]/MY_PI;
//	leg_rotation_Angle.beta [2]=180*leg_rotation_Angle.beta [2]/MY_PI;
//	leg_rotation_Angle.alfa [2]=180*leg_rotation_Angle.alfa [2]/MY_PI;
//	
//	dyz[3]=sqrt(my_pow(mix_leg_XYZ.y[3])+my_pow(mix_leg_XYZ.z[3]));
//	lyz[3]=sqrt(my_pow(dyz[3])-my_pow(l3));
//	lxz[3]=sqrt(my_pow(lyz[3])+my_pow(mix_leg_XYZ.x[3]));
//	leg_rotation_Angle.gamma [3]=atan(lyz[3]/l3)+atan(mix_leg_XYZ.z[3]/mix_leg_XYZ.y[3]);
//	leg_rotation_Angle.beta [3]=MY_PI-acos((my_pow(l1)+my_pow(l2)-my_pow(lxz[3]))/(2*l1*l2));
//	leg_rotation_Angle.alfa [3]=acos((my_pow(l1)+my_pow(lxz[3])-my_pow(l2))/(2*l1*lxz[3]))-atan(mix_leg_XYZ.x[3]/lyz[3]);	
//	leg_rotation_Angle.gamma [3]=180*leg_rotation_Angle.gamma [3]/MY_PI;
//	leg_rotation_Angle.beta [3]=180*leg_rotation_Angle.beta [3]/MY_PI;
//	leg_rotation_Angle.alfa [3]=180*leg_rotation_Angle.alfa [3]/MY_PI;



//	//============  2自由度  =============	
//	float fai0,fai1,fai2,fai3;
//	leg_rotation_Angle.beta [0]=MY_PI-acos((my_pow(mix_leg_XYZ.x[0])+my_pow(mix_leg_XYZ.z[0])-my_pow(l1)-my_pow(l2))/(-2*l1*l2));
//	fai0=acos((my_pow(l1)+my_pow(mix_leg_XYZ.x[0])+my_pow(mix_leg_XYZ.z[0])-my_pow(l2))/(2*l1*sqrt(my_pow(mix_leg_XYZ.x[0])+my_pow(mix_leg_XYZ.z[0]))));
//	if (mix_leg_XYZ.x[0]>0)
//			leg_rotation_Angle.alfa [0]=ABS(atan(mix_leg_XYZ.z[0]/mix_leg_XYZ.x[0]))-fai0;
//	else if (mix_leg_XYZ.x[0]<0)
//			leg_rotation_Angle.alfa [0]=MY_PI-ABS(atan(mix_leg_XYZ.z[0]/mix_leg_XYZ.x[0]))-fai0;
//	else
//			leg_rotation_Angle.alfa [0]=MY_PI/2.0-fai0;
//	leg_rotation_Angle.beta [0]=180*leg_rotation_Angle.beta [0]/MY_PI;
//	leg_rotation_Angle.alfa [0]=180*leg_rotation_Angle.alfa [0]/MY_PI;

//	
//	leg_rotation_Angle.beta [1]=MY_PI-acos((my_pow(mix_leg_XYZ.x[1])+my_pow(mix_leg_XYZ.z[1])-my_pow(l1)-my_pow(l2))/(-2*l1*l2));
//	fai1=acos((my_pow(l1)+my_pow(mix_leg_XYZ.x[1])+my_pow(mix_leg_XYZ.z[1])-my_pow(l2))/(2*l1*sqrt(my_pow(mix_leg_XYZ.x[1])+my_pow(mix_leg_XYZ.z[1]))));
//	if (mix_leg_XYZ.x[1]>0)
//			leg_rotation_Angle.alfa [1]=ABS(atan(mix_leg_XYZ.z[1]/mix_leg_XYZ.x[1]))-fai1;
//	else if (mix_leg_XYZ.x[1]<0)
//			leg_rotation_Angle.alfa [1]=MY_PI-ABS(atan(mix_leg_XYZ.z[1]/mix_leg_XYZ.x[1]))-fai1;
//	else
//			leg_rotation_Angle.alfa [1]=MY_PI/2.0-fai1;
//	leg_rotation_Angle.beta [1]=180*leg_rotation_Angle.beta [1]/MY_PI;
//	leg_rotation_Angle.alfa [1]=180*leg_rotation_Angle.alfa [1]/MY_PI;
//	

//	leg_rotation_Angle.beta [2]=MY_PI-acos((my_pow(mix_leg_XYZ.x[2])+my_pow(mix_leg_XYZ.z[2])-my_pow(l1)-my_pow(l2))/(-2*l1*l2));
//	fai2=acos((my_pow(l1)+my_pow(mix_leg_XYZ.x[2])+my_pow(mix_leg_XYZ.z[2])-my_pow(l2))/(2*l1*sqrt(my_pow(mix_leg_XYZ.x[2])+my_pow(mix_leg_XYZ.z[2]))));
//	if (mix_leg_XYZ.x[2]>0)
//			leg_rotation_Angle.alfa [2]=ABS(atan(mix_leg_XYZ.z[2]/mix_leg_XYZ.x[0]))-fai2;
//	else if (mix_leg_XYZ.x[2]<0)
//			leg_rotation_Angle.alfa [2]=MY_PI-ABS(atan(mix_leg_XYZ.z[2]/mix_leg_XYZ.x[2]))-fai2;
//	else
//			leg_rotation_Angle.alfa [2]=MY_PI/2.0-fai2;
//	leg_rotation_Angle.beta [2]=180*leg_rotation_Angle.beta [2]/MY_PI;
//	leg_rotation_Angle.alfa [2]=180*leg_rotation_Angle.alfa [2]/MY_PI;

//	
//	leg_rotation_Angle.beta [3]=MY_PI-acos((my_pow(mix_leg_XYZ.x[3])+my_pow(mix_leg_XYZ.z[3])-my_pow(l1)-my_pow(l2))/(-2*l1*l2));
//	fai3=acos((my_pow(l1)+my_pow(mix_leg_XYZ.x[3])+my_pow(mix_leg_XYZ.z[3])-my_pow(l2))/(2*l1*sqrt(my_pow(mix_leg_XYZ.x[3])+my_pow(mix_leg_XYZ.z[3]))));
//	if (mix_leg_XYZ.x[3]>0)
//			leg_rotation_Angle.alfa [3]=ABS(atan(mix_leg_XYZ.z[3]/mix_leg_XYZ.x[3]))-fai3;
//	else if (mix_leg_XYZ.x[3]<0)
//			leg_rotation_Angle.alfa [3]=MY_PI-ABS(atan(mix_leg_XYZ.z[3]/mix_leg_XYZ.x[3]))-fai3;
//	else
//			leg_rotation_Angle.alfa [3]=MY_PI/2.0-fai3;
//	leg_rotation_Angle.beta [3]=180*leg_rotation_Angle.beta [3]/MY_PI;
//	leg_rotation_Angle.alfa [3]=180*leg_rotation_Angle.alfa [3]/MY_PI;
//	

}


