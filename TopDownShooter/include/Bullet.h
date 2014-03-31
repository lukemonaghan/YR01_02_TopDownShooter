/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//																			Brief:		Sets up the Bullets
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef Bul
#define Bul
#include <vector>
#include "globals.h"
#include "ai.h"

extern std::vector <bullet> vBullets;

void LoadBullets();

bullet CreateBullet(float px, float py,sfPosition map, float dir,float speed,float range,int parid,int damage,int spread);

void DrawBullet(std::vector<bullet> vbul);
bullet UpdateBullet(bullet bul,sfPosition map,float dt);
void CreateBullet(bullet bul,sfPosition map);
std::vector<bullet> UpdateBullets(std::vector<bullet> vbul,std::vector<instance> &vnpc,sfPosition map,float dt);

void DestroyBullet();

#endif