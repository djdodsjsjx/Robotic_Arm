#ifndef __FILTER_H
#define __FILTER_H

#include "config.h"
#define Kp 100.0f // ��������֧�������������ٶȼ�/��ǿ��
#define Ki 0.002f // ��������֧���ʵ�������ƫ�����ν�
#define halfT 0.001f // �������ڵ�һ��
#define PI 3.14159265

extern s16 Dog_ROL,Dog_PIT;
float Kalman_Filter(float Accel,float Gyro);	
void Get_Angle(void);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az);

#endif
