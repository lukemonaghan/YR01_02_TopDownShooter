/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//																			Brief:		sets up all the global variables and functions														  \\
/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef _GLOBAL
#define _GLOBAL
//apparently extern is bad... but I didnt know how else to do it
extern struct siPosition{
	int x;
	int y;
};
extern struct sfPosition{
	float x;
	float y;
};
extern struct sTex{
	unsigned int uiSprite;
	float fIndex, fIndexOffset, fYIndex, fYIndexOffset, fAniTimer;
	int iIndex;
};
extern struct sVector2D{
	sfPosition Pos;
	float fDir,fLength,fSpread,fSpeed;
};
extern struct sItem{
	sfPosition Pos;
	sTex Tex;
	sVector2D Vec; 
};
extern struct particle{
	sfPosition Pos;
	sfPosition oPos;
	sfPosition tPos;
	sVector2D Vec;
	float timer;
	sTex Tex;
};
extern struct sWeapon{
	int iRange, iRecoil, iClips, iClipSize, iBullets, iReloadSpeed,iDamage,iID;
	double dSpeed,dShootSpeed, UVIndex;
};
extern struct bullet{
	sfPosition Pos;
	sfPosition oPos;
	sfPosition tPos;
	sVector2D Vec;
	sTex Tex;
	float dRange;
	int iDir,iDamage,iParID;
};
extern struct instance{
	sfPosition Pos;
	sfPosition tPos;
	sVector2D Vec;
	sTex Tex;
	int iHealth,iWall;
};
//all my variables(work into specific cpp's)
extern bool bRunning;
extern const int iScreenWidth;
extern const int iScreenHeight;
extern const int iScreenWidthHalf;
extern const int iScreenHeightHalf;
extern const int iMapWidth;
extern const int iMapHeight;
extern const float PI;

extern int iDirection;
extern bool bGodMode;
extern int bChkMap;

extern float dImage;
extern float dAnitimer;

extern char buffer[60];
extern bool usevariablemovement;
extern bool bDebug;

extern float iBladesRot;
//stats
extern int iKills;
extern int iMiss;
extern int iHits;
//Gamestates
typedef enum GameStates
{
	GS_SPLASH_SCREEN,
	GS_MAIN_MENU,
	GS_OPTIONS_MENU,
	GS_MAP_SELECT_MENU,
	GS_HIGHSCORES_MENU,
	GS_HELP_MENU,
	GS_HELP_MENU2,
	GS_CUSTOMIZE_MENU,
	GS_PLAYER_SELECT_MENU,
	GS_GUN_SELECT_MENU,
	GS_GAME_SCREEN,
	GS_END
}GameState;

extern GameState eCurrentState;

void DrawInt(int i,int w, int h);
void DrawImage(unsigned int s,const float x,const float y,int d);
void DrawImage(unsigned int s,const float x,const float y,int d,sfPosition map,int amount,int sep);
int Choose(int a, int b, int c, int d);

#endif