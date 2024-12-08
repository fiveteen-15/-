#include "stm32f10x.h"                  // Device header
#include <math.h>
#include <stdio.h>

void CalculateAngle(double row, double pitch, int *roll, int *yaw)
{
	double r = row*0.0174f;
	double p = pitch*0.0174f;
	double tem_p = atan(sqrt(sin(p)*sin(p)+sin(r)*sin(r))/(cos(p)*cos(r)))/0.0174f;
	double tem_y = -atan(sin(p)/sin(r))/0.0174f;
	
	*roll = (int)tem_p;
	*yaw = (int)tem_y;
	
	return;
	
}
