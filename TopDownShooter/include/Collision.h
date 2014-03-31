/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//																			Brief:		Sets up all Collision functions(needs work)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "globals.h"

#ifndef Col
#define Col

int CheckBox(const float x1,const float y1,const float x2,const float y2,float px, float py);
int CheckBoxLine(const float x1,const float y1,const float x2,const float y2,float px, float py,float pxn, float pyn);
bool CheckLine(float p0_x, float p0_y, float p1_x, float p1_y,float p2_x, float p2_y, float p3_x, float p3_y);
#endif