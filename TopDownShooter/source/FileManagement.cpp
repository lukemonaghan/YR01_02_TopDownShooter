#include <fstream>
#include <string>
#include <sstream>

#include "Highscores.h"
#include "globals.h"
#include "Weapon.h"
#include "player.h"
#include "pickups.h"
#include "ai.h"

std::string toString(float number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
//load highscores
void LoadHighscores(){
	std::ifstream is("highscores.ttg");
	int a,b,c;
	if (is) { 
		while(!is.eof()){
			is>>a;
			is>>b;
			is>>c;
			AddHighscore(a, b, c);
		}
	}
    is.close();
}
//save highscores
void SaveHighscores(){
	std::ofstream os("highscores.ttg");
	std::vector<ScoreTableInstance>::iterator v = vHighScores.begin();
	while (v!=vHighScores.end()) {
		ScoreTableInstance vScore = *v;
			os<<toString(vScore.iKills)+" ";
			os<<toString(vScore.iMisses)+" ";
			if (v==vHighScores.end()-1){
			os<<toString(vScore.iHits);
			}else{
			os<<toString(vScore.iHits)+"\n";
			}
		v++;
	}
   os.close();
}
//load highscores
void LoadSettings(){
	std::ifstream is("settings.ttg");
	int temp;
	if (is) { 
		while(!is.eof()){
			is>>bDebug;
			is>>usevariablemovement;
			//player
			is>>temp;
			SetPlayerPartByID(sUVPlayerHeads,temp);
			is>>temp;
			SetPlayerPartByID(sUVPlayerBodys,temp);
			is>>temp;
			SetPlayerPartByID(sUVPlayerLegs,temp);
			//weapons
			is>>temp;
			SetWeaponByID(temp,&sWeapon1);
			is>>temp;
			SetWeaponByID(temp,&sWeapon2);
			is>>temp;
			SetWeaponByID(temp,&sWeapon3);
			is>>temp;
			SetWeaponByID(temp,&sWeapon4);
			is>>iPickups;
			is>>iEnemies;
			is>>bGodMode;if (bGodMode<0 || bGodMode>1){bGodMode=0;}
			//is>>
		}
	}
    is.close();
}
//save highscores
void SaveSettings(){
	std::ofstream os("settings.ttg");
	os<<toString(bDebug)+"\n";
	os<<toString(usevariablemovement)+"\n";
	//player
	os<<toString(GetPlayerPartID(sUVPlayerHeads))+"\n";
	os<<toString(GetPlayerPartID(sUVPlayerBodys))+"\n";
	os<<toString(GetPlayerPartID(sUVPlayerLegs))+"\n";
	//weapons
	os<<toString(GetWeaponID(*sWeapon1))+"\n";
	os<<toString(GetWeaponID(*sWeapon2))+"\n";
	os<<toString(GetWeaponID(*sWeapon3))+"\n";
	os<<toString(GetWeaponID(*sWeapon4))+"\n";
	//pickups and enemies
	os<<toString(iPickups)+"\n";
	os<<toString(iEnemies)+"\n";
	os<<toString(bGodMode);
   os.close();
}