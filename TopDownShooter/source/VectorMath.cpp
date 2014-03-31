////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Calls for the different functions of vectors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include "VectorMath.h"
#include <math.h>

//magnitude of a vector
float Length(float x, float y){
	return sqrt(x*x + y*y);
}
//normalize a vector
void Normalize(float &x, float &y){
	float m = Length(x,y);
	x /= m;
	y /= m;
}
//rotate radians
void Rotate(float Angle,float &x, float &y){
	double xt = (x * cos(Angle)) - y * (sin(Angle));
	double yt = (y * cos(Angle)) + x * (sin(Angle));
	x = xt;
	y = yt;
}
//difference between two numbers
float Difference(float a, float b){
	return a-b;
}
//get the smaller number
float SmallerNum(float a,float b){
	if (a<b){return a;}
	if (a>b){return b;}
}
//get the larger number
float LargerNum(float a,float b){
	if (a>b){return a;}
	if (a<b){return b;}
}
//scale proportionally
void ScaleP(float &tx, float &ty,float x1,float y1,float x2,float y2){	
	tx /= Length(x1,x2);
	ty /= Length(y1,y2);
}
