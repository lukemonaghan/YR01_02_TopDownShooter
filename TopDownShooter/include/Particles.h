////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Sets up all functions to do with particles
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _part
#define _part
#include "globals.h"
#include <vector>

extern unsigned int uiParticlesAmount;
extern unsigned int uiBlood,uiSpark,uiSmoke,uiExplosion;
extern std::vector <particle> vParticles;

void LoadParticles();
particle CreateParticles(unsigned int spr,sfPosition map, float x, float y,float len, float speed,float dir,int spread);
particle UpdateParticle(particle par,sfPosition map,float dt);
std::vector<particle> UpdateParticles(std::vector<particle> par,std::vector<instance> &vnpc,sfPosition map,float dt);
void DestroyParticle();
#endif