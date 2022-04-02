#include "Posture_control.h"

float PIT_S=0,ROL_S=0,POS_X_S=0,POS_Z_S=0;

//============   ×ËÌ¬µ÷½Ú   =============
void POS_Adjust(float ROL_goal,float PIT_goal,float POS_X_goal,float POS_Z_goal)
{
	if (PIT_S>PIT_goal)
		PIT_S=PIT_S-ABS(PIT_S-PIT_goal)*Kp_G;
	else if (PIT_S<PIT_goal)
		PIT_S=PIT_S+ABS(PIT_S-PIT_goal)*Kp_G;

	if (ROL_S>ROL_goal)
		ROL_S=ROL_S-ABS(ROL_S-ROL_goal)*Kp_G;
	else if (ROL_S<ROL_goal)
		ROL_S=ROL_S+ABS(ROL_S-ROL_goal)*Kp_G;
	
	if (POS_X_S>POS_X_goal)
		POS_X_S=POS_X_S-ABS(POS_X_S-POS_X_goal)*Kp_G;
	else if (POS_X_S<POS_X_goal)
		POS_X_S=POS_X_S+ABS(POS_X_S-POS_X_goal)*Kp_G;

	if (POS_Z_S>POS_Z_goal)
		POS_Z_S=POS_Z_S-ABS(POS_Z_S-POS_Z_goal)*Kp_G;
	else if (POS_Z_S<ROL_goal)
		POS_Z_S=POS_Z_S+ABS(POS_Z_S-POS_Z_goal)*Kp_G;
	
	cal_ges(ROL_S,PIT_S,0,POS_X_S,0,POS_Z_S);
//	printf("PIT_S:%f\n",PIT_S);
	
}

//===========   ×ËÌ¬¿ØÖÆ   ==============
void cal_ges(float ROL,float PIT,float YAW,float POS_X,float POS_Y,float POS_Z)
{
	float P=PIT*MY_PI/180;
	float R=ROL*MY_PI/180;
	float Y=YAW*MY_PI/180;
	
	
//	pos_leg_XYZ.x[0]=-POS_X  -  (l*cos(P)*cos(Y))/2-(b*cos(P)*sin(Y))/2 +l/2 ;
//	pos_leg_XYZ.y[0]=-POS_Y  -  (b*(cos(R)*cos(Y) + sin(P)*sin(R)*sin(Y)))/2 - (l*(cos(R)*sin(Y) - cos(Y)*sin(P)*sin(R)))/2   +  w/2;
//	pos_leg_XYZ.z[0]=-POS_Z  -  (b*(cos(Y)*sin(R) - cos(R)*sin(P)*sin(Y)))/2 - (l*(sin(R)*sin(Y) + cos(R)*cos(Y)*sin(P)))/2;

//	pos_leg_XYZ.x[1]=-POS_X  -  (l*cos(P)*cos(Y))/2+(b*cos(P)*sin(Y))/2 +l/2 ;
//	pos_leg_XYZ.y[1]=-POS_Y  +  (b*(cos(R)*cos(Y) + sin(P)*sin(R)*sin(Y)))/2 - (l*(cos(R)*sin(Y) - cos(Y)*sin(P)*sin(R)))/2   -  w/2;
//	pos_leg_XYZ.z[1]=-POS_Z  +  (b*(cos(Y)*sin(R) - cos(R)*sin(P)*sin(Y)))/2 - (l*(sin(R)*sin(Y) + cos(R)*cos(Y)*sin(P)))/2;

//	pos_leg_XYZ.x[2]=-POS_X  +  (l*cos(P)*cos(Y))/2+(b*cos(P)*sin(Y))/2 -l/2;
//	pos_leg_XYZ.y[2]=-POS_Y  +  (b*(cos(R)*cos(Y) + sin(P)*sin(R)*sin(Y)))/2 + (l*(cos(R)*sin(Y) - cos(Y)*sin(P)*sin(R)))/2   -  w/2;
//	pos_leg_XYZ.z[2]=-POS_Z  +  (b*(cos(Y)*sin(R) - cos(R)*sin(P)*sin(Y)))/2 + (l*(sin(R)*sin(Y) + cos(R)*cos(Y)*sin(P)))/2;

//	pos_leg_XYZ.x[3]=-POS_X  +  (l*cos(P)*cos(Y))/2-(b*cos(P)*sin(Y))/2 -l/2;
//	pos_leg_XYZ.y[3]=-POS_Y  -  (b*(cos(R)*cos(Y) + sin(P)*sin(R)*sin(Y)))/2 + (l*(cos(R)*sin(Y) - cos(Y)*sin(P)*sin(R)))/2   +  w/2 ;
//	pos_leg_XYZ.z[3]=-POS_Z  -  (b*(cos(Y)*sin(R) - cos(R)*sin(P)*sin(Y)))/2 + (l*(sin(R)*sin(Y) + cos(R)*cos(Y)*sin(P)))/2;
	
	pos_leg_XYZ.x[0]=-POS_X  -  (l*cos(R)*cos(Y))/2-(b*cos(R)*sin(Y))/2 +l/2 ;
	pos_leg_XYZ.y[0]=-POS_Y  -  (b*(cos(P)*cos(Y) + sin(R)*sin(P)*sin(Y)))/2 - (l*(cos(P)*sin(Y) - cos(Y)*sin(R)*sin(P)))/2   +  w/2;
	pos_leg_XYZ.z[0]=-POS_Z  -  (b*(cos(Y)*sin(P) - cos(P)*sin(R)*sin(Y)))/2 - (l*(sin(P)*sin(Y) + cos(P)*cos(Y)*sin(R)))/2;

	pos_leg_XYZ.x[1]=-POS_X  -  (l*cos(R)*cos(Y))/2+(b*cos(R)*sin(Y))/2 +l/2 ;
	pos_leg_XYZ.y[1]=-POS_Y  +  (b*(cos(P)*cos(Y) + sin(R)*sin(P)*sin(Y)))/2 - (l*(cos(P)*sin(Y) - cos(Y)*sin(R)*sin(P)))/2   -  w/2;
	pos_leg_XYZ.z[1]=-POS_Z  +  (b*(cos(Y)*sin(P) - cos(P)*sin(R)*sin(Y)))/2 - (l*(sin(P)*sin(Y) + cos(P)*cos(Y)*sin(R)))/2;

	pos_leg_XYZ.x[2]=-POS_X  +  (l*cos(R)*cos(Y))/2+(b*cos(R)*sin(Y))/2 -l/2;
	pos_leg_XYZ.y[2]=-POS_Y  +  (b*(cos(P)*cos(Y) + sin(R)*sin(P)*sin(Y)))/2 + (l*(cos(P)*sin(Y) - cos(Y)*sin(R)*sin(P)))/2   -  w/2;
	pos_leg_XYZ.z[2]=-POS_Z  +  (b*(cos(Y)*sin(P) - cos(P)*sin(R)*sin(Y)))/2 + (l*(sin(P)*sin(Y) + cos(P)*cos(Y)*sin(R)))/2;

	pos_leg_XYZ.x[3]=-POS_X  +  (l*cos(R)*cos(Y))/2-(b*cos(R)*sin(Y))/2 -l/2;
	pos_leg_XYZ.y[3]=-POS_Y  -  (b*(cos(P)*cos(Y) + sin(R)*sin(P)*sin(Y)))/2 + (l*(cos(P)*sin(Y) - cos(Y)*sin(R)*sin(P)))/2   +  w/2 ;
	pos_leg_XYZ.z[3]=-POS_Z  -  (b*(cos(Y)*sin(P) - cos(P)*sin(R)*sin(Y)))/2 + (l*(sin(P)*sin(Y) + cos(P)*cos(Y)*sin(R)))/2;
	
}

