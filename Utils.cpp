/*
 * Utils.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: emjohnson
 */

#include "Utils.h"

float FixAngle(float angle){
	if(angle < 0)
		return angle + 360;
	else if (angle > 360)
		return angle - 360;
	return angle;
}

float Clamp(float min, float max, float val){
	if(val < min){
		return min;
	} else if (val > max){
		return max;
	}
	return val;
}
