////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Global File setup
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "globals.h"
#include "AIE.h"
#include <string>
#include <vector>

//all my variables
bool bRunning = true;
const int iScreenWidth = 1280;
const int iScreenHeight = 780;
const int iScreenWidthHalf = iScreenWidth*0.5;
const int iScreenHeightHalf = iScreenHeight*0.5;
const int iMapWidth = 5374;
const int iMapHeight = 3840;
const float PI = 3.14159f;

int iDirection = 1;
bool bGodMode = 0;
int bChkMap = 0;

float dImage=0.0f;
float dAnitimer = 0.0f;

char buffer[60];
bool usevariablemovement = true;
bool bDebug = false;
float iBladesRot = 0.0f;
int iKills = 0;
int iMiss = 0;
int iHits = 0;

GameState eCurrentState = GS_SPLASH_SCREEN;

void DrawInt(int i,int w, int h){
	_itoa_s (i,buffer,10);
	DrawString(buffer, w, h );
}

void DrawImage(unsigned int s,const float x,const float y,int d){
	RotateSprite(s,d);
	MoveSprite( s,x,y);
	DrawSprite( s );
}

void DrawImage(unsigned int s,const float x,const float y,int d,sfPosition map,int amount,int sep){
	for(int i = 0; i < amount; i++){
		DrawImage(s,map.x+(x*i*sep),map.y+(y*i*sep),d);
	}
}

int Choose(int a, int b, int c, int d){
	int temp = rand()%3+1;
	if (temp==0)return a;
	if (temp==1)return b;
	if (temp==2)return c;
	if (temp==3)return d;
	return 0;
}

