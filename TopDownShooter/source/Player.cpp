#include "AIE.h"
#include "Globals.h"
#include "VectorMath.h"
#include  "Map1.h"
#include "Bullet.h"
#include "weapon.h"
#include "player.h"

#include <vector>
//variables
const double dMaxEnergy = 3;
double dEnergy = dMaxEnergy;
const double iPlayerHealthNormal = 100;
int iPlayerHealth = iPlayerHealthNormal;
const float dSpeedMax = 270.0f;
float fSpeed = dSpeedMax;
int iRunning = 1;
double dDegradeTimer = 0;
//images
unsigned int sPlayerHeads,sPlayerBodys,sPlayerLegs;
//create each index
sUVAnimation sUVPlayerHeads;
sUVAnimation sUVPlayerBodys;
sUVAnimation sUVPlayerLegs;
//functions
void LoadPlayer(){
	//setup each index
	//head
	sUVPlayerHeads.fIndex = 0;
	sUVPlayerHeads.fYIndex = 0;
	sUVPlayerHeads.fOffset = 0.125;
	sUVPlayerHeads.fYOffset = 0.5;
	sUVPlayerHeads.fTimer = 0;
	sUVPlayerHeads.iID=0;
	//body
	sUVPlayerBodys.fIndex = 0;
	sUVPlayerBodys.fYIndex = 0;
	sUVPlayerBodys.fOffset = 0.125;
	sUVPlayerBodys.fYOffset = 0.5;
	sUVPlayerBodys.fTimer = 0;
	sUVPlayerBodys.iID=1;
	//legs
	sUVPlayerLegs.fIndex = 0;
	sUVPlayerLegs.fYIndex = 0;
	sUVPlayerLegs.fOffset = 0.25;
	sUVPlayerLegs.fYOffset = 0.0625;
	sUVPlayerLegs.fTimer = 0;
	sUVPlayerLegs.fYTimer = 0;
	sUVPlayerLegs.iID=2;
	//Loads the player and sets up the UV
	sPlayerHeads  = CreateSprite( "./images/instances/Player/Heads.png", 16, 16, true );
	SetSpriteUVCoordinates(sPlayerHeads,sUVPlayerHeads.fIndex,sUVPlayerHeads.fYIndex,sUVPlayerHeads.fIndex+sUVPlayerHeads.fOffset,sUVPlayerHeads.fYIndex+sUVPlayerHeads.fYOffset);
	sPlayerBodys  = CreateSprite( "./images/instances/Player/Bodys.png", 64, 64, true );
	SetSpriteUVCoordinates(sPlayerBodys,sUVPlayerHeads.fIndex,sUVPlayerBodys.fYIndex,sUVPlayerBodys.fIndex+sUVPlayerBodys.fOffset,sUVPlayerBodys.fYIndex+sUVPlayerBodys.fYOffset);
	sPlayerLegs  = CreateSprite( "./images/instances/Player/Legs.png", 32, 32, true );
	SetSpriteUVCoordinates(sPlayerLegs,sUVPlayerLegs.fIndex,sUVPlayerLegs.fYIndex,sUVPlayerLegs.fIndex+sUVPlayerLegs.fOffset,sUVPlayerLegs.fYIndex+sUVPlayerLegs.fYOffset);
}

int GetPlayerPartID(sUVAnimation player){
	return player.iIndexID;
}
void RollPlayerPart(sUVAnimation &player){
	switch(player.iID){
	case 0:
	case 1:
		player.fIndex+=player.fOffset;
		player.iIndexID+=1;
		if (player.fIndex>1){
			player.fIndex=0;
			player.fYIndex+=player.fYOffset;
			if (player.fYIndex>1){
				player.fYIndex=0;
				player.iIndexID=0;
			}
		}
		break;
	case 2:
		player.fYIndex+=player.fYOffset;
		player.iIndexID+=1;
		if (player.fYIndex>1){
			player.fYIndex=0;
			player.iIndexID=0;
		}
		break;
	}	
}
void SetPlayerPartByID(sUVAnimation &player,int id){
	switch(player.iID){
	case 0:
	case 1:
		player.iIndexID=id;
		player.fIndex=player.fOffset*id;
		if (player.fIndex>1){
			player.fIndex=0;
			player.fYIndex=player.fYOffset;
		}
		break;
	case 2:
		player.iIndexID=id;
		player.fYIndex=player.fYOffset*id;
		break;
	}	
}
void DrawPlayer(float dt){
	if (IsKeyDown('W') || IsKeyDown('S') || IsKeyDown('A') || IsKeyDown('D')){
			if (sUVPlayerLegs.fIndex>1){
				sUVPlayerLegs.fIndex=0;
			}else if (sUVPlayerLegs.fTimer>0.1){
				sUVPlayerLegs.fIndex+=sUVPlayerLegs.fOffset;sUVPlayerLegs.fTimer=0;
			}
			sUVPlayerLegs.fTimer+=dt;
		}
	//legs
	SetSpriteUVCoordinates(sPlayerLegs,sUVPlayerLegs.fIndex,sUVPlayerLegs.fYIndex,sUVPlayerLegs.fIndex+sUVPlayerLegs.fOffset,sUVPlayerLegs.fYIndex+sUVPlayerLegs.fYOffset);
	DrawImage(sPlayerLegs,iScreenWidthHalf,iScreenHeightHalf,iDirection);
	//body
	SetSpriteUVCoordinates(sPlayerBodys,sUVPlayerBodys.fIndex,sUVPlayerBodys.fYIndex,sUVPlayerBodys.fIndex+sUVPlayerBodys.fOffset,sUVPlayerBodys.fYIndex+sUVPlayerBodys.fYOffset);
	DrawImage(sPlayerBodys,iScreenWidthHalf,iScreenHeightHalf,iDirection);
	DrawWeapon(**sCurrentWeapon,iScreenWidthHalf,iScreenHeightHalf,iDirection);
	//head
	SetSpriteUVCoordinates(sPlayerHeads,sUVPlayerHeads.fIndex,sUVPlayerHeads.fYIndex,sUVPlayerHeads.fIndex+sUVPlayerHeads.fOffset,sUVPlayerHeads.fYIndex+sUVPlayerHeads.fYOffset);
	DrawImage(sPlayerHeads,iScreenWidthHalf,iScreenHeightHalf,iDirection);
}
void DrawHudPlayer(float x, float y){
	//legs
	SetSpriteUVCoordinates(sPlayerLegs,sUVPlayerLegs.fIndex,sUVPlayerLegs.fYIndex,sUVPlayerLegs.fIndex+sUVPlayerLegs.fOffset,sUVPlayerLegs.fYIndex+sUVPlayerLegs.fYOffset);
	DrawImage(sPlayerLegs,x,y,0);
	//body
	SetSpriteUVCoordinates(sPlayerBodys,sUVPlayerBodys.fIndex,sUVPlayerBodys.fYIndex,sUVPlayerBodys.fIndex+sUVPlayerBodys.fOffset,sUVPlayerBodys.fYIndex+sUVPlayerBodys.fYOffset);
	DrawImage(sPlayerBodys,x,y,0);
	//weapon
	DrawHudWeapon(**sCurrentWeapon,x,y,0);
	//head
	SetSpriteUVCoordinates(sPlayerHeads,sUVPlayerHeads.fIndex,sUVPlayerHeads.fYIndex,sUVPlayerHeads.fIndex+sUVPlayerHeads.fOffset,sUVPlayerHeads.fYIndex+sUVPlayerHeads.fYOffset);
	DrawImage(sPlayerHeads,x,y,0);
}

void MovementPlayer(float DeltaTime,sfPosition &stWorld,sfPosition &sVector,sfPosition &stMap ){
	if (dDegradeTimer>0.5){
		dDegradeTimer=0;
		if (fSpeed>dSpeedMax){
			fSpeed--;
		}
		if (iPlayerHealth>iPlayerHealthNormal){
			iPlayerHealth--;
		}
	}
	dDegradeTimer+=DeltaTime;
	bChkMap = CheckMap(stMap.x,stMap.y,iScreenWidthHalf,iScreenHeightHalf,sVector.x,sVector.y,16);
	if (bChkMap!=0){
		switch (bChkMap){
		case 1:
			stWorld.x -= 2.0f*fSpeed*iRunning*DeltaTime;
			break;		
		case 2:			 
			stWorld.x += 2.0f*fSpeed*iRunning*DeltaTime;
			break;		 
		case 3:			
			stWorld.y -= 2.0f*fSpeed*iRunning*DeltaTime;
			break;		 
		case 4:			 
			stWorld.y += 2.0f*fSpeed*iRunning*DeltaTime;
			break;
		}
	}
	if ( IsKeyDown(KEY_LSHIFT) && dEnergy>0  ){
		dEnergy-=DeltaTime;
		iRunning = 2;
	}else if (IsKeyDown(KEY_LCTRL)){
		iRunning = 0.5;
	}else{
		iRunning = 1;
		if (dEnergy<dMaxEnergy){
			dEnergy+=DeltaTime*0.5;
		}
	}
//Moves the player dependant on the global var " usevariablemovement"(little long and complicated, refactor in assignment3)
	if (usevariablemovement == true){

		if ( IsKeyDown('W') ){
			Normalize(sVector.x,sVector.y);
			stWorld.x += sVector.x*fSpeed*iRunning*DeltaTime;
			stWorld.y += sVector.y*fSpeed*iRunning*DeltaTime;
		}
		if ( IsKeyDown('S')){
			Normalize(sVector.x,sVector.y);
			stWorld.x -= sVector.x*fSpeed*iRunning*DeltaTime;	
			stWorld.y -= sVector.y*fSpeed*iRunning*DeltaTime;
		}
		if ( IsKeyDown('A') ){
			Rotate(-1.57079633f,sVector.x,sVector.y);
			Normalize(sVector.x,sVector.y);
			stWorld.x += sVector.x*(fSpeed*0.5)*iRunning*DeltaTime;
			stWorld.y += sVector.y*(fSpeed*0.5)*iRunning*DeltaTime;
		}
		if ( IsKeyDown('D') ){
			Rotate(1.57079633f,sVector.x,sVector.y);
			Normalize(sVector.x,sVector.y);
			stWorld.x += sVector.x*(fSpeed*0.5)*iRunning*DeltaTime;	
			stWorld.y += sVector.y*(fSpeed*0.5)*iRunning*DeltaTime;
		}
	}else{
		if ( IsKeyDown('W') ){
			stWorld.y -= fSpeed*iRunning*DeltaTime;
		}
		if ( IsKeyDown('S') ){
			stWorld.y += fSpeed*iRunning*DeltaTime;
		}
		if ( IsKeyDown('A') ){
			stWorld.x -= fSpeed*iRunning*DeltaTime;
		}
		if ( IsKeyDown('D') ){
			stWorld.x += fSpeed*iRunning*DeltaTime;
		}
	}
}

void DestroyPlayer(){
	DestroySprite(sPlayerHeads);
	DestroySprite(sPlayerBodys);
	DestroySprite(sPlayerLegs);
}