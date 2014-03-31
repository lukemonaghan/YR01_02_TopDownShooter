////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Creates, draws and updates the menus
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//this is SUPER messy.. Lots of refactoring to do in assignment three.

#include "AIE.h"
#include "Menus.h"
#include "globals.h"
#include "VectorMath.h"
#include "weapon.h"
#include "player.h"
#include "particles.h"
#include "highscores.h"
#include "ai.h"
#include "Pickups.h"

#include <time.h>
#include <math.h>

unsigned int uiHex,uiHeader,uiBackground,uiBackground2,uiHelpS,uiHud,uiCustomize,uiHelp,uiHelpS2,uiHighScores,uiOptions,uiSurvival,uiSelected,uiLogo,uiLogoAIE;
unsigned int uiBar,uiSlider;
//unsigned int uiMapOffice,uiMapOffice1,uiMapOffice2,uiMapOffice3,uiMapOffice4,uiMapOffice5;

unsigned int curwep = 0;
int iMouseX,iMouseY;
int MenuCheck = 0;
double dVecX = 0;double dVecY = 0;
double dOffX = iScreenWidthHalf;
double dOffY = iScreenHeight-128;
double dTimer=0;
float size1[] = {280,224};
float size2[] = {140,112};

bool CheckMouse(int x1, int x2, int y1, int y2){
	if (iMouseX > x1  && iMouseX < x2 && iMouseY > y1 && iMouseY < y2){
		return true;
	}
	return false;
}

void LoadMenu(){
	uiHex          = CreateSprite( "./images/Menus/HexagonTile.png"    , 280, 224, true , SColour(255,255,255,155));
	//uiMapOffice    = CreateSprite( "./images/maps/OfficeTile.png"      , 512 , 256, true );
	//uiMapOffice1   = CreateSprite( "./images/maps/OfficeTile.png"      , 512 , 256, true );
	//uiMapOffice2   = CreateSprite( "./images/maps/OfficeTile.png"      , 512 , 256, true );
	//uiMapOffice3   = CreateSprite( "./images/maps/OfficeTile.png"      , 512 , 256, true );
	//uiMapOffice4   = CreateSprite( "./images/maps/OfficeTile.png"      , 512 , 256, true );

	uiHeader      = CreateSprite( "./images/Menus/Title.png"           , 988 , 113, true );
	uiBackground  = CreateSprite( "./images/Menus/Background.png"      , 1280, 780, false);
	uiBackground2 = CreateSprite( "./images/Menus/bgOverlay.png"       , 1408, 858, true);
    uiHelpS       = CreateSprite( "./images/Menus/Help.png"            , 1280, 780, true);
	uiHelpS2      = CreateSprite( "./images/Menus/Help2.png"           , 1280, 780, true);
	uiHud         = CreateSprite( "./images/Menus/HUD.png"             , 1408, 858, true );

	uiCustomize   = CreateSprite( "./images/Menus/Text/Customize.png"  , 260 , 52 , true );
	uiHelp        = CreateSprite( "./images/Menus/Text/Help.png"       , 260 , 52 , true );
	uiHighScores  = CreateSprite( "./images/Menus/Text/HighScores.png" , 260 , 52 , true );
	uiOptions     = CreateSprite( "./images/Menus/Text/Options.png"    , 260 , 52 , true );
	uiSurvival    = CreateSprite( "./images/Menus/Text/Survival.png"   , 260 , 52 , true );
	uiSelected    = CreateSprite( "./images/Menus/Selected.png"        , 280 , 224, true );

	uiLogo        = CreateSprite( "./images/Menus/Logo.png"            , 128, 128, true );
	uiLogoAIE     = CreateSprite( "./images/Menus/AIE.png"             , 214, 128, true );

	uiBar        = CreateSprite( "./images/Menus/items/bar.png"        , 392 , 12 , true );
	uiSlider     = CreateSprite( "./images/Menus/items/Slider.png"     , 10  , 16, true );
}

void DrawSplashScreen(double dt){
	////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/8;
	dVecY = (iMouseY - (iScreenHeightHalf))/8;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	////calculate Offsets                      
	dVecX = (iMouseX - (iScreenWidthHalf))/64;
	dVecY = (iMouseY - (iScreenHeightHalf))/64;
	////DrawTitle
	DrawImage(uiHeader,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiLogo,iScreenWidthHalf*1.6-dVecX,iScreenHeightHalf*1.5-dVecY,0);
	DrawImage(uiLogoAIE,iScreenWidthHalf*0.4-dVecX,iScreenHeightHalf*1.5-dVecY,0);
	dTimer+=dt;
	////Goto MainMenu
	if (dTimer>3){
		eCurrentState = GS_MAIN_MENU;
		dTimer=0;
	}
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
}
void DrawMainMenu(){
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
	dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("QUIT",(iScreenWidthHalf*0.2)-36-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			bRunning = false;
		}
	}
	////HELP
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	DrawImage(uiHex,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2-dVecY,0);
	DrawImage(uiHelp,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2-dVecY,0);
	DrawImage(uiHeader,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
	if (CheckMouse((iScreenWidthHalf)-140,(iScreenWidthHalf)+140,(iScreenHeightHalf*1.2)-112,(iScreenHeightHalf*1.2)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_HELP_MENU;
		}
	}
	////SURVIVAL
	DrawImage(uiHex,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	DrawImage(uiSurvival,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_GAME_SCREEN;
		}
	}
	////OPTIONS
	DrawImage(uiHex,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawImage(uiOptions,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_OPTIONS_MENU;
		}
	}
	////MULTIPLAYER
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	DrawImage(uiHighScores,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_HIGHSCORES_MENU;
		}
	}
	////CUSTOMIZE
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawImage(uiCustomize,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_CUSTOMIZE_MENU;
		}
	}
	////Draw Title
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawHighscoresMenu(){
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
////OptionsMenu
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
    dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	DrawHighscores(dVecX,dVecY);
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawCustomizeMenu(){
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
	//vectors
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
	dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	//header
	DrawImage(uiHeader,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	////Player
	DrawImage(uiHex,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2-dVecY,0);
    DrawString("Player" ,(iScreenWidthHalf)-64-dVecX,(iScreenHeightHalf*1.2)-16-dVecY);
	DrawHudPlayer((iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2+48)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf)-140,(iScreenWidthHalf)+140,(iScreenHeightHalf*1.2)-112,(iScreenHeightHalf*1.2)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.2-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_PLAYER_SELECT_MENU;
		}
	}
	////Weapon1
	DrawImage(uiHex,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	DrawString("Weapon 1" ,(iScreenWidthHalf-220)-64-dVecX,(iScreenHeightHalf*1.2-120)-16-dVecY);
	DrawHudWeapon(*sWeapon1,(iScreenWidthHalf-220)-dVecX,(iScreenHeightHalf*1.2-120)+48-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sCurrentWeapon = &sWeapon1;
			eCurrentState = GS_GUN_SELECT_MENU;
			curwep = 1;
		}
	}
	////Weapon2
	DrawImage(uiHex,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawString("Weapon 2" ,(iScreenWidthHalf-220)-64-dVecX,(iScreenHeightHalf*1.2+120)-16-dVecY);
	DrawHudWeapon(*sWeapon2,(iScreenWidthHalf-220)-dVecX,(iScreenHeightHalf*1.2+120)+48-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sCurrentWeapon = &sWeapon2;
			eCurrentState = GS_GUN_SELECT_MENU;
			curwep = 2;
		}
	}
	////Weapon3
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
	DrawString("Weapon 3" ,(iScreenWidthHalf+220)-64-dVecX,(iScreenHeightHalf*1.2-120)-16-dVecY);
	DrawHudWeapon(*sWeapon3,(iScreenWidthHalf+220)-dVecX,(iScreenHeightHalf*1.2-120)+48-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sCurrentWeapon = &sWeapon3;
			eCurrentState = GS_GUN_SELECT_MENU;
			curwep = 3;
		}
	}
	////Weapon4
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawString("Weapon 4" ,(iScreenWidthHalf+220)-64-dVecX,(iScreenHeightHalf*1.2+120)-16-dVecY);
	DrawHudWeapon(*sWeapon4,(iScreenWidthHalf+220)-dVecX,(iScreenHeightHalf*1.2+120)+48-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sCurrentWeapon = &sWeapon4;
			eCurrentState = GS_GUN_SELECT_MENU;
			curwep = 4;
		}
	}
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawGunSelectMenu(){
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
	//vectors
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
	dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	//header
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2)*0.15-dVecY,0);
	//back
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_CUSTOMIZE_MENU;
		}
	}
	//DrawHudWeapon
	DrawImage(uiHex,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.5)-128-dVecY,0);
	DrawHudPlayer((iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.5)-128-dVecY);
	////HEXS
	MoveSprite(uiHex,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.5)-dVecY);
	DrawSprite(uiHex);
    DrawString("LMG" ,(iScreenWidthHalf)-32-dVecX,(iScreenHeightHalf*1.5)-32-dVecY);
	DrawHudWeapon(sGunLMG,(iScreenWidthHalf)+16-dVecX,(iScreenHeightHalf*1.5)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf)-70,(iScreenWidthHalf)+70,(iScreenHeightHalf*1.5)-56,(iScreenHeightHalf*1.5)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.5)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunLMG;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunLMG;
					break;
				case 2:
					sWeapon2 = &sGunLMG;
					break;
				case 3:
					sWeapon3 = &sGunLMG;
					break;
				case 4:
					sWeapon4 = &sGunLMG;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
    DrawString("SMG" ,(iScreenWidthHalf-120)-32-dVecX,(iScreenHeightHalf*1.5-60)-32-dVecY);
	DrawHudWeapon(sGunSMG,(iScreenWidthHalf-120)+16-dVecX,(iScreenHeightHalf*1.5-60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-120)-70,(iScreenWidthHalf-120)+70,(iScreenHeightHalf*1.5-60)-56,(iScreenHeightHalf*1.5-60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunSMG;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunSMG;
					break;
				case 2:
					sWeapon2 = &sGunSMG;
					break;
				case 3:
					sWeapon3 = &sGunSMG;
					break;
				case 4:
					sWeapon4 = &sGunSMG;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
    DrawString("AK47" ,(iScreenWidthHalf-120)-32-dVecX,(iScreenHeightHalf*1.5+60)-32-dVecY);
	DrawHudWeapon(sGunAK,(iScreenWidthHalf-120)+16-dVecX,(iScreenHeightHalf*1.5+60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-120)-70,(iScreenWidthHalf-120)+70,(iScreenHeightHalf*1.5+60)-56,(iScreenHeightHalf*1.5+60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunAK;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunAK;
					break;
				case 2:
					sWeapon2 = &sGunAK;
					break;
				case 3:
					sWeapon3 = &sGunAK;
					break;
				case 4:
					sWeapon4 = &sGunAK;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
    DrawString("AK47u" ,(iScreenWidthHalf+120)-54-dVecX,(iScreenHeightHalf*1.5-60)-32-dVecY);
	DrawHudWeapon(sGunAKu,(iScreenWidthHalf+120)+16-dVecX,(iScreenHeightHalf*1.5-60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+120)-70,(iScreenWidthHalf+120)+70,(iScreenHeightHalf*1.5-60)-56,(iScreenHeightHalf*1.5-60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunAKu;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunAKu;
					break;
				case 2:
					sWeapon2 = &sGunAKu;
					break;
				case 3:
					sWeapon3 = &sGunAKu;
					break;
				case 4:
					sWeapon4 = &sGunAKu;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
    DrawString("Assult" ,(iScreenWidthHalf+120)-64-dVecX,(iScreenHeightHalf*1.5+60)-32-dVecY);
	DrawHudWeapon(sGunAssult,(iScreenWidthHalf+120)+16-dVecX,(iScreenHeightHalf*1.5+60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+120)-70,(iScreenWidthHalf+120)+70,(iScreenHeightHalf*1.5+60)-56,(iScreenHeightHalf*1.5+60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunAssult;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunAssult;
					break;
				case 2:
					sWeapon2 = &sGunAssult;
					break;
				case 3:
					sWeapon3 = &sGunAssult;
					break;
				case 4:
					sWeapon4 = &sGunAssult;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf+240)-dVecX,(iScreenHeightHalf*1.5)-dVecY,0);
    DrawString("LAW" ,(iScreenWidthHalf+240)-32-dVecX,(iScreenHeightHalf*1.5)-32-dVecY);
	DrawHudWeapon(sGunLAW,(iScreenWidthHalf+240)+16-dVecX,(iScreenHeightHalf*1.5)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+240)-70,(iScreenWidthHalf+240)+70,(iScreenHeightHalf*1.5)-56,(iScreenHeightHalf*1.5)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf+240)-dVecX,(iScreenHeightHalf*1.5)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunLAW;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunLAW;
					break;
				case 2:
					sWeapon2 = &sGunLAW;
					break;
				case 3:
					sWeapon3 = &sGunLAW;
					break;
				case 4:
					sWeapon4 = &sGunLAW;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf-240)-dVecX,(iScreenHeightHalf*1.5)-dVecY,0);
    DrawString("LMG2" ,(iScreenWidthHalf-240)-38-dVecX,(iScreenHeightHalf*1.5)-16-dVecY,90);
	DrawHudWeapon(sGunLMG2,(iScreenWidthHalf-240)+8-dVecX,(iScreenHeightHalf*1.5)+32-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-240)-70,(iScreenWidthHalf-240)+70,(iScreenHeightHalf*1.5)-56,(iScreenHeightHalf*1.5)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf-240)-dVecX,(iScreenHeightHalf*1.5)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunLMG2;			
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunLMG2;
					break;
				case 2:
					sWeapon2 = &sGunLMG2;
					break;
				case 3:
					sWeapon3 = &sGunLMG2;
					break;
				case 4:
					sWeapon4 = &sGunLMG2;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf-360)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
    DrawString("LMG3" ,(iScreenWidthHalf-360)-48-dVecX,(iScreenHeightHalf*1.5-60)-32-dVecY);
	DrawHudWeapon(sGunLMG3,(iScreenWidthHalf-360)+16-dVecX,(iScreenHeightHalf*1.5-60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-360)-70,(iScreenWidthHalf-360)+70,(iScreenHeightHalf*1.5-60)-56,(iScreenHeightHalf*1.5-60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf-360)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunLMG3;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunLMG3;
					break;
				case 2:
					sWeapon2 = &sGunLMG3;
					break;
				case 3:
					sWeapon3 = &sGunLMG3;
					break;
				case 4:
					sWeapon4 = &sGunLMG3;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf-360)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
    DrawString("RPG" ,(iScreenWidthHalf-360)-32-dVecX,(iScreenHeightHalf*1.5+60)-32-dVecY);
	DrawHudWeapon(sGunRPG,(iScreenWidthHalf-360)+16-dVecX,(iScreenHeightHalf*1.5+60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf-360)-70,(iScreenWidthHalf-360)+70,(iScreenHeightHalf*1.5+60)-56,(iScreenHeightHalf*1.5+60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf-360)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunRPG;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunRPG;
					break;
				case 2:
					sWeapon2 = &sGunRPG;
					break;
				case 3:
					sWeapon3 = &sGunRPG;
					break;
				case 4:
					sWeapon4 = &sGunRPG;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf+360)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
    DrawString("RPG2" ,(iScreenWidthHalf+360)-32-dVecX,(iScreenHeightHalf*1.5-60)-32-dVecY);
	DrawHudWeapon(sGunRPG2,(iScreenWidthHalf+360)+16-dVecX,(iScreenHeightHalf*1.5-60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+360)-70,(iScreenWidthHalf+360)+70,(iScreenHeightHalf*1.5-60)-56,(iScreenHeightHalf*1.5-60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf+360)-dVecX,(iScreenHeightHalf*1.5-60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunRPG2;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunRPG2;
					break;
				case 2:
					sWeapon2 = &sGunRPG2;
					break;
				case 3:
					sWeapon3 = &sGunRPG2;
					break;
				case 4:
					sWeapon4 = &sGunRPG2;
					break;
				}
			}
		}
	}
	DrawImage(uiHex,(iScreenWidthHalf+360)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
    DrawString("Sniper" ,(iScreenWidthHalf+360)-54-dVecX,(iScreenHeightHalf*1.5+60)-32-dVecY);
	DrawHudWeapon(sGunSniper,(iScreenWidthHalf+360)+16-dVecX,(iScreenHeightHalf*1.5+60)+16-dVecY,90);
	if (CheckMouse((iScreenWidthHalf+360)-70,(iScreenWidthHalf+360)+70,(iScreenHeightHalf*1.5+60)-56,(iScreenHeightHalf*1.5+60)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf+360)-dVecX,(iScreenHeightHalf*1.5+60)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			sTempWeapon = &sGunSniper;
			if (!CheckWeapons()){
				switch (curwep){
				case 1:
					sWeapon1 = &sGunSniper;
					break;
				case 2:
					sWeapon2 = &sGunSniper;
					break;
				case 3:
					sWeapon3 = &sGunSniper;
					break;
				case 4:
					sWeapon4 = &sGunSniper;
					break;
				}
			}
		}
	}
////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_CUSTOMIZE_MENU;
		curwep = 0;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawPlayerSelectMenu(){
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
	//vectors
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
	dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	//header
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2)*0.15-dVecY,0);
	//player
	DrawImage(uiHex,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2)-dVecY,0);
	DrawHudPlayer((iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2)-dVecY);
	//back
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_CUSTOMIZE_MENU;
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////HEXS
		DrawImage(uiHex,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2+120)-dVecY,0);
		DrawImage(sPlayerLegs,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2+120)-dVecY,0);
		if (CheckMouse((iScreenWidthHalf)-70,(iScreenWidthHalf)+70,(iScreenHeightHalf*1.2+120)-56,(iScreenHeightHalf*1.2+120)+56)){
			DrawImage(uiSelected,(iScreenWidthHalf)-dVecX,(iScreenHeightHalf*1.2+120)-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				MenuCheck=1;
				RollPlayerPart(sUVPlayerLegs);
			}
		}
		DrawImage(uiHex,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
		DrawImage(sPlayerBodys,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
		if (CheckMouse((iScreenWidthHalf-120)-70,(iScreenWidthHalf-120)+70,(iScreenHeightHalf*1.2-60)-56,(iScreenHeightHalf*1.2-60)+56)){
			DrawImage(uiSelected,(iScreenWidthHalf-120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				MenuCheck=1;
				RollPlayerPart(sUVPlayerBodys);
			}
		}
		DrawImage(uiHex,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
		DrawImage(sPlayerHeads,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
		if (CheckMouse((iScreenWidthHalf+120)-70,(iScreenWidthHalf+120)+70,(iScreenHeightHalf*1.2-60)-56,(iScreenHeightHalf*1.2-60)+56)){
			DrawImage(uiSelected,(iScreenWidthHalf+120)-dVecX,(iScreenHeightHalf*1.2-60)-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				MenuCheck=1;
				RollPlayerPart(sUVPlayerHeads);
			}
		}
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_CUSTOMIZE_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
/*
void DrawMapSelectMenu(){
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
////MapSelectMenu
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
    dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
////Maps
	DrawImage(uiMapOffice,(dOffX-1032)-dVecX,dOffY-dVecY,0);
	DrawImage(uiMapOffice1,(dOffX-516)-dVecX,dOffY-dVecY,0);
	DrawImage(uiMapOffice2,(dOffX)-dVecX,dOffY-dVecY,0);
	DrawImage(uiMapOffice3,(dOffX+516)-dVecX,dOffY-dVecY,0);
	DrawImage(uiMapOffice4,(dOffX+1032)-dVecX,dOffY-dVecY,0);
////TEMP
	if (IsKeyDown(KEY_LEFT) && MenuCheck==0 && dOffX>iScreenWidthHalf-1032){
		MenuCheck=1;
		dOffX-=516;
	}
	if (IsKeyDown(KEY_RIGHT) && MenuCheck==0 && dOffX<iScreenWidthHalf+1032){
		MenuCheck=1;
		dOffX+=516;
	}
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)){
		MenuCheck=0;
	}
}
*/
void DrawOptionsMenu(){
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
////OptionsMenu
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
    dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
/////hex1 - dynamicmove
	DrawImage(uiHex,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2-dVecY,0);
    DrawString("Dynamic" ,(iScreenWidthHalf)-64-dVecX,(iScreenHeightHalf*1.1)-16-dVecY);
    DrawString("Movement",(iScreenWidthHalf)-76-dVecX,(iScreenHeightHalf*1.2)-16-dVecY);
    if (usevariablemovement == true){
        DrawString("On",(iScreenWidthHalf)-16-dVecX,(iScreenHeightHalf*1.3)-16-dVecY);
    }else{
        DrawString("Off",(iScreenWidthHalf)-24-dVecX,(iScreenHeightHalf*1.3)-16-dVecY);
    }
	if (CheckMouse((iScreenWidthHalf)-140,(iScreenWidthHalf)+140,(iScreenHeightHalf*1.2)-112,(iScreenHeightHalf*1.2)+112)){
		DrawImage(uiSelected,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
            if (usevariablemovement == true){usevariablemovement = false;}else{usevariablemovement = true;}
		}
	}
////hex2 - DebugMode
	DrawImage(uiHex,(iScreenWidthHalf-220)-dVecX,(iScreenHeightHalf*1.2-120)-dVecY,0);
    DrawString("Debug" ,(iScreenWidthHalf-220)-48-dVecX,(iScreenHeightHalf*1.1-120)-16-dVecY);
    DrawString("Mode",(iScreenWidthHalf-220)-40-dVecX,(iScreenHeightHalf*1.2-120)-16-dVecY);
    if (bDebug == true){
        DrawString("On",(iScreenWidthHalf-220)-16-dVecX,(iScreenHeightHalf*1.3-120)-16-dVecY);
    }else{
        DrawString("Off",(iScreenWidthHalf-220)-24-dVecX,(iScreenHeightHalf*1.3-120)-16-dVecY);
    }
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,(iScreenWidthHalf-220)-dVecX,(iScreenHeightHalf*1.2-120)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
            if (bDebug == true){bDebug = false;}else{bDebug = true;}
		}
	}
////hex3
	DrawImage(uiHex,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawString("GodMode",(iScreenWidthHalf-220)-70-dVecX,(iScreenHeightHalf*1.2+120)-16-dVecY);
    if (bGodMode == true){
        DrawString("On",(iScreenWidthHalf-220)-16-dVecX,(iScreenHeightHalf*1.3+120)-16-dVecY);
    }else{
        DrawString("Off",(iScreenWidthHalf-220)-24-dVecX,(iScreenHeightHalf*1.3+120)-16-dVecY);
    }
	if (CheckMouse((iScreenWidthHalf-220)-140,(iScreenWidthHalf-220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf-220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			if (bGodMode == true){bGodMode = false;}else{bGodMode = true;}
		}
	}
////hex4
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
    DrawString("Pickups",(iScreenWidthHalf+220)-76-dVecX,(iScreenHeightHalf*1.2-120)-16-dVecY);
    DrawInt(iPickups,(iScreenWidthHalf+220)-dVecX,(iScreenHeightHalf*1.2-120)+16-dVecY);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2-120)-112,(iScreenHeightHalf*1.2-120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2-120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			if (iPickups<10){iPickups++;}else{iPickups=1;}
		}
	}
////hex5
	DrawImage(uiHex,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
	DrawString("Enemies",(iScreenWidthHalf+220)-76-dVecX,(iScreenHeightHalf*1.2+120)-16-dVecY);
    DrawInt(iEnemies,(iScreenWidthHalf+220)-dVecX,(iScreenHeightHalf*1.2+120)+16-dVecY);
	if (CheckMouse((iScreenWidthHalf+220)-140,(iScreenWidthHalf+220)+140,(iScreenHeightHalf*1.2+120)-112,(iScreenHeightHalf*1.2+120)+112)){
		DrawImage(uiSelected,iScreenWidthHalf+220-dVecX,iScreenHeightHalf*1.2+120-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			if (iEnemies<10){iEnemies++;}else{iEnemies=1;}
		}
	}
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawHelpMenu(){
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
////OptionsMenu
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
    dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
    DrawImage(uiHelpS,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);//Draw selected Highlighter Image
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_HELP_MENU2;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawHelpMenu2(){
////MOUSE
	GetMouseLocation(iMouseX,iMouseY);
	////BACKGROUND
	DrawImage(uiBackground,0,0,0);
	////Overlay
	dVecX = (iMouseX - (iScreenWidthHalf))/4;
	dVecY = (iMouseY - (iScreenHeightHalf))/4;
	DrawImage(uiBackground2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	DrawImage(uiBackground2,iScreenWidthHalf-(dVecX*2),iScreenHeightHalf-(dVecY*2),180);
	//vectors
////OptionsMenu
	dVecX = (iMouseX - (iScreenWidthHalf))/16;
    dVecY = (iMouseY - (iScreenHeightHalf*1.2))/16;
	DrawImage(uiHeader,(iScreenWidthHalf)-dVecX,iScreenHeightHalf*1.2*0.15-dVecY,0);
    DrawImage(uiHelpS2,iScreenWidthHalf-dVecX,iScreenHeightHalf-dVecY,0);
	//back
	SetSpriteScale(uiHex,size2[0],size2[1]);
	SetSpriteScale(uiSelected,size2[0],size2[1]);
	DrawImage(uiHex,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
	DrawString("BACK",(iScreenWidthHalf*0.2)-40-dVecX,(iScreenHeightHalf*0.2)-16-dVecY);
	if (CheckMouse((iScreenWidthHalf*0.2)-dVecX-70,(iScreenWidthHalf*0.2)-dVecX+70,(iScreenHeightHalf*0.2)-56,(iScreenHeightHalf*0.2)+56)){
		DrawImage(uiSelected,(iScreenWidthHalf*0.2)-dVecX,(iScreenHeightHalf*0.2)-dVecY,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			eCurrentState = GS_MAIN_MENU;
		}
	}
	SetSpriteScale(uiHex,size1[0],size1[1]);
	SetSpriteScale(uiSelected,size1[0],size1[1]);
	////TEMP
	if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
		MenuCheck=1;
		eCurrentState = GS_MAIN_MENU;
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1)){
		MenuCheck=0;
	}
}
void DrawGameMenu(){
////DrawWeaponChanger
	GetMouseLocation(iMouseX,iMouseY);
		////Resize Images
		SetSpriteScale(uiHex,size2[0],size2[1]);
		SetSpriteScale(uiSelected,size2[0],size2[1]);
		////Vector
		dVecX = (iMouseX - (iScreenWidthHalf))/32;
		dVecY = (iMouseY - (iScreenHeightHalf))/32;
	if (GetMouseButtonDown(MOUSE_BUTTON_2)){
		DrawImage(uiHex,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.25-dVecY,0);
		DrawHudWeapon(*sWeapon1,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.25-dVecY,90);
		if (CheckMouse((iScreenWidthHalf)-70,(iScreenWidthHalf)+70,(iScreenHeightHalf*1.25)-56,(iScreenHeightHalf*1.25)+56)){
			DrawImage(uiSelected,iScreenWidthHalf-dVecX,iScreenHeightHalf*1.25-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				sCurrentWeapon = &sWeapon1;
				MenuCheck=1;
			}
		}
		DrawImage(uiHex,iScreenWidthHalf*1.16-dVecX,iScreenHeightHalf-dVecY,0);
		DrawHudWeapon(*sWeapon2,iScreenWidthHalf*1.16-dVecX,iScreenHeightHalf-dVecY,90);
		if (CheckMouse((iScreenWidthHalf*1.16)-70,(iScreenWidthHalf*1.16)+70,(iScreenHeightHalf)-56,(iScreenHeightHalf)+56)){
			DrawImage(uiSelected,iScreenWidthHalf*1.16-dVecX,iScreenHeightHalf-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				sCurrentWeapon = &sWeapon2;
				MenuCheck=1;
			}
		}
		DrawImage(uiHex,iScreenWidthHalf*0.83-dVecX,iScreenHeightHalf-dVecY,0);
		DrawHudWeapon(*sWeapon3,iScreenWidthHalf*0.83-dVecX,iScreenHeightHalf-dVecY,90);
		if (CheckMouse((iScreenWidthHalf*0.83)-70,(iScreenWidthHalf*0.83)+70,(iScreenHeightHalf)-56,(iScreenHeightHalf)+56)){
			DrawImage(uiSelected,iScreenWidthHalf*0.83-dVecX,iScreenHeightHalf-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				sCurrentWeapon = &sWeapon3;
				MenuCheck=1;
			}
		}
		DrawImage(uiHex,iScreenWidthHalf-dVecX,iScreenHeightHalf*0.75-dVecY,0);
		DrawHudWeapon(*sWeapon4,iScreenWidthHalf-dVecX,iScreenHeightHalf*0.75-dVecY,90);
		if (CheckMouse((iScreenWidthHalf)-70,(iScreenWidthHalf)+70,(iScreenHeightHalf*0.75)-56,(iScreenHeightHalf*0.75)+56)){
			DrawImage(uiSelected,iScreenWidthHalf-dVecX,iScreenHeightHalf*0.75-dVecY,0);
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
				sCurrentWeapon = &sWeapon4;
				MenuCheck=1;
			}
		}
	}
	if (!GetMouseButtonDown(MOUSE_BUTTON_1) && IsKeyDown('`') && MenuCheck==0){
		MenuCheck=1;
		if (bDebug == true){bDebug = false;}else{bDebug = true;}
	}
////Draw HUD
	DrawImage(uiHud,iScreenWidthHalf+dVecX,iScreenHeightHalf+dVecY,0);

	DrawAmmo(**sCurrentWeapon,dVecX,dVecY);
	SetSpriteUVCoordinates(uiBar,0,0,1,1);

	DrawImage(uiBar,(iScreenWidthHalf*0.2)+dVecX,iScreenHeightHalf*1.8+dVecY,0);
	DrawImage(uiSlider,(310*(dEnergy/dMaxEnergy))+dVecX,iScreenHeightHalf*1.8+dVecY,0);

	DrawString("HEalth",iScreenWidthHalf*0.15+dVecX,iScreenHeightHalf*1.85+dVecY);
	DrawInt(iPlayerHealth,iScreenWidthHalf*0.35+dVecX,iScreenHeightHalf*1.85+dVecY);
	DrawString("Kills",iScreenWidthHalf*0.2+dVecX,iScreenHeightHalf*0.05+dVecY);
	DrawInt(iKills,iScreenWidthHalf*0.25+dVecX,iScreenHeightHalf*0.15+dVecY);
	DrawString("Hits MissEs",iScreenWidthHalf*1.6+dVecX,iScreenHeightHalf*0.05+dVecY);
	DrawInt(iHits,iScreenWidthHalf*1.6+dVecX,iScreenHeightHalf*0.15+dVecY);
	DrawInt(iMiss,iScreenWidthHalf*1.75+dVecX,iScreenHeightHalf*0.15+dVecY);
	if (!GetMouseButtonDown(MOUSE_BUTTON_1) && !IsKeyDown('`')){
		MenuCheck=0;
	}
}

void DestroyMenu(){
	DestroySprite(uiHex);
	DestroySprite(uiHeader);
	DestroySprite(uiBackground);
	DestroySprite(uiBackground2);
	DestroySprite(uiHelpS);
	DestroySprite(uiHud);
	DestroySprite(uiCustomize);
	DestroySprite(uiHelp);
	DestroySprite(uiHelpS2);
	DestroySprite(uiHighScores);
	DestroySprite(uiOptions);
	DestroySprite(uiSurvival);
	DestroySprite(uiSelected);
	DestroySprite(uiLogo);
	DestroySprite(uiLogoAIE);
	DestroySprite(uiBar);
	DestroySprite(uiSlider);
	DestroySprite(uiHex);
}
/*assignment3
void DrawMenuItem(float x, float y,float size[1],int action){
	//back
	SetSpriteScale(uiHex,size[0],size[1]);
	SetSpriteScale(uiSelected,size[0],size[1]);
	DrawImage(uiHex,x,y,0);
	DrawString("QUIT",x,y);
	if (CheckMouse(x-70,x+70,y-70,y+70)){
		DrawImage(uiSelected,x,y,0);
		if (GetMouseButtonDown(MOUSE_BUTTON_1) && MenuCheck==0){
			MenuCheck=1;
			switch (action){
			case 0:
				eCurrentState = GS_MAIN_MENU;
				break;
			}
		}
	}
}
*/