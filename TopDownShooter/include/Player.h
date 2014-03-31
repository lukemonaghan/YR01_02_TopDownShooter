/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//                                                                          Brief:      Setting up the player
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER
#define _PLAYER
#include <vector>
#include "globals.h"

extern const double dMaxEnergy;
extern double dEnergy;
extern int iPlayerHealth;
extern float fSpeed;
extern int iRunning;

extern unsigned int sPlayerHeads,sPlayerBodys,sPlayerLegs;

extern struct sUVAnimation{
	float fIndex,fOffset,fYIndex,fYOffset,fTimer,fYTimer;
	int iIndexID,iID;
};

extern struct sUVAnimation sUVPlayerHeads;
extern struct sUVAnimation sUVPlayerBodys;
extern struct sUVAnimation sUVPlayerLegs;

void LoadPlayer();

int GetPlayerPartID(sUVAnimation player);
void RollPlayerPart(sUVAnimation &player);
void SetPlayerPartByID(sUVAnimation &player,int id);

void DrawPlayer(float dt);
void DrawHudPlayer(float x, float y);

void MovementPlayer(float DeltaTime,sfPosition &stWorld,sfPosition &sVector,sfPosition &stMap );
void ShootPlayer(float DeltaTime,std::vector <bullet> &vBullets, siPosition &stMouse, sfPosition &stMap,int iDirection);

void DestroyPlayer();

#endif