#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS	0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);		//?
	MyI2C_ReceiveAck();
	
	Data = MyI2C_ReceiveByte();
	//MyI2C_SendAck(0);
	
	MyI2C_SendAck(1);
	
	MyI2C_Stop();
	
	return Data;
}

void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);

}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH,DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}

uint8_t MPU6050_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
//	if(len==1){
//		MPU6050_WriteReg(reg, buf[0]);
//		return 0;
//	}
//	
	uint8_t i;
	MyI2C_Start();
	MyI2C_SendByte((addr<<1)|0);
	if (MyI2C_ReceiveAck())
	{
		MyI2C_Stop();
		return 1;
	}
	MyI2C_SendByte(reg);
	MyI2C_ReceiveAck();
	for (i=0; i<len; i++){
		MyI2C_SendByte(buf[i]);
		if (MyI2C_ReceiveAck())
		{
			MyI2C_Stop();
			return 1;
		}
	}
	MyI2C_Stop();
	return 0;
}

uint8_t MPU6050_Read_Len (uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	MyI2C_Start();
	MyI2C_SendByte((addr<<1)|0);
	if (MyI2C_ReceiveAck())
	{
		MyI2C_Stop();
		return 1;
	}
//	MyI2C_ReceiveAck();
	MyI2C_SendByte(reg);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte((addr<<1)|1);		//?
	MyI2C_ReceiveAck();
	
	while (len)
	{
		if(len==1)
		{
			*buf = MyI2C_ReceiveByte();
			MyI2C_SendAck(0);
			break;
		}
		else
		{
			*buf = MyI2C_ReceiveByte();
			MyI2C_SendAck(1);
		}
		len--;
		buf++;
	}
	MyI2C_Stop();
	
	return 0;
}
