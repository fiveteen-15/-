#include "stm32f10x.h"                  // Device header
#include <math.h>
#include <stdio.h>

struct Angle {
	double roll;
	double pitch;
	double yaw;
} angle;
extern double r;
extern double p;
extern double y;

void AccCal(int16_t *AccX, int16_t *AccY, int16_t *AccZ)
{
	double ay = (*AccY)/32678.0*16.0*9.8;
	double ax = (*AccX)/32678.0*16.0*9.8;
	double az = (*AccZ)/32678.0*16.0*9.8;

	angle.roll = atan((double)(ay/az))/0.0174f;
	angle.pitch = (0 - atan((double)(ax/(sqrt(ay*ay+az*az)))))/0.0174f;
//	angle.roll = acos((ax + 0) / 16384.0);
//	angle.pitch = acos((ay + 0) / 16384.0);
//	angle.yaw = acos((az + 2234) / 16384.0);
//	
//	angle.roll *= 57.29577;
//	angle.pitch *= 57.29577;
//	angle.yaw *= 57.29577;
//	
	
	return;
}

void GyroCal(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	double gx = (*GyroX)/32768.0*2000.0;
	double gy = (*GyroY)/32768.0*2000.0;
	double gz = (*GyroZ)/32768.0*2000.0;
	
	
	r += (gx + gy*sin(p)*sin(r)/cos(p) + gz*sin(p)*cos(r)/cos(p))*0.1;
	p += (gy*cos(r) - gz*sin(r))*0.1;
//	y += (gy*sin(r)/cos(p) + gz*cos(r)/cos(p))*0.1;
//	
//	r += gx * 0.1;
//	p += gy * 0.1;
//	y += gz * 0.1;
	gz = gz * 0.1;
	if((gz > 1.0f) || (gz < -1.0f))
		y += gz;
	
	return;
}

void Calculate(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	AccCal(AccX, AccY, AccZ);
	GyroCal(GyroX, GyroY, GyroZ);
	
	r = r + (angle.roll - r)*0.4;
	p = p + (angle.pitch - p)*0.4;
	y = y;
	
//	r = angle.roll;
//	p = angle.pitch;
//	y = y;
//	
	
	return;
	
}
