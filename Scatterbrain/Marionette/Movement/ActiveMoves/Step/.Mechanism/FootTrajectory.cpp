#include "../AM_Step.h"

float FAM_Step::FootTrajectory(const float X)
{
	return -pow(X * 2 - 1, 2) + 1; 
}

float FAM_Step::FootTrajectoryInverse(const float Y)
{
	return sqrt(Y) / 2;
}