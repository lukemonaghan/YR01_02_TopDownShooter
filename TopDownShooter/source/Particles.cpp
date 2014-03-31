////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Creates Draws and updates particles
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <math.h>
#include <iostream>

#include "AIE.h"
#include "VectorMath.h"
#include "globals.h"
#include "map1.h"
#include "ai.h"
#include "weapon.h"

unsigned int uiParticlesAmount = 0;
unsigned int uiBlood,uiSpark,uiSmoke,uiExplosion;

std::vector <particle> vParticles;

void LoadParticles(){
	uiBlood     = CreateSprite("./images/particles/Blood.png"    ,8 ,8 ,true,SColour(255,255,255,155));
	std::cout << "uiBlood" << uiBlood << std::endl;
	uiSpark     = CreateSprite("./images/particles/spark.png"    ,2 ,2 ,true,SColour(255,255,255,155));
	std::cout << "uiSpark" << uiSpark << std::endl;
	uiSmoke     = CreateSprite("./images/particles/Smoke.png"    ,8 ,8 ,true,SColour(255,255,255,155));
	std::cout << "uiSmoke" << uiSmoke << std::endl;
	uiExplosion = CreateSprite("./images/particles/Explosion.png",16,16,true,SColour(255,255,255,155));
	std::cout << "uiExplosion" << uiExplosion << std::endl;
	
}
//vParticles.push_back(CreateParticles(uiBlood,iScreenWidthHalf,iScreenHeightHalf,Length(vx,vy),Length(vx,vy)*0.2,iDirection,50));
particle CreateParticles(unsigned int spr,sfPosition map, float x, float y,float len, float speed,float dir,int spread){
	particle part;
	//length to destroy
	part.Vec.fLength = len;
	//spread of the particles
	part.Vec.fSpread = (float)(rand()%spread-(spread*0.5));
	//speed to move
	part.Vec.fSpeed = speed;
	//direction of texture
	part.Vec.fDir = (float)(rand()%360);
	//direction of particles
	float radians = (dir-part.Vec.fSpread) * (PI / 180.0f);
	part.Vec.Pos.x = part.Vec.fSpeed*cos(radians);
	part.Vec.Pos.y = part.Vec.fSpeed*sin(radians);
	//Normalize(part.Vec.Pos.x,part.Vec.Pos.y);
	//start
	part.Pos.x = x+(part.Vec.Pos.x/part.Vec.fLength*2);
	part.Pos.y = y+(part.Vec.Pos.y/part.Vec.fLength*2);
	//origin
	part.oPos.x = part.Pos.x;
	part.oPos.y = part.Pos.y;
	//tempx
	part.tPos.x = -map.x+part.oPos.x;
	part.tPos.y = -map.y+part.oPos.y;
	//image to draw
	part.Tex.uiSprite = spr;
	part.Tex.fIndex = rand()%4*0.25;
	part.timer = 0;
	SetSpriteUVCoordinates(part.Tex.uiSprite,part.Tex.fIndex,0,part.Tex.fIndex+0.25,1);
 return part;
}

particle UpdateParticle(particle par,sfPosition map,float dt){
	par.timer++;
	//setup the offset x/y
	par.tPos.x += par.Vec.Pos.x*dt;
	par.tPos.y += par.Vec.Pos.y*dt;
	//setup the npc's world x/y
	par.Pos.x = map.x+par.tPos.x;
	par.Pos.y = map.y+par.tPos.y;
	SetSpriteUVCoordinates(par.Tex.uiSprite,par.Tex.fIndex,0,par.Tex.fIndex+0.25,1);
	DrawImage(par.Tex.uiSprite,par.Pos.x,par.Pos.y,par.Vec.fDir);
	if (bDebug == true){
		DrawLine(par.Pos.x,par.Pos.y,par.oPos.x,par.oPos.y,SColour(255,255,255,150));
	}
	return par;
}
std::vector<particle> UpdateParticles(std::vector<particle> par,std::vector<instance> &vnpc,sfPosition map,float dt){
	std::vector<particle>::iterator b = par.begin();
	while (b!=par.end()) {
		particle bpar = *b;
		bool ts = false;
		//setup the bullet direction
		int dir = atan2( ((bpar.Pos.y+map.y) - (bpar.Pos.y+map.y+bpar.Vec.Pos.y)), ((bpar.Pos.x+map.x) - (bpar.Pos.x+map.x+bpar.Vec.Pos.x) ) )* 180.0f / PI;//direction
		//(hardcoded switch below... really bad thing to do..)checks if the particles collide with the npc's
		switch (bpar.Tex.uiSprite){
		case 32://uiSpark 
			CheckNPC(vnpc,bpar.Pos.x, bpar.Pos.y,5,ts);
			break;
		case 34://uiExplosion
			CheckNPC(vnpc,bpar.Pos.x, bpar.Pos.y,400*iDamageOffset,ts);
			break;
		}
		//check the map
		if (CheckMap(map.x,map.y,bpar.Pos.x,bpar.Pos.y,0,0,6)!=0){
			b=par.erase(b);
		//check if the collision NPC-PARTICLE was true
		}else if (ts==true){
			//CreateParticles
			for (int i = 0; i<30;i++){
			vParticles.push_back(CreateParticles(uiBlood,map,bpar.Pos.x,bpar.Pos.y,rand()%50,50+rand()%50,dir,90));//create Particle
			i++;
			}
			b=par.erase(b);
		//else update the next zombie
		}else if (bpar.timer>1000){
			b=par.erase(b);
		}
		//check if its length is above its set length
		else if (Length(bpar.oPos.x - bpar.Pos.x,bpar.oPos.y - bpar.Pos.y)>bpar.Vec.fLength){
			b=par.erase(b);
			uiParticlesAmount--;
		//else update it, and goto the next one
		} else {
			*b = UpdateParticle(bpar,map,dt);
			b++;
		}
	}
	return par;
}

void DestroyParticle(){
	DestroySprite(uiBlood);
	DestroySprite(uiSpark);
	DestroySprite(uiSmoke);
	DestroySprite(uiExplosion);
}