////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Create, draw, and use of weapons
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Weapon.h"
#include "AIE.h"
#include "globals.h"
#include "Bullet.h"
#include "Menus.h"

#include <vector>
//load image and setup UV
unsigned int sWeapons;
double dWeaponOffset = 0.091;
//setup global vars for damage multiplier shooting and reloading timers
int iDamageOffset = 1;
double ShootVar = 0,ReloadTimer = 0;
//keychecker
int KeyCheck = 1;
//pointers to the selected weapons
struct sWeapon *sWeapon1;
struct sWeapon *sWeapon2;
struct sWeapon *sWeapon3;
struct sWeapon *sWeapon4;
//pointers to tempweapon (for setting guns) and currentweapon
struct sWeapon *sTempWeapon;
struct sWeapon **sCurrentWeapon;
//all the weapons
sWeapon sGunLMG;
sWeapon sGunAssult;
sWeapon sGunLAW;
sWeapon sGunSniper;
sWeapon sGunSMG;
sWeapon sGunRPG;
sWeapon sGunLMG2;
sWeapon sGunAKu;
sWeapon sGunLMG3;
sWeapon sGunAK;
sWeapon sGunRPG2;
//setting and getting weapons by ID 
int GetWeaponID(sWeapon wep){
	return wep.iID;
}
void SetWeaponByID(int id,sWeapon **wep){
	switch(id){
	case 0:
		*wep=&sGunLMG;
		break;
	case 1:
		*wep=&sGunAssult;
		break;
	case 2:
		*wep=&sGunLAW;
		break;
	case 3:
		*wep=&sGunSniper;
		break;
	case 4:
		*wep=&sGunSMG;
		break;
	case 5:
		*wep=&sGunRPG;
		break;
	case 6:
		*wep=&sGunLMG2;
		break;
	case 7:
		*wep=&sGunAKu;
		break;
	case 8:
		*wep=&sGunLMG3;
		break;
	case 9:
		*wep=&sGunAK;
		break;
	case 10:
		*wep=&sGunRPG2;
		break;
	}
}
//setting up the weapons
void SetupWeapon(sWeapon &wep,int clips, int clipsize, int range, int recoil,double speed, int damage, double shootspeed,int reloadspeed,double UV){
	wep.iClips = clips;
	wep.iClipSize = clipsize;
	wep.iRange = range;
	wep.iRecoil = recoil;
	wep.dSpeed = speed;
	wep.dShootSpeed = shootspeed;
	wep.UVIndex = UV;
	wep.iBullets = wep.iClipSize;
	wep.iReloadSpeed = reloadspeed;
	wep.iDamage = damage;
	wep.iID = (UV/dWeaponOffset)*1;
}
void ResetWeapons(){
	SetupWeapon(sGunLMG   , 3, 75, 1000, 10, 1000, 80 , 0.15, 60 , 0);
	SetupWeapon(sGunAssult, 4, 40, 1000, 8 , 1200, 60 , 0.1 , 40 , dWeaponOffset);
	SetupWeapon(sGunLAW   , 3, 1 , 800 , 15, 500 , 300, 1   , 150, dWeaponOffset*2);
    SetupWeapon(sGunSniper, 5, 6 , 1500, 5 , 800 , 120, 0.3 , 75 , dWeaponOffset*3);
	SetupWeapon(sGunSMG   , 5, 25, 600 , 4 , 1400, 40 , 0.05, 30 , dWeaponOffset*4);
	SetupWeapon(sGunRPG   , 2, 1 , 500 , 15, 550 , 250, 1   , 140, dWeaponOffset*5);
	SetupWeapon(sGunLMG2  , 3, 70, 1200, 10, 1000, 85 , 0.15, 60 , dWeaponOffset*6);
	SetupWeapon(sGunAKu   , 5, 30, 650 , 4 , 1400, 45 , 0.05, 35 , dWeaponOffset*7);
	SetupWeapon(sGunLMG3  , 3, 65, 1200, 10, 1000, 75 , 0.15, 60 , dWeaponOffset*8);
	SetupWeapon(sGunAK    , 4, 35, 900 , 8 , 1200, 65 , 0.1 , 45 , dWeaponOffset*9);
	SetupWeapon(sGunRPG2  , 4, 1 , 500 , 15, 600 , 275, 1   , 250, dWeaponOffset*10);

}
void LoadWeapons(){
	sWeapons  = CreateSprite( "./images/instances/Player/Guns.png", 32, 96, true );
	//setup the guns
	ResetWeapons();
	sWeapon1 = &sGunLMG;
	sWeapon2 = &sGunAssult;
	sWeapon3 = &sGunLAW;
	sWeapon4 = &sGunSMG;
	sCurrentWeapon = &sWeapon1;
	//set the UV
	SetSpriteUVCoordinates(sWeapons,sGunLMG.UVIndex,0,sGunLMG.UVIndex+dWeaponOffset,1);
}
//drawing
//remove the duplicate functions
void DrawWeapon(sWeapon wep,double x, double y,int dir){
	SetSpriteUVCoordinates(sWeapons,wep.UVIndex,0,wep.UVIndex+dWeaponOffset,1);
	DrawImage(sWeapons,x,y,dir);
}
void DrawHudWeapon(sWeapon wep,double x, double y,int rot){
	SetSpriteUVCoordinates(sWeapons,wep.UVIndex,0,wep.UVIndex+dWeaponOffset,1);
	DrawImage(sWeapons,x,y,rot);
}
void DrawAmmo(sWeapon wep,double vx, double vy){
	//clips
	SetSpriteUVCoordinates(uiBar,1,0,0,1);
	MoveSprite(uiBar,(iScreenWidthHalf*1.8)+vx,iScreenHeightHalf*1.8+vy);
	DrawSprite(uiBar);
	//bullets
	MoveSprite(uiBar,(iScreenWidthHalf*1.75)+vx,iScreenHeightHalf*1.9+dVecY);
	DrawSprite(uiBar);	
	DrawString("AMMO",iScreenWidthHalf*1.7+vx,iScreenHeightHalf*1.92+vy);
	DrawInt(wep.iClips,iScreenWidth-(310*(((float)wep.iClips)/10))+vx,(iScreenHeightHalf*1.8)-12+vy);
	DrawInt(wep.iBullets,iScreenWidth-(310*(((float)wep.iBullets+1)/((float)wep.iClipSize+1)))+vx,(iScreenHeightHalf*1.9)-12+vy);
	
}
//shooting
void UseWeapon(sWeapon &wep, siPosition stMouse, sfPosition stMap,double DeltaTime){
	if (!GetMouseButtonDown(MOUSE_BUTTON_2) && GetMouseButtonDown(MOUSE_BUTTON_1) && ShootVar>wep.dShootSpeed && wep.iBullets>0 && ReloadTimer > 1){
		wep.iBullets--;
		ShootVar=0;
		vBullets.push_back(CreateBullet(iScreenWidthHalf,iScreenHeightHalf,stMap,iDirection,wep.dSpeed,wep.iRange,wep.iID,wep.iDamage*iDamageOffset,wep.iRecoil));
	} 
	if ( wep.iBullets==0 && wep.iClips == 0){
		DrawString("!Out of Ammo!",iScreenWidthHalf-64,iScreenHeight-64);
	}
	if ( wep.iBullets<wep.iClipSize/3 && wep.iClips > 0){
		DrawString("Reload",iScreenWidthHalf-32,iScreenHeight-64);
	}
	if ( IsKeyDown('R') && ReloadTimer > 1 && wep.iBullets<wep.iClipSize && wep.iClips > 0){
		ReloadTimer = 0;
		wep.iBullets=wep.iClipSize;
		wep.iClips-=1;
	}
	ShootVar+=DeltaTime;
	ReloadTimer+=DeltaTime;

	if (IsKeyDown('1') &&  KeyCheck==0){
		KeyCheck=1;
		sCurrentWeapon = &sWeapon1;
	} 
	if (IsKeyDown('2') &&  KeyCheck==0){
		KeyCheck=1;
		sCurrentWeapon = &sWeapon2;
	} 
	if (IsKeyDown('3') &&  KeyCheck==0){
		KeyCheck=1;
		sCurrentWeapon = &sWeapon3;
	} 
	if (IsKeyDown('4') &&  KeyCheck==0){
		KeyCheck=1;
		sCurrentWeapon = &sWeapon4;
	} 
	if (!IsKeyDown('1') && !IsKeyDown('2') && !IsKeyDown('3') && !IsKeyDown('4')){
		KeyCheck=0;
	}
}
//checking if selected weapon is already equiped(for the weapons selection)
bool CheckWeapons(){
	if (sTempWeapon == sWeapon1
	||  sTempWeapon == sWeapon2
	||  sTempWeapon == sWeapon3
	||  sTempWeapon == sWeapon4){
		return true;
	}
	return false;
}
//destroy the weapon sprite
void DestroyWeapon(){
	DestroySprite(sWeapons);
}