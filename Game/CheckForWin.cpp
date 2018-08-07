#include "stdafx.h"
#include "CheckForWin.h"


CheckForWin::CheckForWin()
{
}


CheckForWin::~CheckForWin()
{
}

bool CheckForWin::checkForWin(BuildGameField *gamefield)
{
	return checkForDiagonalWinRight(gamefield) || checkForHorizontalWin(gamefield) 
		|| checkForVerticalWin(gamefield) || checkForDiagonalWinLeft(gamefield);
}

bool CheckForWin::checkDraw(BuildGameField * gamefield)
{
	//Zählt wie viele Höhen 0 sind (voll aufgefühlt)
	int countZeroHeights = 0;
	for (int i = 0; i < gamefield->getGamefieldWidth(); i++) {
		if (gamefield->getColumnHeights(i) == -1) {
			countZeroHeights++;
		}
	}

	if (countZeroHeights == 7) {
		return true;
	}

	return false;
}

bool CheckForWin::checkForVerticalWin(BuildGameField *gamefield)
{
	return winLogic(NoMoving, 1, gamefield);
}

bool CheckForWin::checkForHorizontalWin(BuildGameField *gamefield)
{
return winLogic(MoveUp, NoMoving, gamefield);
}

bool CheckForWin::checkForDiagonalWinLeft(BuildGameField * gamefield)
{
	return winLogic(MoveUp, MoveLeft, gamefield);
}

bool CheckForWin::checkForDiagonalWinRight(BuildGameField *gamefield)
{
	return winLogic(MoveUp, MoveRight, gamefield);
}

bool CheckForWin::winLogic(int HeightMove, int WidthMove, BuildGameField *gamefield)
{
	int winplayer1 = 1;
	int winplayer2 = 2;

	int cloneWidth = 0;
	int cloneHeight = 0;

	for (int height = gamefield->getGamefieldHeight() -1; height >= 0; height--) {

		for (int width = 0; width < gamefield->getGamefieldWidth(); width++) {

			cloneHeight = height;
			cloneWidth = width;

			winplayer1 = 1;
			winplayer2 = 1;

			while (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight + HeightMove) == 1) {
				if (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) != 1 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight+ HeightMove) != 1) {
					winplayer1 = 1;
					break;
				}
				winplayer1++;
				cloneWidth += WidthMove;
				cloneHeight += HeightMove;

				//Wenn vier Steine in einer Reihe waren
				if (winplayer1 >= 4) return true;
			}

			while (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) == 2 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight+ HeightMove) == 2) {
				if (gamefield->getvalueAtGamefieldpos(cloneWidth, cloneHeight) != 2 && gamefield->getvalueAtGamefieldpos(cloneWidth + WidthMove, cloneHeight+ HeightMove) != 2) {
					winplayer2 = 1;
					break;
				}
				winplayer2++;

				cloneWidth += WidthMove;
				cloneHeight += HeightMove;

				//Wenn vier Steine in einer Reihe waren
				if (winplayer2 >= 4) return true;
			}


		}
	}

	return false;
}


