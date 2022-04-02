#ifndef __MEARM_H
#define __MEARM_H
#include "config.h"


typedef struct
{
	float x;
	float y;
	float z;
}MEARM_XYZ;

typedef struct
{
	float alfa;
	float beta;
	float gamma;
	float pliers;
}MEARM_Angle;

extern MEARM_XYZ mearm_xyz;
extern MEARM_Angle mearm_action_angle;
extern MEARM_Angle mearm_init_angle;
extern u8 MEARM_state;
extern float l1,l2,speed;

void mearm_control(void);
void trajectory(float mearm_goal_x,float mearm_goal_y,float mearm_goal_z);
void Inverse_Kinematics(void);
void mearm_servo_output(void);
void pliers_servo(u8 a);
void position(u8 cmd,u16 value);
#endif
