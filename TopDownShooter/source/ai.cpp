////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Creates updates and draws NPC's
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AI.h"
#include "AIE.h"
#include "VectorMath.h"
#include "map1.h"
#include "globals.h"
#include "collision.h"
#include "Pickups.h"
#include "player.h"
#include "particles.h"

#include <vector>
#include <time.h>
#include <iostream>

//enemy sprite index
unsigned int uiEnemy;
//amount of enemies at the start of the game
unsigned int iEnemies = 3;

void LoadInstance(){
	uiEnemy = CreateSprite("./images/instances/zombie_topdown.png", 64, 64, true );
}
instance CreateInstance(float x, float y, float dir,float speed,int health,float px, float py){
//create temp instance
	instance ins;
//setup vars
	ins.Vec.fDir = dir;
	ins.Pos.x  = 0.0f;
	ins.Pos.y  = 0.0f;
	ins.tPos.x = x;
	ins.tPos.y = y;
	ins.Vec.Pos.x = (px - ins.Pos.x);
	ins.Vec.Pos.y = (py - ins.Pos.y);
	ins.Vec.fSpeed = speed;
	ins.Tex.uiSprite = uiEnemy; 
	ins.iHealth = health;
	ins.Tex.fIndexOffset = 0.125f;
	ins.Tex.fIndex  = 0.0f;
	ins.Tex.fYIndexOffset = 1.0f/8.0f;
	ins.Tex.fYIndex = rand()%8*ins.Tex.fYIndexOffset;
	ins.iWall = 0;
	return ins;
}

void DrawNPC(std::vector<instance> vin){
	//draws the npc	
	for each (instance ins in vin){
		if (bDebug==true){
			DrawLine(iScreenWidthHalf,iScreenHeightHalf,(int)ins.Pos.x,(int)ins.Pos.y,SColour(255,0,0,155));
		}
        //update the instances texture
		SetSpriteUVCoordinates(ins.Tex.uiSprite,ins.Tex.fIndex,ins.Tex.fYIndex,ins.Tex.fIndex+ins.Tex.fIndexOffset,ins.Tex.fYIndex+ins.Tex.fYIndexOffset);
		DrawImage(ins.Tex.uiSprite,ins.Pos.x,ins.Pos.y,(int)ins.Vec.fDir);
        //Draw Health
		DrawLine((int)(ins.Pos.x-16-((ins.iHealth*0.0625)*0.5)),(int)ins.Pos.y-16,(int)(ins.Pos.x+(ins.iHealth*0.0625)),(int)ins.Pos.y-16,SColour(255,0,0,150),SColour(0,255,0,150));
	}
}
instance UpdateNPCxy(instance ins,sfPosition map,float px, float py,sfPosition world,float dt){
	/*  assignment 3 (start of better AI)
	sfPosition pos;
	pos.x = pos.y = 0;
	if (abs(Length(ins.Pos.x-iScreenWidthHalf,ins.Pos.y-iScreenHeightHalf))<320){
		if (CheckMapLines(map.x,map.y,ins.Pos.x,ins.Pos.y)==true){
			CheckNodes(map.x,map.y,ins.Pos.x,ins.Pos.y,pos);
			px=pos.x+(ins.Vec.Pos.x*32);
			py=pos.y+(ins.Vec.Pos.y*32);
		}
	}
	DrawLine(px,py,ins.Pos.x,ins.Pos.y,SColour(0,0,255,255));
	*/
	//get the vectors from player to npc
	ins.Vec.Pos.x = (px - ins.Pos.x);
	ins.Vec.Pos.y = (py - ins.Pos.y);
	Normalize(ins.Vec.Pos.x,ins.Vec.Pos.y);
	ins.Vec.fDir = 180.0f + atan2( ins.Vec.Pos.x, ins.Vec.Pos.y )* 180.0f / PI;
	int tmc = CheckMap(map.x,map.y,ins.Pos.x,ins.Pos.y,ins.Pos.x+ins.Vec.Pos.x,ins.Pos.y+ins.Vec.Pos.y,16);
	if (tmc==0){
		//setup the offset x/y
		ins.tPos.x += ins.Vec.Pos.x*ins.Vec.fSpeed*dt;
		ins.tPos.y += ins.Vec.Pos.y*ins.Vec.fSpeed*dt;
		//Check Walls
		//animate
		ins.Tex.fAniTimer+=dt;
	}
	//setup the npc's world x/y
	ins.Pos.x = map.x+ins.tPos.x;
	ins.Pos.y = map.y+ins.tPos.y;
	//reset animations
	if (ins.Tex.fIndex>=1.0f){
		ins.Tex.fIndex=0.0f;
	}
	if (ins.Tex.fAniTimer>0.175f){
		ins.Tex.fIndex+=ins.Tex.fIndexOffset;
		ins.Tex.fAniTimer=0.0f;
	}
	if (ins.Tex.fAniTimer<0.0f){
		ins.Tex.fAniTimer=0.0f;
	}
	//check if we are at the player
	int TempCheck = CheckBox(ins.Pos.x-16 , ins.Pos.y-16, ins.Pos.x+16, ins.Pos.y+16,iScreenWidthHalf,iScreenHeightHalf);
	if (TempCheck!=0){
		if (!bGodMode){iPlayerHealth -= 1;}
		vParticles.push_back(CreateParticles(uiBlood,map,ins.Pos.x+rand()%6-3,ins.Pos.y+rand()%6-3,rand()%80,rand()%50,0,360));//create Particle
	}
	return ins;
}
void UpdateNPC(std::vector<instance> &vins,sfPosition map,float px, float py,sfPosition world,float dt){
	//update all npc's for the group
	std::vector<instance>::iterator i = vins.begin();
	while (i!=vins.end()) {
		instance ins = *i;
		*i = UpdateNPCxy(ins,map,px,py,world,dt);
		i++;
	}
}

instance TakeHealth(instance ins,int damage,bool &dead){
	ins.iHealth -= damage;
	if (ins.iHealth<1){
			iPickups+=rand()%2;
			iKills +=rand()%2;
			dead = true;
	}
	return ins;
}
void CheckNPC(std::vector<instance> &vins,float x, float y,int damage,bool &check){
	//update all npc's for the group
	std::vector<instance>::iterator i = vins.begin();
	bool dead = false;
	while (i!=vins.end()) {
		dead = false;
        instance ins = *i;
		//debug
        if (bDebug == true){
			DrawInt((int)ins.Pos.x,0, iScreenHeight-96);
            DrawInt((int)ins.Pos.y,0, iScreenHeight-128);
        }
		//Collisions
		if (CheckBox(ins.Pos.x-16 , ins.Pos.y-16, ins.Pos.x+16, ins.Pos.y+16,x,y)){
			*i = TakeHealth(ins,damage,dead);
			iHits ++;
			check = true;
		}if (dead == true){
			i=vins.erase(i);
		} else {
			i++; 
		}
    }
}

void DestroyInstance(){
	DestroySprite(uiEnemy);
}

/* assignment 3
check to player
if length < roomdistance
	if wall inbetween
		check closest door to both player and self
		move to door +offset(1.5ish)(to be on the other side of the door)
	else
		move to player
else
	find a point inside set length(rand()%360,rand()%length)
	move towards it
	check player length = true
		rush to player
	else
		keep random movement
repeat
*/