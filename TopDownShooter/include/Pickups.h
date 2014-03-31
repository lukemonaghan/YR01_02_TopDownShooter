/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//																			Author:		Luke Monaghan																						  \\
//																			Date:		22/03/2013																						      \\
//																			Brief:		Sets up all functions to do with ItemDrops   														  \\
/////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef _PICKUPS
#define _PICKUPS
#include <vector>
#include "globals.h"

extern unsigned int iPickups;
extern unsigned int uiHealth,uiAmmo,uiFloorItems;

extern 	std::vector <sItem> vItems;

void LoadItems();
sItem CreateItem(unsigned int spr,double x, double y, int dir,double subimg,int index, int iind);

void CreateItems(int x, int y);
void DrawItems(std::vector<sItem> item,sfPosition stWorld);
void PickupItems(std::vector<sItem> &item, sfPosition stm, double x, double y);

void DestroyPickups();
#endif