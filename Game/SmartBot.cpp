#include "stdafx.h"
#include "SmartBot.h"


SmartBot::SmartBot(int playerid, int icon)
	: Player(playerid, icon)
{
}


SmartBot::~SmartBot()
{
}

int SmartBot::getPositionForColumn(BuildGameField * gamefield)
{
	setProbabilitysToZero();
	checkForPossibleWin(gamefield);
	checkForPossibleLose(gamefield);

	//Hier muss dan jeweils noch ein winningpathleft und right reingemacht werden (alle if abfragen)

	if (winningPathHorizontal != NoWinDetected && probabilityForColumn.at(winningPathHorizontal) == 100 && gamefield->canInsert(winningPathHorizontal + 1)) return winningPathHorizontal + 1;
	if (winningPathVertikalleft != NoWinDetected && probabilityForColumn.at(winningPathVertikalleft) == 100 && gamefield->canInsert(winningPathVertikalleft + 1)) return winningPathVertikalleft + 1;
	if (winningPathVertikalright != NoWinDetected && probabilityForColumn.at(winningPathVertikalright) == 100 && gamefield->canInsert(winningPathVertikalright + 1)) return winningPathVertikalright + 1;

	//Wenn ein unmittelbarer loose bevorsteht ohne das ein 100% win erreichbar ist wird der gegner blockiert 
	if (gamefield->canInsert(loosingPathHorizontal + 1) && loosingPathHorizontal != NoLossDetected) return loosingPathHorizontal+1;
	if (gamefield->canInsert(loosingPathVertikalright + 1) && loosingPathVertikalright != NoLossDetected) return loosingPathVertikalright+1;
	if (gamefield->canInsert(loosingPathVertikalleft + 1) && loosingPathVertikalleft != NoLossDetected) return loosingPathVertikalleft + 1;

	//wenn es eine 50 % chance gibt zu gewinnen
	if (winningPathVertikalright  != NoWinDetected && gamefield->canInsert(winningPathVertikalright +1)) return winningPathVertikalright+1;
	if (winningPathVertikalleft != NoWinDetected && gamefield->canInsert(winningPathVertikalleft + 1)) return winningPathVertikalleft+1;
	if (winningPathHorizontal != NoWinDetected && gamefield->canInsert(winningPathHorizontal + 1)) return winningPathHorizontal+1;

	//Wenn es keine Chance zum gewinnen gibt
		//Die Mitte für Column Heights ist bei 3, da sie von 0 beginnt
		if (gamefield->getColumnHeights(MITTE-1) >= 0) {
			//Hier wird die Mitte zum einwerfen genommen diese ist 4
			return MITTE;
		}
		else if(gamefield->getColumnHeights(2) >= 0)
		{
			//Links neben die Mitte
			return MITTE-1;
		}
		else if (gamefield->getColumnHeights(4) >= 0)
		{
			//Links neben die Mitte
			return MITTE +1;
		}
		else
		{
			//Wenn es keine möglichkeiten zum gewinnen gibt und links und rechts neben der Mitte alles voll ist
			return rand() % 7 + 1;
		}
	

}

void SmartBot::setProbabilitysToZero()
{
	for (int i = 0; i < 7; i++) {
		probabilityForColumn.at(i) = 0;
	}
}


void SmartBot::checkForPossibleWin(BuildGameField * gamefield)
{
	//Diagonalen Win maybe
	winningPathHorizontal = BothasChanceForWin(MoveUp , NoMoving, gamefield);

	//Wenn ein 100 % Win detected wurde soll er returnen 
	if (winningPathHorizontal != NoWinDetected && probabilityForColumn.at(winningPathHorizontal) == 100) {
		return;
	}
	winningPathVertikalright = BothasChanceForWin(NoMoving, MoveRight,gamefield);
	if (winningPathVertikalright != NoWinDetected && probabilityForColumn.at(winningPathVertikalright) == 100) {
		return;
	}
	winningPathVertikalleft = BothasChanceForWin(NoMoving, MoveLeft, gamefield);
}

void SmartBot::checkForPossibleLose(BuildGameField * gamefield)
{
	loosingPathHorizontal = EnemyhasChanceForWin(MoveUp, NoMoving, gamefield);
	loosingPathVertikalright = EnemyhasChanceForWin(NoMoving, MoveRight, gamefield);
	loosingPathVertikalleft = EnemyhasChanceForWin(NoMoving, MoveLeft, gamefield);
}

int SmartBot::BothasChanceForWin(int HeightMove, int WidthMove, BuildGameField * gamefield)
{
	int cloneWidth = 0;
	int cloneHeight = 0;

	for (int height = gamefield->getGamefieldHeight() - 1; height >= 0; height--) {

		for (int width = 0; width < gamefield->getGamefieldWidth(); width++) {

			cloneHeight = height;
			cloneWidth = width;

			winSmartBot = 1;

			while (cloneWidth < 7 && cloneHeight >= 0 && (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 2 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) == 2)) {

				winSmartBot++;
				cloneWidth += WidthMove;
				cloneHeight += HeightMove;

				if ((gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 2 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) == 1)) {
					probabilityForColumn.at(cloneWidth) = 0;
					winSmartBot = 1;
					break;
				}

				if ((cloneWidth >= 0 && cloneWidth < 7 && winSmartBot == 2 && HeightMove != 0) || (cloneWidth > 0 && cloneWidth < 6 && winSmartBot == 2 && gamefield->getColumnHeights(cloneWidth+WidthMove) == cloneHeight)) {
					//Wenn 2 übereinander sind wird die Wahrscheinlichkeit auf 50% gesetzt 
					probabilityForColumn.at(cloneWidth + WidthMove) = 50;
				}

				//Wenn vier Steine in einer Reihe waren
				if ((cloneWidth >= 0 && cloneWidth < 6 && winSmartBot >= 3 && gamefield->getColumnHeights(cloneWidth + WidthMove) == cloneHeight)
					|| (cloneWidth >= 0 && cloneWidth < 7 && winSmartBot >= 3 && HeightMove != 0)) {
					probabilityForColumn.at(cloneWidth + WidthMove) = 100;
					return cloneWidth + WidthMove;
				} 

			}
		}
	}

	return getMaximum(probabilityForColumn);
}

int SmartBot::EnemyhasChanceForWin(int HeightMove, int WidthMove, BuildGameField * gamefield)
{
	int EnemyWin = 1;
	int cloneWidth = 0;
	int cloneHeight = 0;

	for (int width = 0; width < gamefield->getGamefieldWidth(); width++) {

		for (int height = gamefield->getGamefieldHeight() - 1; height >= 0; height--) {
			EnemyWin = 1;

			cloneHeight = height;
			cloneWidth = width;

			while (cloneWidth < 7 && cloneHeight >= 0 && (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) == 1)) {
	
				EnemyWin++;
				cloneWidth += WidthMove;
				cloneHeight += HeightMove;

				//Wenn vier Steine in einer Reihe waren
				if (cloneWidth >= 0 && cloneWidth < 6 && EnemyWin >= 3 && (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) != 2) && gamefield->getColumnHeights(cloneWidth + WidthMove) == cloneHeight
					|| (cloneWidth >= 0 && cloneWidth < 7 && EnemyWin >= 3 && (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) != 2) && HeightMove != 0)) {
					return cloneWidth + WidthMove;
				}

				if (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) == 2) {
					//Wenn ein gegnerischer Stein über dem eigenen liegt
					EnemyWin = 1;
					break;
				}
			}

		}
	}

	return NoLossDetected;
}

int SmartBot::getMaximum(std::array<int, 7> probabilityForColumn)
{
	int MaximumColumn = 0;
	for (int i = 1; i < 7; i++) {
		if (probabilityForColumn.at(MaximumColumn) < probabilityForColumn.at(i)) {
			MaximumColumn = i;
		}
	}

	if (MaximumColumn == 0 && probabilityForColumn.at(0) == 0) return NoWinDetected;

	return MaximumColumn;
}



