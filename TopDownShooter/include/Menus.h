////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Sets up the Menus
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MENU
#define _MENU

extern unsigned int uiBar,uiSlider;
extern double dVecX,dVecY;
extern int MenuCheck;

bool CheckMouse(int x1, int y1, int x2, int y2);

void DrawInt(int i,int w, int h);
void LoadMenu();
void DrawSplashScreen(double dt);
void DrawMainMenu();
void DrawHighscoresMenu();
void DrawCustomizeMenu();
void DrawGunSelectMenu();
void DrawPlayerSelectMenu();
//void DrawMapSelectMenu();
void DrawOptionsMenu();
void DrawHelpMenu();
void DrawHelpMenu2();
void DrawGameMenu();

void DestroyMenu();

#endif