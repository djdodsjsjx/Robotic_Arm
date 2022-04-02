#ifndef __FILTER_H
#define __FILTER_H

#include "config.h"
#define Kp 100.0f // 比例增益支配率收敛到加速度计/磁强计
#define Ki 0.002f // 积分增益支配率的陀螺仪偏见的衔接
#define halfT 0.001f // 采样周期的一半
#define PI 3.14159265

extern s16 Dog_ROL,Dog_PIT;
float Kalman_Filter(float Accel,float Gyro);	
void Get_Angle(void);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

#endif
