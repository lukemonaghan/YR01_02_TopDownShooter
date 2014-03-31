////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																			Author:		Luke Monaghan
//																			Date:		22/03/2013
//																			Brief:		Create, draw, and use of Highscores
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//highscores
#include "AIE.h"
#include "globals.h"
#include "HighScores.h"
#include "FileManagement.h"

#include <vector>
#include <algorithm>
//create the highscores vector
std::vector <ScoreTableInstance> vHighScores;
//compair the two scores in the vector
bool compareKills(const ScoreTableInstance &a, const ScoreTableInstance &b)
{
	return a.iKills > b.iKills;
}
//add a score
void AddHighscore(int kills,int miss, int hits){
	if (kills>0){
		ScoreTableInstance score;
		score.iKills  = kills;
		score.iMisses = miss;
		score.iHits   = hits;
		vHighScores.push_back(score);
		std::sort (vHighScores.begin(), vHighScores.end(), compareKills);
		std::vector<ScoreTableInstance>::iterator   v = vHighScores.begin();
		//limit it to 10 scores
		while (vHighScores.size()>10){
			vHighScores.erase(vHighScores.end()-1);
		}
	}
}
//draw the scores
void DrawHighscores(double x, double y){
	DrawString("Kills",iScreenWidthHalf-256-x ,192-y );
	DrawString("Miss" ,iScreenWidthHalf-16-x  ,192-y );
	DrawString("Hits" ,iScreenWidthHalf+224-x  ,192-y );
	std::vector<ScoreTableInstance>::iterator   v = vHighScores.begin();
	int i = 0;
	while (v!=vHighScores.end()) {
		ScoreTableInstance vScore = *v;
		DrawInt(vScore.iKills  ,iScreenWidthHalf-256-x,224+(32*i)-y);
		DrawInt(vScore.iMisses,iScreenWidthHalf-x   , 224+(32*i)-y);
		DrawInt(vScore.iHits  ,iScreenWidthHalf+224-x, 224+(32*i)-y);
		i++;
		v++;
	}
}