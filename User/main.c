#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Servo.h"
#include "EulerAngle.h"
#include "StableAngle.h"

float Angle;
//uint8_t KeyNum;
uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;
unsigned long ms_Num;

double r = 0;
double p = 0;
double y = 0;

void stimulate(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
}

void signal(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}


int main ()
{
	stimulate();
	signal();
	
	
	OLED_Init();
	Servo_Init();
	MPU6050_Init();

//	char s_pitch[10];
//	char s_roll[10];
//	char s_yaw[10];
	
//	int roll = (int)r;
	int roll = (int)r;
	int pitch = (int)p;
	int yaw = (int)y;
	int tem_roll = roll;
	int tem_yaw = yaw;
	Servo_SetAngle2(0);
	Servo_SetAngle1(90);
//	Servo_SetAngle1(0);
	Delay_ms(1000);
	
//	int flag = 0;
	
	
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		Calculate(&AX, &AY, &AZ, &GX, &GY, &GZ);
		
//		roll = r;
//		pitch = p;
//		yaw = y;
//		
//		OLED_ShowSignedNum(1, 1, AX, 5);
//		OLED_ShowSignedNum(2, 1, AY, 5);
//		OLED_ShowSignedNum(3, 1, AZ, 5);
//		OLED_ShowSignedNum(1, 8, GX, 5);
//		OLED_ShowSignedNum(2, 8, GY, 5);
//		OLED_ShowSignedNum(4, 1, GZ, 5);
		
//		sprintf(s_pitch,"%.2f",p);
//		sprintf(s_roll,"%.2f",r);
//		sprintf(s_yaw,"%.2f",y);
//		
//		OLED_ShowString(1, 1, s_pitch);
//		OLED_ShowString(2, 1, s_roll);
//		OLED_ShowString(3, 1, s_yaw);


//		if((((int)r - roll > 3 || (int)r - roll < -3)) && ((int)r >= 0))
//		{
//			roll = (int)r;
//			Servo_SetAngle2(roll);
//		}
//		
////		if((((int)y - yaw > 3 || (int)y - yaw < -3)) && ((int)y >= 0) && ((int)y <= 180))
////		{
////			yaw = (int)y;
////			Servo_SetAngle1(yaw);
////		}
//		
//		if((((int)y - yaw > 3 || (int)y - yaw < -3)) && ((int)y >= -90) && ((int)y <= 90))
//		{
//			yaw = (int)y;
//			Servo_SetAngle1(90 - yaw);
//		}

//		int tem_roll = roll;
//		int tem_yaw = yaw;

//		CalculateAngle(r, p, &roll, &yaw);
//		
//		if((roll - tem_roll > 5 || roll - tem_roll < -5) && (roll >= 0) && (roll <= 180))
//		{
//			Servo_SetAngle2(roll);
//		}
//		
//		if((yaw - tem_yaw > 5 || yaw - tem_yaw < -5) && (yaw >= -90) && (yaw <= 90))
//		{
//			Servo_SetAngle1(yaw);
//		}
//		
//		OLED_ShowSignedNum(1, 1, pitch, 3);
//		OLED_ShowSignedNum(2, 1, yaw, 3);
//		
//		Delay_ms(100);



		CalculateAngle(r, p, &roll, &yaw);
		
		if((roll - tem_roll > 3 || roll - tem_roll < -3) && (roll >= 0) && (roll <= 180))
		{
			Servo_SetAngle2(roll);
			tem_roll = roll;
			OLED_ShowSignedNum(1, 1, roll, 3);
		}
		
		if((yaw - tem_yaw > 3 || yaw - tem_yaw < -3) && (yaw >= -90) && (yaw <= 90))
		{
			Servo_SetAngle1(90 - yaw);
			tem_yaw = yaw;
			OLED_ShowSignedNum(2, 1, yaw, 3);
		}
		
		Delay_ms(100);
	}
	
}
