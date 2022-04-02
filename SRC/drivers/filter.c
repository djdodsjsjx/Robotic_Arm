#include "filter.h"

s16 Dog_ROL,Dog_PIT;

float K1_X =0.02; 
float angle_X, angle_dot_X; 	
float Q_angle_X=0.001;// ����������Э����
float Q_gyro_X=0.003;//0.03 ����������Э���� ����������Э����Ϊһ��һ�����о���
float R_angle_X=0.5;// ����������Э���� �Ȳ���ƫ��
float dt_X=0.005;//                 
char  C_0_X = 1;
float Q_bias_X, Angle_err_X;
float PCt_0_X, PCt_1_X, E_X;
float K_0_X, K_1_X, t_0_X, t_1_X;
float Pdot_X[4] ={0,0,0,0};
float PP_X[2][2] = { { 1, 0 },{ 0, 1 } };

float K1_Y =0.02; 
float angle_Y, angle_dot_Y; 	
float Q_angle_Y=0.001;// ����������Э����
float Q_gyro_Y=0.003;//0.03 ����������Э���� ����������Э����Ϊһ��һ�����о���
float R_angle_Y=0.5;// ����������Э���� �Ȳ���ƫ��
float dt_Y=0.005;//                 
char  C_0_Y = 1;
float Q_bias_Y, Angle_err_Y;
float PCt_0_Y, PCt_1_Y, E_Y;
float K_0_Y, K_1_Y, t_0_Y, t_1_Y;
float Pdot_Y[4] ={0,0,0,0};
float PP_Y[2][2] = { { 1, 0 },{ 0, 1 } };
	
float K1_Z =0.02; 
float angle_Z, angle_dot_Z; 	
float Q_angle_Z=0.001;// ����������Э����
float Q_gyro_Z=0.003;//0.03 ����������Э���� ����������Э����Ϊһ��һ�����о���
float R_angle_Z=0.5;// ����������Э���� �Ȳ���ƫ��
float dt_Z=0.005;//                 
char  C_0_Z = 1;
float Q_bias_Z, Angle_err_Z;
float PCt_0_Z, PCt_1_Z, E_Z;
float K_0_Z, K_1_Z, t_0_Z, t_1_Z;
float Pdot_Z[4] ={0,0,0,0};
float PP_Z[2][2] = { { 1, 0 },{ 0, 1 } };
/**************************************************************************
�������ܣ����׿������˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/

float	Kalman_Filter_X(float Accel_X,float Gyro_X)		
{

	angle_X+=(Gyro_X - Q_bias_X) * dt_X; //�������
	Pdot_X[0]=Q_angle_X- PP_X[0][1] - PP_X[1][0]; // Pk-����������Э�����΢��

	Pdot_X[1]=-PP_X[1][1];
	Pdot_X[2]=-PP_X[1][1];
	Pdot_X[3]=Q_gyro_X;
	PP_X[0][0] += Pdot_X[0] * dt_X;   // Pk-����������Э����΢�ֵĻ���
	PP_X[0][1] += Pdot_X[1] * dt_X;   // =����������Э����
	PP_X[1][0] += Pdot_X[2] * dt_X;
	PP_X[1][1] += Pdot_X[3] * dt_X;
		
	Angle_err_X = Accel_X - angle_X;	//zk-�������
	
	PCt_0_X = C_0_X * PP_X[0][0];
	PCt_1_X = C_0_X * PP_X[1][0];
	
	E_X = R_angle_X + C_0_X * PCt_0_X;
	
	K_0_X = PCt_0_X / E_X;
	K_1_X = PCt_1_X / E_X;
	
	t_0_X = PCt_0_X;
	t_1_X = C_0_X * PP_X[0][1];

	PP_X[0][0] -= K_0_X * t_0_X;		 //����������Э����
	PP_X[0][1] -= K_0_X * t_1_X;
	PP_X[1][0] -= K_1_X * t_0_X;
	PP_X[1][1] -= K_1_X * t_1_X;
		
	angle_X	+= K_0_X * Angle_err_X;	 //�������
	Q_bias_X	+= K_1_X * Angle_err_X;	 //�������
	angle_dot_X   = Gyro_X - Q_bias_X;	 //���ֵ(�������)��΢��=���ٶ�
	return angle_X;
}

float	Kalman_Filter_Y(float Accel_Y,float Gyro_Y)		
{


	angle_Y+=(Gyro_Y - Q_bias_Y) * dt_Y; //�������
	Pdot_Y[0]=Q_angle_Y- PP_Y[0][1] - PP_Y[1][0]; // Pk-����������Э�����΢��

	Pdot_Y[1]=-PP_Y[1][1];
	Pdot_Y[2]=-PP_Y[1][1];
	Pdot_Y[3]=Q_gyro_Y;
	PP_Y[0][0] += Pdot_Y[0] * dt_Y;   // Pk-����������Э����΢�ֵĻ���
	PP_Y[0][1] += Pdot_Y[1] * dt_Y;   // =����������Э����
	PP_Y[1][0] += Pdot_Y[2] * dt_Y;
	PP_Y[1][1] += Pdot_Y[3] * dt_Y;
		
	Angle_err_Y = Accel_Y - angle_Y;	//zk-�������
	
	PCt_0_Y = C_0_Y * PP_Y[0][0];
	PCt_1_Y = C_0_Y * PP_Y[1][0];
	
	E_Y = R_angle_Y + C_0_Y * PCt_0_Y;
	
	K_0_Y = PCt_0_Y / E_Y;
	K_1_Y = PCt_1_Y / E_Y;
	
	t_0_Y = PCt_0_Y;
	t_1_Y = C_0_Y * PP_Y[0][1];

	PP_Y[0][0] -= K_0_Y * t_0_Y;		 //����������Э����
	PP_Y[0][1] -= K_0_Y * t_1_Y;
	PP_Y[1][0] -= K_1_Y * t_0_Y;
	PP_Y[1][1] -= K_1_Y * t_1_Y;
		
	angle_Y	+= K_0_Y * Angle_err_Y;	 //�������
	Q_bias_Y	+= K_1_Y * Angle_err_Y;	 //�������
	angle_dot_Y  = Gyro_Y - Q_bias_Y;	 //���ֵ(�������)��΢��=���ٶ�
	return angle_Y;
}



float	Kalman_Filter_Z(float Accel_Z,float Gyro_Z)		
{

	angle_Z+=(Gyro_Z - Q_bias_Z) * dt_Z; //�������
	Pdot_Z[0]=Q_angle_Z- PP_Z[0][1] - PP_Z[1][0]; // Pk-����������Э�����΢��

	Pdot_Z[1]=-PP_Z[1][1];
	Pdot_Z[2]=-PP_Z[1][1];
	Pdot_Z[3]=Q_gyro_Z;
	PP_Z[0][0] += Pdot_Z[0] * dt_Z;   // Pk-����������Э����΢�ֵĻ���
	PP_Z[0][1] += Pdot_Z[1] * dt_Z;   // =����������Э����
	PP_Z[1][0] += Pdot_Z[2] * dt_Z;
	PP_Z[1][1] += Pdot_Z[3] * dt_Z;
		
	Angle_err_Z = Accel_Z - angle_Z;	//zk-�������
	
	PCt_0_Z = C_0_Z * PP_Z[0][0];
	PCt_1_Z = C_0_Z * PP_Z[1][0];
	
	E_Z = R_angle_Z + C_0_Z * PCt_0_Z;
	
	K_0_Z = PCt_0_Z / E_Z;
	K_1_Z = PCt_1_Z / E_Z;
	
	t_0_Z = PCt_0_Z;
	t_1_Z = C_0_Z * PP_Z[0][1];

	PP_Z[0][0] -= K_0_Z * t_0_Z;		 //����������Э����
	PP_Z[0][1] -= K_0_Z * t_1_Z;
	PP_Z[1][0] -= K_1_Z * t_0_Z;
	PP_Z[1][1] -= K_1_Z * t_1_Z;
		
	angle_Z	+= K_0_Z * Angle_err_Z;	 //�������
	Q_bias_Z	+= K_1_Z * Angle_err_Z;	 //�������
	angle_dot_Z  = Gyro_Z - Q_bias_Z;	 //���ֵ(�������)��΢��=���ٶ�
	return angle_Z;
}

//===========   ��ȡ����Ǻ͸�����   ============
void Get_Angle(void)
{
		float Accel_Y,Accel_X,Gyro_Y,Gyro_X;
		float MPU_Accel_X,MPU_Accel_Z,MPU_Accel_Y,MPU_Gyro_Y,MPU_Gyro_X,MPU_Gyro_Z;
	
		MPU_Gyro_Y=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
		MPU_Gyro_X=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L); 
		MPU_Gyro_Z=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L); 
		if(MPU_Gyro_Y>32768)  MPU_Gyro_Y-=65536;     //��������ת��  Ҳ��ͨ��shortǿ������ת��
		if(MPU_Gyro_X>32768)  MPU_Gyro_X-=65536;
		if(MPU_Gyro_Z>32768)  MPU_Gyro_Z-=65536;
		Gyro_Y=MPU_Gyro_Y/16.4;                                    //����������ת��	
		Gyro_X=MPU_Gyro_X/16.4;                                    //����������ת��	
//		Gyro_Z=MPU_Gyro_Z/16.4;                                    //����������ת��	

		MPU_Accel_Z=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L);    //��ȡZ��������
		MPU_Accel_X=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
		MPU_Accel_Y=(MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+MPU_I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L);
		if(MPU_Accel_Y>32768) MPU_Accel_Y-=65536;
		if(MPU_Accel_Z>32768) MPU_Accel_Z-=65536;     //��������ת��
		if(MPU_Accel_X>32768) MPU_Accel_X-=65536;    //��������ת��
	
		Accel_Y=atan2(MPU_Accel_X,MPU_Accel_Z)*180.0/PI;                 //���������ļн�	
		Accel_X=atan2(MPU_Accel_Y,MPU_Accel_Z)*180.0/PI; 
 
		
		Dog_PIT=Kalman_Filter_Y(Accel_Y,-Gyro_Y);//�������˲�	
		Dog_ROL=Kalman_Filter_X(Accel_X,Gyro_X);


		DT_Send03(Dog_ROL,Dog_PIT,0,1);
//	printf("Dog_ROL:%d,Dog_PIT:%d\n",Dog_ROL,Dog_PIT);
				
}

//==========   ��Ԫ����  ����֤    ============
//void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)

//{

//float q0 = 1, q1 = 0, q2 = 0, q3 = 0; // ��Ԫ����Ԫ�أ�������Ʒ���

//float exInt = 0, eyInt = 0, ezInt = 0; // ��������С�������

//float Yaw,Pitch,Roll; //ƫ���ǣ������ǣ�������

//float norm;

//float vx, vy, vz;

//float ex, ey, ez;

//// ����������

//norm = sqrt(ax*ax + ay*ay + az*az);

//ax = ax / norm; //��λ��

//ay = ay / norm;

//az = az / norm;

//// ���Ʒ��������

//vx = 2*(q1*q3 - q0*q2);

//vy = 2*(q0*q1 + q2*q3);

//vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

//// ���������ͷ��򴫸��������ο�����֮��Ľ���˻����ܺ�

//ex = (ay*vz - az*vy);

//ey = (az*vx - ax*vz);

//ez = (ax*vy - ay*vx);

//// ������������������

//exInt = exInt + ex*Ki;

//eyInt = eyInt + ey*Ki;

//ezInt = ezInt + ez*Ki;

//// ������������ǲ���

//gx = gx + Kp*ex + exInt;

//gy = gy + Kp*ey + eyInt;

//gz = gz + Kp*ez + ezInt;

//// ������Ԫ���ʺ�������

//q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;

//q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;

//q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;

//q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

//// ��������Ԫ

//norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);

//q0 = q0 / norm;

//q1 = q1 / norm;

//q2 = q2 / norm;

//q3 = q3 / norm;

//Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch ,ת��Ϊ����

//Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // rollv

//Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3; //�˴�û�м�ֵ��ע��

//DT_Send03(Pitch,Roll,Yaw,1);
//}
