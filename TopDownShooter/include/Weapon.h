////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Sets up the Creation of Weapons 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _WEAPON
#define _WEAPON

#include <vector>
#include "globals.h"
#include "Bullet.h"

extern int iDamageOffset;

struct sWeapon;

//define all the guns
extern sWeapon sGunLMG;
extern sWeapon sGunAssult;
extern sWeapon sGunLAW;
extern sWeapon sGunSniper;
extern sWeapon sGunSMG;
extern sWeapon sGunRPG;
extern sWeapon sGunLMG2;
extern sWeapon sGunAKu;
extern sWeapon sGunLMG3;
extern sWeapon sGunAK;
extern sWeapon sGunRPG2;

extern struct sWeapon **sCurrentWeapon;
extern struct sWeapon *sTempWeapon;

extern struct sWeapon *sWeapon1;
extern struct sWeapon *sWeapon2;
extern struct sWeapon *sWeapon3;
extern struct sWeapon *sWeapon4;

int GetWeaponID(sWeapon wep);
void SetWeaponByID(int id,sWeapon **wep);
void SetupWeapon(sWeapon &wep,int clips, int clipsize, int range, int recoil,double speed,int damage, double shootspeed,int reloadspeed,double UV);
void ResetWeapons();
void LoadWeapons();

void DrawWeapon(sWeapon wep,double x, double y,int dir);
void UseWeapon(sWeapon &wep, siPosition stMouse, sfPosition stMap,double DeltaTime);
void DrawHudWeapon(sWeapon wep,double x, double y,int rot);
void DrawAmmo(sWeapon wep,double vx, double vy);

bool CheckWeapons();
void DestroyWeapon();

#endif