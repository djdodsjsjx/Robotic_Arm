#include "mpuiic.h"


/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Init(void)
*��������:		��ʼ��I2C��Ӧ�Ľӿ����š�
*******************************************************************************/
void MPU_IIC_Init(void)
{			
	RCC->APB2ENR|=1<<2;//��ʹ������IO PORTAʱ�� 							 
	GPIOA->CRH&=0XFFFF0FF0;//PA8/11 �������
	GPIOA->CRH|=0X00003003;	   
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Start(void)
*��������:		����IIC��ʼ�ź�
*******************************************************************************/
int MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda�����
	MPU_IIC_SDA=1;
	if(!MPU_READ_SDA)return 0;	
	MPU_IIC_SCL=1;
	Delay_us(1);
 	MPU_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	if(MPU_READ_SDA)return 0;
	Delay_us(1);
	MPU_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	return 1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Stop(void)
*��������:	    //����IICֹͣ�ź�
*******************************************************************************/	  
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda�����
	MPU_IIC_SCL=0;
	MPU_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(1);
	MPU_IIC_SCL=1; 
	MPU_IIC_SDA=1;//����I2C���߽����ź�
	Delay_us(1);							   	
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IIC_Wait_Ack(void)
*��������:	    �ȴ�Ӧ���źŵ��� 
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
*******************************************************************************/
int MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
	MPU_IIC_SDA=1;
	Delay_us(1);	   
	MPU_IIC_SCL=1;
	Delay_us(1);	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			MPU_IIC_Stop();
			return 0;
		}
	  Delay_us(1);
	}
	MPU_IIC_SCL=0;//ʱ�����0 	   
	return 1;  
} 

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Ack(void)
*��������:	    ����ACKӦ��
*******************************************************************************/
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=0;
	Delay_us(1);
	MPU_IIC_SCL=1;
	Delay_us(1);
	MPU_IIC_SCL=0;
}
	
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_NAck(void)
*��������:	    ����NACKӦ��
*******************************************************************************/	    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=1;
	Delay_us(1);
	MPU_IIC_SCL=1;
	Delay_us(1);
	MPU_IIC_SCL=0;
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Send_Byte(u8 txd)
*��������:	    IIC����һ���ֽ�
*******************************************************************************/		  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU_SDA_OUT(); 	    
    MPU_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        MPU_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		Delay_us(1);   
		MPU_IIC_SCL=1;
		Delay_us(1); 
		MPU_IIC_SCL=0;	
		Delay_us(1);
    }	 
} 	 
  
/**************************ʵ�ֺ���********************************************
*����ԭ��:		bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data)
*��������:		
*******************************************************************************/
int MPU_i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
		int i;
    if (!MPU_IIC_Start())
        return 1;
    MPU_IIC_Send_Byte(addr << 1 );
    if (!MPU_IIC_Wait_Ack()) {
        MPU_IIC_Stop();
        return 1;
    }
    MPU_IIC_Send_Byte(reg);
    MPU_IIC_Wait_Ack();
		for (i = 0; i < len; i++) {
        MPU_IIC_Send_Byte(data[i]);
        if (!MPU_IIC_Wait_Ack()) {
            MPU_IIC_Stop();
            return 0;
        }
    }
    MPU_IIC_Stop();
    return 0;
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data)
*��������:		
*******************************************************************************/
int MPU_i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!MPU_IIC_Start())
        return 1;
    MPU_IIC_Send_Byte(addr << 1);
    if (!MPU_IIC_Wait_Ack()) {
        MPU_IIC_Stop();
        return 1;
    }
    MPU_IIC_Send_Byte(reg);
    MPU_IIC_Wait_Ack();
    MPU_IIC_Start();
    MPU_IIC_Send_Byte((addr << 1)+1);
    MPU_IIC_Wait_Ack();
    while (len) {
        if (len == 1)
            *buf = MPU_IIC_Read_Byte(0);
        else
            *buf = MPU_IIC_Read_Byte(1);
        buf++;
        len--;
    }
    MPU_IIC_Stop();
    return 0;
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IIC_Read_Byte(unsigned char ack)
*��������:	    //��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
*******************************************************************************/  
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL=0; 
        Delay_us(2);
		MPU_IIC_SCL=1;
        receive<<=1;
        if(MPU_READ_SDA)receive++;   
		Delay_us(2); 
    }					 
    if (ack)
        MPU_IIC_Ack(); //����ACK 
    else
        MPU_IIC_NAck();//����nACK  
    return receive;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	I2C_Addr  Ŀ���豸��ַ
		addr	   �Ĵ�����ַ
����   ��������ֵ
*******************************************************************************/ 
unsigned char MPU_I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	MPU_IIC_Start();	
	MPU_IIC_Send_Byte(I2C_Addr);	   //����д����
	res++;
	MPU_IIC_Wait_Ack();
	MPU_IIC_Send_Byte(addr); res++;  //���͵�ַ
	MPU_IIC_Wait_Ack();	  
	//IIC_Stop();//����һ��ֹͣ����	
	MPU_IIC_Start();
	MPU_IIC_Send_Byte(I2C_Addr+1); res++;          //�������ģʽ			   
	MPU_IIC_Wait_Ack();
	res=MPU_IIC_Read_Byte(0);	   
    MPU_IIC_Stop();//����һ��ֹͣ����

	return res;
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ����� length��ֵ
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫ�����ֽ���
		*data  ���������ݽ�Ҫ��ŵ�ָ��
����   ���������ֽ�����
*******************************************************************************/ 
u8 MPU_IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data){
    u8 count = 0;
	
	MPU_IIC_Start();
	MPU_IIC_Send_Byte(dev);	   //����д����
	MPU_IIC_Wait_Ack();
	MPU_IIC_Send_Byte(reg);   //���͵�ַ
    MPU_IIC_Wait_Ack();	  
	MPU_IIC_Start();
	MPU_IIC_Send_Byte(dev+1);  //�������ģʽ	
	MPU_IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=MPU_IIC_Read_Byte(1);  //��ACK�Ķ�����
		 	else  data[count]=MPU_IIC_Read_Byte(0);	 //���һ���ֽ�NACK
	}
    MPU_IIC_Stop();//����һ��ֹͣ����
    return count;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*��������:	    ������ֽ�д��ָ���豸 ָ���Ĵ���
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫд���ֽ���
		*data  ��Ҫд�����ݵ��׵�ַ
����   �����Ƿ�ɹ�
*******************************************************************************/ 
u8 MPU_IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	MPU_IIC_Start();
	MPU_IIC_Send_Byte(dev);	   //����д����
	MPU_IIC_Wait_Ack();
	MPU_IIC_Send_Byte(reg);   //���͵�ַ
    MPU_IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		MPU_IIC_Send_Byte(data[count]); 
		MPU_IIC_Wait_Ack(); 
	 }
	MPU_IIC_Stop();//����һ��ֹͣ����

    return 1; //status == 0;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICreadByte(u8 dev, u8 reg, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		*data  ���������ݽ�Ҫ��ŵĵ�ַ
����   1
*******************************************************************************/ 


u8 MPU_IICreadByte(u8 dev, u8 reg, u8 *data){
	*data=MPU_I2C_ReadOneByte(dev, reg);
    return 1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*��������:	    д��ָ���豸 ָ���Ĵ���һ���ֽ�
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		data  ��Ҫд����ֽ�
����   1
*******************************************************************************/ 
unsigned char MPU_IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return MPU_IICwriteBytes(dev, reg, 1, &data);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �еĶ��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitStart  Ŀ���ֽڵ���ʼλ
		length   λ����
		data    ��Ÿı�Ŀ���ֽ�λ��ֵ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 

u8 MPU_IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (MPU_IICreadByte(dev, reg, &b) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return MPU_IICwriteByte(dev, reg, b);
    } else {
        return 0;
    }
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �е�1��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitNum  Ҫ�޸�Ŀ���ֽڵ�bitNumλ
		data  Ϊ0 ʱ��Ŀ��λ������0 ���򽫱���λ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 
u8 MPU_IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data){
    u8 b;
    MPU_IICreadByte(dev, reg, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return MPU_IICwriteByte(dev, reg, b);
}

//------------------End of File----------------------------
