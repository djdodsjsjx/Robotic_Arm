#ifndef __POSTURE_CONTROL_H
#define __POSTURE_CONTROL_H
#include "config.h"

extern float PIT_S,ROL_S,POS_X_S,POS_Z_S;

void POS_Adjust(float ROL_goal,float PIT_goal,float POS_X_goal,float POS_Z_goal);
void cal_ges(float ROL,float PIT,float YAW,float POS_X,float POS_Y,float POS_Z);


	
#endif
