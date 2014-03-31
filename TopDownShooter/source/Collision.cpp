////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Calls for collision types
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "VectorMath.h"
#include "Collision.h"
#include "map1.h"
#include "globals.h"

#include <cmath>
int CheckBox(const float x1,const float y1,const float x2,const float y2,float px, float py){
////gets the middle of the box
	float mx = (x2 + x1)*0.5;
	float my = (y2 + y1)*0.5;
	float smx =abs((px - mx)) / (x2 - x1);
	float smy =abs((py - my)) / (y2 - y1);
////draws debug information
	if (bDebug == true){
		DrawLine(x1,y1,x2,y1,SColour(255,255,0,155));
		DrawLine(x1,y2,x2,y2,SColour(255,255,0,155));
		DrawLine(x1,y1,x1,y2,SColour(255,255,0,155));
		DrawLine(x2,y1,x2,y2,SColour(255,255,0,155));
    }
////Move the instance
	if (py > y1 && py < y2 && px > x1 && px < x2){
		//the following finds out what side of the wall you are hitting, and moves you correspondingly
		if (px > x1 && px < mx && LargerNum(smx,smy) == smx) {return 1;}//
		if 
			(px < x2 && px > mx && LargerNum(smx,smy) == smx) {return 2;}//
		if (py > y1 && py < my && LargerNum(smx,smy) == smy) {return 3;}//
		if (py < y2 && py > my && LargerNum(smx,smy) == smy) {return 4;}//
	}
////if no collisions have been hit, then return 0.
	return 0;
}

int CheckBoxLine(const float x1,const float y1,const float x2,const float y2,float px, float py,float pxn, float pyn){
////gets the middle of the box
	float mx = (x2 + x1)*0.5;
	float my = (y2 + y1)*0.5;
	float smx =abs((px - mx)) / (x2 - x1);
	float smy =abs((py - my)) / (y2 - y1);
////draws debug information
	if (bDebug == true){
		DrawLine(x1,y1,x2,y1,SColour(255,255,0,155));
		DrawLine(x1,y2,x2,y2,SColour(255,255,0,155));
		DrawLine(x1,y1,x1,y2,SColour(255,255,0,155));
		DrawLine(x2,y1,x2,y2,SColour(255,255,0,155));
    }
	if (CheckLine(x1,y1,x2,y1,px,py,px+pxn,py+pyn)) {return 1;}
	if (CheckLine(x1,y2,x2,y2,px,py,px+pxn,py+pyn)) {return 2;}
	if (CheckLine(x1,y1,x1,y2,px,py,px+pxn,py+pyn)) {return 3;}
	if (CheckLine(x2,y1,x2,y2,px,py,px+pxn,py+pyn)) {return 4;}
////if no collisions have been hit, then return 0
	return 0;
}

//http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
//Gavin Dec 28 '09 at 7:16
bool CheckLine(float p0_x, float p0_y, float p1_x, float p1_y,float p2_x, float p2_y, float p3_x, float p3_y){
	DrawLine(p2_x,p2_y,p3_x,p3_y);
    float s1_x, s1_y, s2_x, s2_y;

    s1_x = p1_x - p0_x;     
	s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     
	s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
        return true;
		
    }
    return false; // No collision
}