////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Calls for the bullet objects, Creation, updating, and drawing.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "Bullet.h"
#include "AIE.h"
#include "VectorMath.h"
#include "map1.h"
#include "ai.h"
#include "Particles.h"
#include "globals.h"
#include "weapon.h"

unsigned int uiBullet;
float dBulUVOffset = 0.09f;
std::vector <bullet> vBullets;

/*
Gun ID's
0  = sGunLMG   
1  = sGunAssult
2  = sGunLAW   
3  = sGunSniper
4  = sGunSMG   
5  = sGunRPG   
6  = sGunLMG2  
7  = sGunAKu   
8  = sGunLMG3  
9  = sGunAK    
10 = sGunRPG2  
*/

void LoadBullets(){
	uiBullet = CreateSprite("./images/instances/Bullets.png", 16, 16, true );
}
bullet CreateBullet(float px, float py,sfPosition map, float dir,float speed,float range,int parid,int damage,int spread){
	bullet bul;
	//id
	bul.iParID = parid;
	//range
	bul.dRange = range;
	//damage
	bul.iDamage = damage;
	//direction
	bul.iDir = dir;
	//bullet x/y offset
	bul.Pos.x = px;
	bul.Pos.y = py;
	//origin
	bul.oPos.x = px;
	bul.oPos.y = py;
	//tempx
	bul.tPos.x = -map.x+px;
	bul.tPos.y = -map.y+py;
	//speed
	bul.Vec.fSpeed = speed;
	//vectors
	float radians = (-90.0f-dir-(rand()%spread-(spread*0.5f))) * (PI / 180.0f);
	bul.Vec.Pos.x = bul.Vec.fSpeed*cos((float)radians);
	bul.Vec.Pos.y = bul.Vec.fSpeed*sin((float)radians);
	Normalize(bul.Vec.Pos.x, bul.Vec.Pos.y);
	//sprite
	bul.Tex.uiSprite = uiBullet;
	//	
	bul.Tex.fIndex = parid*dBulUVOffset;
	return bul;
}
void DrawBullet(std::vector<bullet> vbul){
	for each (bullet bul in vbul){
		if (bDebug==true){
			DrawInt((int)bul.Pos.x,(int)bul.Pos.x-32,  (int)bul.Pos.y);
            DrawInt((int)bul.Pos.y,(int)bul.Pos.x+32,  (int)bul.Pos.y);
			DrawInt((int)bul.oPos.x,(int)bul.Pos.x-32, (int)bul.Pos.y);
			DrawInt((int)bul.oPos.y,(int)bul.Pos.x+32, (int)bul.Pos.y);
			DrawLine((int)bul.oPos.x,(int)bul.oPos.y,(int)bul.Pos.x,(int)bul.Pos.y,SColour(0,0,255,255));
		}
		//update the sprite
		SetSpriteUVCoordinates(bul.Tex.uiSprite,bul.Tex.fIndex,0,bul.Tex.fIndex+dBulUVOffset,1);
		DrawImage(bul.Tex.uiSprite,bul.Pos.x,bul.Pos.y,bul.iDir);
	}
}
bullet UpdateBullet(bullet bul,sfPosition map,float dt){	
	//setup the offset x/y
	bul.tPos.x += bul.Vec.Pos.x*bul.Vec.fSpeed*dt;
	bul.tPos.y += bul.Vec.Pos.y*bul.Vec.fSpeed*dt;
	//setup the npc's world x/y
	bul.Pos.x = map.x+bul.tPos.x;
	bul.Pos.y = map.y+bul.tPos.y;
	float dir = -90 -atan2( ((bul.Pos.y+map.y) - iScreenHeightHalf), ((bul.Pos.x+map.x) - iScreenWidthHalf ) )* 180 / PI;//direction
	switch (bul.iParID){
	case 2:
	case 5:
	case 10:	
		//CreateParticles
		vParticles.push_back(CreateParticles(uiSmoke,map,bul.Pos.x-bul.Vec.Pos.x,bul.Pos.y-bul.Vec.Pos.y,12+rand()%12,25+rand()%50,dir,90));//create Particle
		break;
	}
return bul;
}
std::vector<bullet> UpdateBullets(std::vector<bullet> vbul,std::vector<instance> &vnpc,sfPosition map,float dt){
	std::vector<bullet>::iterator b = vbul.begin();
	while (b!=vbul.end()) {
		bullet bBul = *b;
		//set the npc size
        bool ts = false;
		//direction
		float dir =atan2( (bBul.Pos.y - (bBul.Pos.y+bBul.Vec.Pos.y)), (bBul.Pos.x - (bBul.Pos.x+bBul.Vec.Pos.x) ) )* 180 / PI;
		//check if we hit any
		CheckNPC(vnpc,bBul.Pos.x, bBul.Pos.y,bBul.iDamage,ts);
		//check the walls
        if (CheckMap(map.x,map.y,bBul.Pos.x,bBul.Pos.y,bBul.Pos.x+bBul.Vec.Pos.x,bBul.Pos.y+bBul.Vec.Pos.y,6)!=0){
			//CreateParticles
			switch (bBul.iParID){
				case 2:
				case 5:
				case 10:	
					for (int i = 1; i<320*iDamageOffset;i++){
						vParticles.push_back(CreateParticles(uiExplosion,map,bBul.Pos.x-bBul.Vec.Pos.x,bBul.Pos.y-bBul.Vec.Pos.y,50+rand()%25,50+rand()%50,1,360));//create Particle
						i++;
					}
					break;
				default:
					for (int i = 0; i<15;i++){
						vParticles.push_back(CreateParticles(uiSpark,map,bBul.Pos.x-bBul.Vec.Pos.x,bBul.Pos.y-bBul.Vec.Pos.y,10.0f+rand()%40,50.0f+rand()%100,dir,90));//create Particle
						i++;
					}
					break;
				}
			b=vbul.erase(b);
			iMiss ++;
		//check the weapons range
		} else if (Length(bBul.Pos.x-bBul.oPos.x,bBul.Pos.y-bBul.oPos.y)>bBul.dRange){
			switch (bBul.iParID){
				case 2:
				case 5:
				case 10:	
				for (int i = 1; i<320*iDamageOffset;i++){
						vParticles.push_back(CreateParticles(uiExplosion,map,bBul.Pos.x-bBul.Vec.Pos.x,bBul.Pos.y-bBul.Vec.Pos.y,50+rand()%25,50+rand()%50,1,360));//create Particle
						i++;
				}
				break;
			}		
			b=vbul.erase(b);
			iMiss ++;
		//if we hit an enemy before, destroy the bullet
		}else if (ts==true){
			//CreateParticles
			switch (bBul.iParID){
				case 2:
				case 5:
				case 10:	
				for (int i = 1; i<320*iDamageOffset;i++){
						vParticles.push_back(CreateParticles(uiExplosion,map,bBul.Pos.x-bBul.Vec.Pos.x,bBul.Pos.y-bBul.Vec.Pos.y,50+rand()%25,50+rand()%50,1,360));//create Particle
						i++;
				}
				break;
			}		
			for (int i = 0; i<15;i++){
				vParticles.push_back(CreateParticles(uiBlood,map,bBul.Pos.x+rand()%6-3,bBul.Pos.y+rand()%6-3,25+rand()%25,50+rand()%50,dir,45));//create Particle
				i++;
			}
			b=vbul.erase(b);
		//else update the next zombie
        }else  {
			*b = UpdateBullet(bBul,map,dt);
			b++;
		}
	}
	return vbul;
}

void DestroyBullet(){
	DestroySprite(uiBullet);
}
