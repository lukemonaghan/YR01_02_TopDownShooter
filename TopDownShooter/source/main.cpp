////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Main CPP for Top Down Shooter
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "VectorMath.h"
#include "map1.h"
#include "Bullet.h"
#include "ai.h"
#include "Menus.h"
#include "globals.h"
#include "Player.h"
#include "weapon.h"
#include "Pickups.h"
#include "particles.h"
#include "highscores.h"
#include "FileManagement.h"

#include <string>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;
////DeltaTime
float LastTime = clock();
float DeltaTime = 0.0f;
float fFrames = 0.0f;
float fFPS = 0.0f;
float LastFPS = 0.0f;

//main function
int main( int argc, char* argv[] ){
	srand((unsigned)time(NULL));
	Initialise( iScreenWidth, iScreenHeight, false, "Top Down Shooter - Luke Monaghan" );
////Structs
	siPosition stMouse;
	sfPosition stWorld;
	sfPosition sVector;
	sfPosition stMap;
	sfPosition stBlackHawk;
////Structs
	stWorld.x = iScreenWidthHalf+((rand()%iMapWidth*0.6) - (iMapWidth*0.6));
	stWorld.y = iScreenHeightHalf+((rand()%iMapHeight*0.3) - (iMapHeight*0.3));
	stMap.x = stMap.y = 0.0f;
	stMouse.x = stMouse.y = 0;
	stBlackHawk.x = stWorld.x;
	stBlackHawk.y = stWorld.y;
////Vectors
	std::vector <instance> vNPCs;
//Load Images
	LoadBullets();
	LoadMenu();
	LoadPlayer();
	LoadWeapons();
	LoadInstance();
	LoadItems();
	LoadParticles();
	LoadMap();
	LoadHighscores();
	LoadSettings();
	unsigned int sCursor = CreateSprite( "./images/cursor.png", 32, 32, true );	
	unsigned int sBlackHawk = CreateSprite( "./images/instances/blackhawk.png", 576, 576, true );	
	unsigned int sBlackHawkBlades = CreateSprite( "./images/instances/blackhawkblades.png", 576, 576, true );	
	float wallvx;
	float wallvy;
	do 
	{
////////delta
	DeltaTime = (clock() - LastTime)/(float)CLOCKS_PER_SEC;
	LastTime = clock();
		if (fFrames >= 1){
			fFrames = 0;
			fFPS = (clock() - LastFPS)/(float)CLOCKS_PER_SEC;
			LastFPS = clock();
		}
		fFrames+=DeltaTime;
////////clear the screen for drawing
		ClearScreen();
////////Check the current game state
		switch(eCurrentState)
		{
////////////SPLASH
		case GS_SPLASH_SCREEN:
			DrawSplashScreen(DeltaTime);
			break;
////////////MAIN
		case GS_MAIN_MENU:
			DrawMainMenu();
			break;
////////////CUSTOMIZE
		case GS_CUSTOMIZE_MENU:
			DrawCustomizeMenu();
			break;
////////////HIGHSCORES
		case GS_HIGHSCORES_MENU:
			DrawHighscoresMenu();
			break;
////////////CUSTOMIZE
		case GS_GUN_SELECT_MENU:
			DrawGunSelectMenu();
			break;
////////////CUSTOMIZE
		case GS_PLAYER_SELECT_MENU:
			DrawPlayerSelectMenu();
			break;
////////////MAPSELECT
		//case GS_MAP_SELECT_MENU:
		//	DrawMapSelectMenu();
		//	break;
////////////OPTIONS
		case GS_OPTIONS_MENU:
			DrawOptionsMenu();
			break;
////////////HELP
		case GS_HELP_MENU:
			DrawHelpMenu();
			break;
////////////HELP2
		case GS_HELP_MENU2:
			DrawHelpMenu2();
			break;
////////////GAME
		case GS_GAME_SCREEN:
				//Vector stuff
				GetMouseLocation( stMouse.x, stMouse.y );
				sVector.x = ((float)stMouse.x - (float)iScreenWidthHalf);
				sVector.y = ((float)stMouse.y - (float)iScreenHeightHalf);
                //player rotation
				iDirection = -90 -atan2( sVector.y, sVector.x )* 180 / PI;
				//Draw Level
				stMap.x = iScreenWidthHalf  - stWorld.x;
				stMap.y = iScreenHeightHalf - stWorld.y;
				DrawImage(uiMap1,stMap.x,stMap.y,0);
				//Draw Fancy Walls, (currently broken because of zbuffer)
				//wallvx = (stMap.x -iScreenWidthHalf);
				//wallvy = -abs(stMap.y -iScreenHeightHalf);
				//Normalize(wallvx,wallvy);
				//DrawImage(uiMap1Wall,wallvx,wallvy,0,stMap,5,8);
				//Create another enemy if one is destroyed
                while (vNPCs.size()<iEnemies+iKills){
                    vNPCs.push_back(CreateInstance(((rand()%iMapWidth*0.9) - (iMapWidth*0.45)),
												   ((rand()%iMapHeight*0.9) - (iMapHeight*0.45)),
												   iDirection,
												   100+rand()%100,
												   100+(rand()%10*iKills),
												   iScreenWidthHalf,
												   iScreenHeightHalf));
				}
				//create the items
				while (iPickups > 0){
					iPickups--;
					CreateItems((rand()%iMapWidth*0.9) - (iMapWidth*0.45),(rand()%iMapHeight*0.9) - (iMapHeight*0.45));
				}
				//DrawItems
				DrawItems(vItems,stMap);
                PickupItems(vItems,stMap,iScreenWidthHalf,iScreenHeightHalf);
				//Update And Draw Bullets
				vBullets = UpdateBullets(vBullets,vNPCs,stMap,DeltaTime);
				DrawBullet(vBullets);
				//Update And Draw NPCs
				UpdateNPC(vNPCs,stMap,iScreenWidthHalf,iScreenHeightHalf,stWorld,DeltaTime);
				DrawNPC(vNPCs);
				//Draw Player
				DrawPlayer(DeltaTime);	
				//update particles
				vParticles = UpdateParticles(vParticles,vNPCs,stMap,DeltaTime);
				//Move Player
				MovementPlayer(DeltaTime,stWorld,sVector,stMap );
				//Using the current weapon
				if (MenuCheck == 0){
				UseWeapon(**sCurrentWeapon, stMouse, stMap,DeltaTime);
				}
				//blackhawk
				if (stBlackHawk.x>-4000){
					DrawImage(sBlackHawk,stMap.x+stBlackHawk.x,stMap.y+stBlackHawk.y,90);
					DrawImage(sBlackHawkBlades,stMap.x+stBlackHawk.x,stMap.y+stBlackHawk.y,iBladesRot);
					iBladesRot+=1000.0f*DeltaTime;
					stBlackHawk.x -= (600.0f*DeltaTime);
				}
				//draw the game menu
				DrawGameMenu();
				//Draw Cursor
				DrawImage(sCursor,stMouse.x,stMouse.y,iDirection);
				//reset the world when dead or closed
				if (iPlayerHealth<0 || IsKeyDown(KEY_ESC)){
					AddHighscore(iKills,iMiss,iHits);
					if (vBullets.size()>0){
						std::vector<bullet>::iterator   bul = vBullets.begin();
						while (bul!=vBullets.end()) {
							bullet bBul = *bul;
							bul=vBullets.erase(bul);
						}
					}
					if (vNPCs.size()>0){
						std::vector<instance>::iterator   ins = vNPCs.begin();
						while (ins!=vNPCs.end()) {
							instance vins = *ins;
							ins=vNPCs.erase(ins);
						}
					}
					if (vItems.size()>0){
						std::vector<sItem>::iterator   itm = vItems.begin();
						while (itm!=vItems.end()) {
							sItem vitm = *itm;
							itm=vItems.erase(itm);
						}
					}
					if (vParticles.size()>0){
						std::vector<particle>::iterator   par = vParticles.begin();
						while (par!=vParticles.end()) {
							particle vitm = *par;
							par=vParticles.erase(par);
						}
					}
					//reset world
					stWorld.x = iScreenWidthHalf+((rand()%iMapWidth*0.6) - (iMapWidth*0.6));
					stWorld.y = iScreenHeightHalf+((rand()%iMapHeight*0.3) - (iMapHeight*0.3));
					stMap.x = stMap.y = 0;
					stMouse.x = stMouse.y = 0;
					stBlackHawk.x = stWorld.x;
					stBlackHawk.y = stWorld.y;
					//reset globals(move when I make scorescreen)
					ResetWeapons();
					dEnergy = dMaxEnergy;
					iPlayerHealth = 100;
					fSpeed = 270;
					iRunning = 1;
					dImage=0;
					dAnitimer = 0;
					iKills = 0;
					iMiss = 0;
					iHits = 0;
					iPickups = rand()%10+1;
					//go back to the main menu
					eCurrentState = GS_HIGHSCORES_MENU;
					MenuCheck=1;
			}
			break;
		default:
			break;
		}//End of Switch Statement
        if (bDebug == true){          
            DrawLine(iScreenWidthHalf,iScreenHeightHalf,stMap.x,stMap.y,SColour(0,255,0,155));
////left
            DrawString("Vector Arrays",0,0);
            DrawInt((int)vBullets.size(),0, 32);
            DrawInt((int)vNPCs.size(),0, 64);
			DrawInt((int)vItems.size(),0, 96);
			DrawInt(iPickups,64, 96);
			DrawInt((int)vParticles.size(),0, 128);
			DrawInt((int)vHighScores.size(),0, 160);
//right
            DrawString("Keys",iScreenWidth-96,0);
            DrawInt(IsKeyDown('W'),iScreenWidth-32, 32);
            DrawInt(IsKeyDown('S'),iScreenWidth-32, 64);
            DrawInt(IsKeyDown('A'),iScreenWidth-32, 96);
            DrawInt(IsKeyDown('D'),iScreenWidth-32, 128);
           
            DrawInt(IsKeyDown(KEY_LSHIFT),iScreenWidth-32, 192);

            DrawInt(GetMouseButtonDown(MOUSE_BUTTON_1),iScreenWidth-32, 256);
            DrawInt(GetMouseButtonDown(MOUSE_BUTTON_2),iScreenWidth-32, 288);
            DrawInt(GetMouseButtonDown(MOUSE_BUTTON_3),iScreenWidth-32, 320);
            DrawInt(MenuCheck,iScreenWidth-32, 352);
//middle
            DrawString("Positions",iScreenWidthHalf-72,0);
			DrawString("Map",iScreenWidthHalf-32,32);
            DrawInt(stMap.x,iScreenWidthHalf-64, 64);
            DrawInt(stMap.y,iScreenWidthHalf+64, 64);
			DrawString("World",iScreenWidthHalf-48,96);
            DrawInt(stWorld.x,iScreenWidthHalf-64, 128);
            DrawInt(stWorld.y,iScreenWidthHalf+64, 128);
			DrawString("Mouse",iScreenWidthHalf-48,160);
            DrawInt(stMouse.x,iScreenWidthHalf-64, 192);
            DrawInt(stMouse.y,iScreenWidthHalf+64, 192);
			DrawString("SpeedHealth",iScreenWidthHalf-48,224);
            DrawInt(iPlayerHealth,iScreenWidthHalf-64, 256);
            DrawInt(fSpeed,iScreenWidthHalf+64, 256);
			DrawInt(DeltaTime*1000,iScreenWidthHalf-64, 288);
			DrawInt(fFPS,iScreenWidthHalf-64, 320);
			
        }
	} while ( FrameworkUpdate() == false && bRunning==true );

	DestroyInstance();
	DestroyBullet();
	DestroyMenu();
	DestroyPlayer();
	DestroyWeapon();
	DestroyPickups();
	DestroyParticle();
	DestroySprite(sCursor);
	DestroySprite(uiMap1);
	DestroySprite(sBlackHawk);
	DestroySprite(sBlackHawkBlades);
	SaveHighscores();
	SaveSettings();
	Shutdown();

	return 0;
}