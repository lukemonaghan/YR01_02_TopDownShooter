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
#include "weapon.h"
#include "player.h"
#include "particles.h"

#include <vector>
#include <time.h>
#include <iostream>

unsigned int iPickups = 1;
unsigned int uiHealth,uiAmmo,uiFloorItems;
std::vector <sItem> vItems;
void LoadItems(){
	uiHealth      = CreateSprite("./images/instances/Health.png"    , 16, 16, true );
	uiFloorItems  = CreateSprite("./images/instances/FloorItems.png", 16, 16, true );
	uiAmmo        = CreateSprite("./images/instances/Clips.png"     , 16, 16, true );
}

sItem CreateItem(unsigned int spr,float x, float y, float dir,float subimg,int index, int iind){
//create temp instance
	sItem itm;
//setup vars
	itm.Vec.fDir = dir;
	itm.Pos.x = x;
	itm.Pos.y = y;
	itm.Tex.uiSprite = spr; 
	itm.Tex.fIndexOffset = 1/subimg;
	itm.Tex.fIndex  = index*itm.Tex.fIndexOffset;
	itm.Tex.iIndex  = index;
	//SetSpriteUVCoordinates(itm.uiSprite,itm.dIndex,0,itm.dIndex+itm.dIndexOffset,1);
	return itm;
}
void CreateItems(int x, int y){
	int sprtemp = rand()%3+1;
	double dtempsubs = 0;
	int itempUVind = 0;
	int itempind = 0;
	int w1 = GetWeaponID(*sWeapon1);
	int w2 = GetWeaponID(*sWeapon2);
	int w3 = GetWeaponID(*sWeapon3);
	int w4 = GetWeaponID(*sWeapon4);
	switch (sprtemp){
	case 1:
		sprtemp = uiHealth;
		dtempsubs = 4;
		itempUVind = rand()%4;
		itempind = itempUVind+1;(1-4);
		break;
	case 2:
		sprtemp = uiFloorItems;
		dtempsubs = 8;
		itempUVind = rand()%8;
		itempind = (itempUVind+1)+4;(5-12);
		break;
	case 3:
		sprtemp = uiAmmo;  
		dtempsubs = 11;
		itempUVind = Choose(w1,w2,w3,w4);
		itempind = (itempUVind+1)+12;(12-23);
		break;

	}
	vItems.push_back(CreateItem(sprtemp,x,
										y, 
										rand()%360,
										dtempsubs,
										itempUVind, 
										itempind));
}

void DrawItems(std::vector<sItem> item,sfPosition stm){
	for each (sItem itm in item){
		if (bDebug==true){
			DrawLine(iScreenWidthHalf,iScreenHeightHalf,itm.Pos.x+stm.x,itm.Pos.y+stm.y,SColour(0,255,255,55));
			int tmx,tmy;
			GetMouseLocation(tmx,tmy);
			if (tmx > itm.Pos.x+stm.x-16  && 
				tmx < itm.Pos.x+stm.x+16 && 
				tmy > itm.Pos.y+stm.y-16 && 
				tmy < itm.Pos.y+stm.y+16
				){
					DrawInt(itm.Tex.uiSprite,itm.Pos.x+stm.x,itm.Pos.x+stm.y-32);
				DrawInt(itm.Tex.fIndexOffset*100,itm.Pos.x+stm.x,itm.Pos.x+stm.y);
				DrawInt(itm.Tex.fIndex*100,itm.Pos.x+stm.x,itm.Pos.x+stm.y+32);
			}
		}
		SetSpriteUVCoordinates(itm.Tex.uiSprite,itm.Tex.fIndex,0,itm.Tex.fIndex+itm.Tex.fIndexOffset,1);
		DrawImage(itm.Tex.uiSprite,itm.Pos.x+stm.x,itm.Pos.y+stm.y,itm.Vec.fDir);
	}
}
void PickupItems(std::vector<sItem> &item, sfPosition stm,double x, double y){
	//update all npc's for the group
	std::vector<sItem>::iterator i = item.begin();
	while (i!=item.end()) {
        sItem ins = *i;
		//Collisions
		if (CheckBox((ins.Pos.x-32.0f)+stm.x , (ins.Pos.y-32.0f)+stm.y, (ins.Pos.x+32.0f)+stm.x, (ins.Pos.y+32.0f)+stm.y,x,y)!=0){
			std::cout << ins.Tex.iIndex << std::endl;
			switch (ins.Tex.iIndex){
////////////////health/speed
                case 1:
                    iPlayerHealth+=50;
                    break;
                case 2:
                    iPlayerHealth+=25;
                    break;
                case 3:
                    fSpeed+=50;
                    break;
				case 4:
					fSpeed+=25;
					break;
////////////////flooritems(random risky food coins paper phones)
				case 5:
					iPlayerHealth+=(rand()%10+1)-5;
					break;
				case 6:
					iPlayerHealth+=(rand()%20+1)-10;
					break;
				case 7:
					iPlayerHealth+=(rand()%15+1)-7;
					break;
				case 8:
					iPlayerHealth+=(rand()%30+1)-15;
					break;
				case 9:
					iPlayerHealth+=(rand()%25+1)-20;
					break;
				case 10:
					iPlayerHealth+=(rand()%10+1)-5;
					break;
				case 11:
					iPlayerHealth+=(rand()%50+1)-10;
					break;
				case 12:
					iPickups+=10;
					iDamageOffset++;
					break;
////////////////ammo
				case 13:
					if (sGunLMG.iClips<10){
					sGunLMG.iClips++;
					}
					break;
				case 14:
					if (sGunAssult.iClips<10){
					sGunAssult.iClips++;
					}
					break;
				case 15:
					if (sGunLAW.iClips<10){
					sGunLAW.iClips++;
					}
					break;
				case 16:
					if (sGunSniper.iClips<10){
					sGunSniper.iClips++;
					}
					break;
				case 17:
					if (sGunSMG.iClips<10){
					sGunSMG.iClips++;
					}
					break;
				case 18:
					if (sGunRPG.iClips<10){
					sGunRPG.iClips++;
					}
					break;
				case 19:
					if (sGunLMG2.iClips<10){
					sGunLMG2.iClips++;
					}
					break;
				case 20:
					if (sGunAKu.iClips<10){
					sGunAKu.iClips++;
					}
					break;
				case 21:
					if (sGunLMG3.iClips<10){
					sGunLMG3.iClips++;
					}
					break;
				case 22:
					if (sGunAK.iClips<10){
					sGunAK.iClips++;
					}
					break;
				case 23:
					if (sGunRPG2.iClips<10){
					sGunRPG2.iClips++;
					}
					break;
				}
				i=item.erase(i);
		} else {
		i++;
		}  
    }
}

void DestroyPickups(){
	DestroySprite(uiHealth);
	DestroySprite(uiFloorItems);
	DestroySprite(uiAmmo);      
}