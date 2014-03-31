////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Draw and setup Collisions for objects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "collision.h"
#include "globals.h"
#include "VectorMath.h"

#include <cmath>

unsigned int uiMap1,uiMap1Wall;

void LoadMap(){
		uiMap1 = CreateSprite( "./images/maps/Map1.png", 5347, 3840, true );
		uiMap1Wall = CreateSprite( "./images/maps/Map1_Walls.png", 5347, 3840, true );
}
//MAPS
int CheckMapOLD(float x,float y,float px, float py,int offset){
//////Collision with each wall
	int t = 0;
////draw box around instance
if (bDebug == true){
	DrawLine(px-1,py+1,px+1,py+1);
	DrawLine(px-1,py-1,px+1,py-1);
	DrawLine(px+1,py-1,px+1,py+1);
	DrawLine(px-1,py-1,px-1,py+1);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TOP
    //t = CheckBox(x-128-16 , y-128+16, x+128+16, y+128-16,px,py); if (t!=0){return t;}//this is a generic box in the center of the "map" used for testing.
//outside map
    t = CheckBox(x-(iMapWidth*0.5)-160 , y-(iMapHeight*0.5)-160 , x-(iMapWidth*0.5)+16  , y+(iMapHeight*0.5)+160 ,px,py); if (t!=0){return t;}
    t = CheckBox(x+(iMapWidth*0.5)-16  , y-(iMapHeight*0.5)-160 , x+(iMapWidth*0.5)+160 , y+(iMapHeight*0.5)+160 ,px,py); if (t!=0){return t;}
    t = CheckBox(x-(iMapWidth*0.5)-160 , y-(iMapHeight*0.5)-160 , x+(iMapWidth*0.5)+160 , y-(iMapHeight*0.5)+16  ,px,py); if (t!=0){return t;}
    t = CheckBox(x-(iMapWidth*0.5)-160 , y+(iMapHeight*0.5)-16  , x+(iMapWidth*0.5)+160 , y+(iMapHeight*0.5)+160,px,py); if (t!=0){return t;}
//top left stairs
	t = CheckBox(x+128-offset , y-640-offset, x+256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y-768-offset, x+256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y-768-offset, x+640+offset, y-768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y-768-offset, x+640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y-512-offset, x+768+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y-640-offset, x+640+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y-640-offset, x+384+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+128-offset , y-512-offset, x+384+offset, y-512+offset,px,py); if (t!=0){return t;}
//top left kitchen
	t = CheckBox(x+896 -offset, y-512-offset, x+1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset, y-896-offset, x+1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+768 -offset, y-640-offset, x+1024+offset, y-640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y-896-offset, x+1024+offset, y-896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y-768-offset, x+768 +offset, y-640+offset,px,py); if (t!=0){return t;}
//top room
	//left
	t = CheckBox(x+256-offset, y-1024-offset, x+768+offset, y-1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+256-offset, y-1024-offset, x+256+offset, y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset, y-1280-offset, x+256+offset, y-1160+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-128-offset , y-896 -offset,x+128+offset, y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-1280-offset,x+256+offset, y-1280+offset,px,py); if (t!=0){return t;}
	//right
	t = CheckBox(x-768-offset , y-1024-offset,x-256+offset , y-1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-256-offset , y-1024-offset,x-256+offset , y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-1280-offset,x-256+offset , y-1160+offset,px,py); if (t!=0){return t;}
//top right stairs
	t = CheckBox(x-256-offset , y-640-offset, x-128+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-768-offset, x-256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-768-offset, x-256+offset, y-768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-768-offset, x-640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-768-offset , y-512-offset, x-640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-640-offset, x-384+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset , y-640-offset, x-384+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset , y-512-offset, x-128+offset, y-512+offset,px,py); if (t!=0){return t;}
 //top right kitchen				   
	t = CheckBox(x-1024-offset, y-512-offset, x-896 +offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y-896-offset, x-1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y-640-offset, x-768 +offset, y-640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-1024-offset, y-896-offset, x-768 +offset, y-896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-768 -offset, y-768-offset, x-768 +offset, y-640+offset,px,py); if (t!=0){return t;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MIDDLE
//middle left room
	//top
	t = CheckBox(x-1024-offset , y-256-offset, x-1024+offset, y-128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y-256-offset, x-1024+offset, y-256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1408-offset , y-128-offset, x-1152+offset, y-128+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-1152-offset , y-128-offset, x-1152+offset, y+128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y-256-offset, x-1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	//bottom
	t = CheckBox(x-1024-offset , y+128-offset, x-1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y+256-offset, x-1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1408-offset , y+128-offset, x-1152+offset, y+128+offset,px,py); if (t!=0){return t;}
//middle right room
	//top
	t = CheckBox(x+1024-offset , y-256-offset, x+1024+offset, y-128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset , y-256-offset, x+1664+offset, y-256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1152-offset , y-128-offset, x+1408+offset, y-128+offset,px,py); if (t!=0){return t;}
	//middle	  						
	t = CheckBox(x+1152-offset , y-128-offset, x+1152+offset, y+128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1664-offset , y-256-offset, x+1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	//bottom	  						
	t = CheckBox(x+1024-offset , y+128-offset, x+1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset , y+256-offset, x+1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1152-offset , y+128-offset, x+1408+offset, y+128+offset,px,py); if (t!=0){return t;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////BOTTOM
//Bottom left stairs
	t = CheckBox(x+128-offset , y+640-offset, x+256+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y+640-offset, x+256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y+768-offset, x+640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y+512-offset, x+640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y+512-offset, x+768+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y+640-offset, x+640+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y+512-offset, x+384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+128-offset , y+512-offset, x+384+offset, y+512+offset,px,py); if (t!=0){return t;}
//Bottom left kitchen
	t = CheckBox(x+896 -offset, y+512-offset, x+1024+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset, y+512-offset, x+1024+offset, y+896+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+768 -offset, y+640-offset, x+1024+offset, y+640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y+896-offset, x+1024+offset, y+896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y+640-offset, x+768 +offset, y+768+offset,px,py); if (t!=0){return t;}
//Bottom room
	//left
	t = CheckBox(x+256-offset, y+1024-offset, x+768+offset, y+1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+256-offset, y+896 -offset, x+256+offset, y+1024+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset, y+1160-offset, x+256+offset, y+1280+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-128-offset, y+896 -offset, x+128+offset, y+896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+1280-offset, x+256+offset, y+1280+offset,px,py); if (t!=0){return t;}
	//right
	t = CheckBox(x-768-offset, y+1024-offset, x-256+offset, y+1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-256-offset, y+896 -offset, x-256+offset, y+1024+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+1160-offset, x-256+offset, y+1280+offset,px,py); if (t!=0){return t;}
//Bottom right stairs		 
	t = CheckBox(x-256-offset, y+640-offset, x-128+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+640-offset, x-256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+768-offset, x-256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+512-offset, x-640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-768-offset, y+512-offset, x-640+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+640-offset, x-384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset, y+512-offset, x-384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset, y+512-offset, x-128+offset, y+512+offset,px,py); if (t!=0){return t;}
 //Bottom right kitchen				   
	t = CheckBox(x-1024-offset, y+512-offset, x-896 +offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y+512-offset, x-1024+offset, y+896+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y+640-offset, x-768 +offset, y+640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-1024-offset, y+896-offset, x-768 +offset, y+896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-768- offset, y+640-offset, x-768 +offset, y+768+offset,px,py); if (t!=0){return t;}
//repeat above for each collision object in the map, will be alot!
	return 0;
}
int CheckMap(float x,float y,float px, float py,float pxn, float pyn,int offset){
//////Collision with each wall
	int t = 0;
////draw box around instance
if (bDebug == true){
	DrawLine(px-1,py+1,px+1,py+1);
	DrawLine(px-1,py-1,px+1,py-1);
	DrawLine(px+1,py-1,px+1,py+1);
	DrawLine(px-1,py-1,px-1,py+1);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TOP
    //t = CheckBox(x-128-16 , y-128+16, x+128+16, y+128-16,px,py); if (t!=0){return t;}//this is a generic box in the center of the "map" used for testing.
//outside map
    t = CheckBox(x-(iMapWidth*0.5)-160 , y-(iMapHeight*0.5)-160 , x-(iMapWidth*0.5)+16  , y+(iMapHeight*0.5)+160 ,px,py); if (t!=0){return t;}
    t = CheckBox(x+(iMapWidth*0.5)-16  , y-(iMapHeight*0.5)-160 , x+(iMapWidth*0.5)+160 , y+(iMapHeight*0.5)+160 ,px,py); if (t!=0){return t;}
    t = CheckBox(x-(iMapWidth*0.5)-160 , y-(iMapHeight*0.5)-160 , x+(iMapWidth*0.5)+160 , y-(iMapHeight*0.5)+16  ,px,py); if (t!=0){return t;}
    t = CheckBox(x-(iMapWidth*0.5)-160 , y+(iMapHeight*0.5)-16  , x+(iMapWidth*0.5)+160 , y+(iMapHeight*0.5)+160,px,py); if (t!=0){return t;}
//top left stairs
	t = CheckBox(x+128-offset , y-640-offset, x+256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y-768-offset, x+256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y-768-offset, x+640+offset, y-768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y-768-offset, x+640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y-512-offset, x+768+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y-640-offset, x+640+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y-640-offset, x+384+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+128-offset , y-512-offset, x+384+offset, y-512+offset,px,py); if (t!=0){return t;}
//top left kitchen
	t = CheckBox(x+896 -offset, y-512-offset, x+1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset, y-896-offset, x+1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+768 -offset, y-640-offset, x+1024+offset, y-640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y-896-offset, x+1024+offset, y-896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y-768-offset, x+768 +offset, y-640+offset,px,py); if (t!=0){return t;}
//top room
	//left
	t = CheckBox(x+256-offset, y-1024-offset, x+768+offset, y-1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+256-offset, y-1024-offset, x+256+offset, y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset, y-1280-offset, x+256+offset, y-1160+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-128-offset , y-896 -offset,x+128+offset, y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-1280-offset,x+256+offset, y-1280+offset,px,py); if (t!=0){return t;}
	//right
	t = CheckBox(x-768-offset , y-1024-offset,x-256+offset , y-1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-256-offset , y-1024-offset,x-256+offset , y-896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-1280-offset,x-256+offset , y-1160+offset,px,py); if (t!=0){return t;}
//top right stairs
	t = CheckBox(x-256-offset , y-640-offset, x-128+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset , y-768-offset, x-256+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-768-offset, x-256+offset, y-768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-768-offset, x-640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-768-offset , y-512-offset, x-640+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset , y-640-offset, x-384+offset, y-640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset , y-640-offset, x-384+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset , y-512-offset, x-128+offset, y-512+offset,px,py); if (t!=0){return t;}
 //top right kitchen				   
	t = CheckBox(x-1024-offset, y-512-offset, x-896 +offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y-896-offset, x-1024+offset, y-512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y-640-offset, x-768 +offset, y-640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-1024-offset, y-896-offset, x-768 +offset, y-896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-768 -offset, y-768-offset, x-768 +offset, y-640+offset,px,py); if (t!=0){return t;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MIDDLE
//middle left room
	//top
	t = CheckBox(x-1024-offset , y-256-offset, x-1024+offset, y-128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y-256-offset, x-1024+offset, y-256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1408-offset , y-128-offset, x-1152+offset, y-128+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-1152-offset , y-128-offset, x-1152+offset, y+128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y-256-offset, x-1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	//bottom
	t = CheckBox(x-1024-offset , y+128-offset, x-1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1664-offset , y+256-offset, x-1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1408-offset , y+128-offset, x-1152+offset, y+128+offset,px,py); if (t!=0){return t;}
//middle right room
	//top
	t = CheckBox(x+1024-offset , y-256-offset, x+1024+offset, y-128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset , y-256-offset, x+1664+offset, y-256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1152-offset , y-128-offset, x+1408+offset, y-128+offset,px,py); if (t!=0){return t;}
	//middle	  						
	t = CheckBox(x+1152-offset , y-128-offset, x+1152+offset, y+128+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1664-offset , y-256-offset, x+1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	//bottom	  						
	t = CheckBox(x+1024-offset , y+128-offset, x+1024+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset , y+256-offset, x+1664+offset, y+256+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1152-offset , y+128-offset, x+1408+offset, y+128+offset,px,py); if (t!=0){return t;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////BOTTOM
//Bottom left stairs
	t = CheckBox(x+128-offset , y+640-offset, x+256+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y+640-offset, x+256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset , y+768-offset, x+640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y+512-offset, x+640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+640-offset , y+512-offset, x+768+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y+640-offset, x+640+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+384-offset , y+512-offset, x+384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+128-offset , y+512-offset, x+384+offset, y+512+offset,px,py); if (t!=0){return t;}
//Bottom left kitchen
	t = CheckBox(x+896 -offset, y+512-offset, x+1024+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+1024-offset, y+512-offset, x+1024+offset, y+896+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+768 -offset, y+640-offset, x+1024+offset, y+640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y+896-offset, x+1024+offset, y+896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+768 -offset, y+640-offset, x+768 +offset, y+768+offset,px,py); if (t!=0){return t;}
//Bottom room
	//left
	t = CheckBox(x+256-offset, y+1024-offset, x+768+offset, y+1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x+256-offset, y+896 -offset, x+256+offset, y+1024+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x+256-offset, y+1160-offset, x+256+offset, y+1280+offset,px,py); if (t!=0){return t;}
	//middle
	t = CheckBox(x-128-offset, y+896 -offset, x+128+offset, y+896 +offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+1280-offset, x+256+offset, y+1280+offset,px,py); if (t!=0){return t;}
	//right
	t = CheckBox(x-768-offset, y+1024-offset, x-256+offset, y+1024+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-256-offset, y+896 -offset, x-256+offset, y+1024+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+1160-offset, x-256+offset, y+1280+offset,px,py); if (t!=0){return t;}
//Bottom right stairs		 
	t = CheckBox(x-256-offset, y+640-offset, x-128+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-256-offset, y+640-offset, x-256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+768-offset, x-256+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+512-offset, x-640+offset, y+768+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-768-offset, y+512-offset, x-640+offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-640-offset, y+640-offset, x-384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset, y+512-offset, x-384+offset, y+640+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-384-offset, y+512-offset, x-128+offset, y+512+offset,px,py); if (t!=0){return t;}
 //Bottom right kitchen				   
	t = CheckBox(x-1024-offset, y+512-offset, x-896 +offset, y+512+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y+512-offset, x-1024+offset, y+896+offset,px,py); if (t!=0){return t;}
	t = CheckBox(x-1024-offset, y+640-offset, x-768 +offset, y+640+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-1024-offset, y+896-offset, x-768 +offset, y+896+offset,px,py); if (t!=0){return t;} 
	t = CheckBox(x-768- offset, y+640-offset, x-768 +offset, y+768+offset,px,py); if (t!=0){return t;}
//repeat above for each collision object in the map, will be alot!
	return 0;
}
bool CheckMapLines(float x,float y,float px, float py){
//////Collision with each wall
	int t = false;
//top left stairs
	t = CheckLine(x+128,y-640,x+256,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y-768,x+256,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y-768,x+640,y-768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+640,y-768,x+640,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+640,y-512,x+768,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+384,y-640,x+640,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+384,y-640,x+384,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+128,y-512,x+384,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//top left kitchen
	t = CheckLine(x+896 ,y-512,x+1024,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1024,y-896,x+1024,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y-640,x+1024,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y-896,x+1024,y-896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y-768,x+768 ,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//top room
	//left
	t = CheckLine(x+256,y-1024,x+768,y-1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y-1024,x+256,y-896 ,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y-1280,x+256,y-1160,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	//middle
	t = CheckLine(x-128,y-896 ,x+128,y-896 ,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y-1280,x+256,y-1280,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	//right
	t = CheckLine(x-768,y-1024,x-256,y-1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y-1024,x-256,y-896 ,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y-1280,x-256,y-1160,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//top right stairs 
	t = CheckLine(x-256,y-640,x-128,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y-768,x-256,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y-768,x-256,y-768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y-768,x-640,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-768,y-512,x-640,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y-640,x-384,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-384,y-640,x-384,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-384,y-512,x-128,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
 //top right kitchen
	t = CheckLine(x-1024,y-512,x-896 ,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y-896,x-1024,y-512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y-640,x-768 ,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y-896,x-768 ,y-896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-768 ,y-768,x-768 ,y-640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MIDDLE
//middle left room
	//top
	t = CheckLine(x-1024,y-256,x-1024,y-128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1664,y-256,x-1024,y-256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1408,y-128,x-1152,y-128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//middle
	t = CheckLine(x-1152,y-128,x-1152,y+128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1664,y-256,x-1664,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//bottom
	t = CheckLine(x-1024,y+128,x-1024,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1664,y+256,x-1024,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1408,y+128,x-1152,y+128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//middle right room
//top
	t = CheckLine(x+1024,y-256,x+1024,y-128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1024,y-256,x+1664,y-256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1152,y-128,x+1408,y-128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//middle		   		  	
	t = CheckLine(x+1152,y-128,x+1152,y+128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1664,y-256,x+1664,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//bottom		   		  	
	t = CheckLine(x+1024,y+128,x+1024,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1024,y+256,x+1664,y+256,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1152,y+128,x+1408,y+128,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////BOTTOM
//Bottom left stairs
	t = CheckLine(x+128,y+640,x+256,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y+640,x+256,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y+768,x+640,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+640,y+512,x+640,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+640,y+512,x+768,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+384,y+640,x+640,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+384,y+512,x+384,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+128,y+512,x+384,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//Bottom left kitchen
	t = CheckLine(x+896 ,y+512,x+1024,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+1024,y+512,x+1024,y+896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y+640,x+1024,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y+896,x+1024,y+896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+768 ,y+640,x+768 ,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//Bottom room
//left
	t = CheckLine(x+256,y+1024,x+768,y+1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y+896 ,x+256,y+1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x+256,y+1160,x+256,y+1280,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//middle
	t = CheckLine(x-128,y+896 ,x+128,y+896 ,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y+1280,x+256,y+1280,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//right
	t = CheckLine(x-768,y+1024,x-256,y+1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y+896 ,x-256,y+1024,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y+1160,x-256,y+1280,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
//Bottom right stairs
	t = CheckLine(x-256,y+640,x-128,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-256,y+640,x-256,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y+768,x-256,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y+512,x-640,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-768,y+512,x-640,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-640,y+640,x-384,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-384,y+512,x-384,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-384,y+512,x-128,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
 //Bottom right kitchen	
	t = CheckLine(x-1024,y+512,x-896 ,y+512,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y+512,x-1024,y+896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y+640,x-768 ,y+640,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-1024,y+896,x-768 ,y+896,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	t = CheckLine(x-768 ,y+640,x-768 ,y+768,px,py,iScreenWidthHalf,iScreenHeightHalf); if (t==true){return true;}
	return false;
}
void CheckNodes(float x,float y, float px, float py,sfPosition &pos){
////Setup temp vars, t(testlength), l(length) ,xx(current closest x) ,yy(current closest y)
	float tl,tlp,l,lp,xx,yy,pxx,pyy,zxx,zyy;
	tl = tlp = l = lp = xx = yy = pxx = pyy = zxx = zyy = 9999999;
//////////////////////////////////////////////////////////////////////////////////Start LengthChecks
//top
	xx = x+128; yy = y-576;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-128; yy = y-576;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
																																																									   
	xx = x+192; yy = y-896;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-192; yy = y-896;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+256; yy = y-1088; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-256; yy = y-1088; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
						
	xx = x+768; yy = y-832;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-768; yy = y-832;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+768; yy = y-960;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-768; yy = y-960;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+832; yy = y-512;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-832; yy = y-512;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
//middle					 
	xx = x+1088; yy = y-128; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-1088; yy = y-128; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							 
	xx = x+1408; yy = y;     l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-1408; yy = y;     l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+1088; yy = y+128; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-1088; yy = y+128; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
//Bottom					
	xx = x+128; yy = y+576;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-128; yy = y+576;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							 
	xx = x+192; yy = y+896;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-192; yy = y+896;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+256; yy = y+1088; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-256; yy = y+1088; l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
						
	xx = x+768; yy = y+832;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-768; yy = y+832;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							
	xx = x+768; yy = y+960;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-768; yy = y+960;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
							 
	xx = x+832; yy = y+512;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
	xx = x-832; yy = y+512;  l=abs(Length(px-xx,py-yy)); if (tl>l){tl=l;pos.x=xx;pos.y=yy;} if (bDebug==true){DrawLine(px,py,xx,yy); DrawLine(iScreenWidthHalf,iScreenHeightHalf,xx,yy);}
}