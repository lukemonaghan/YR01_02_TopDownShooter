/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//																			Brief:		Sets up all functions to do with AI																	  \\
/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef _AI
#define _AI
#include <vector>
#include "Bullet.h"
#include "globals.h"

extern unsigned int iEnemies;

void LoadInstance();
instance CreateInstance(float x, float y, float dir,float speed,int health,float px, float py);

void DrawNPC(std::vector<instance> vbul);
instance UpdateNPCxy(instance ins,sfPosition map,float px, float py,sfPosition world,float dt);
void UpdateNPC(std::vector<instance> &vins,sfPosition map,float px, float py,sfPosition world,float dt);

instance TakeHealth(instance ins,int damage,bool &dead);
void CheckNPC(std::vector<instance> &vins,float x, float y,int damage,bool &check);

void DestroyInstance();

#endif