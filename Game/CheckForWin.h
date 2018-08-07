#pragma once
#include "BuildGameField.h"
#define NoMoving 0
#define MoveLeft -1
#define MoveUp -1
#define MoveRight 1

class CheckForWin
{
public:
	CheckForWin();
	~CheckForWin();

	bool checkForWin(BuildGameField *gamefield);
	bool checkDraw(BuildGameField *gamefield);
private:
	bool checkForVerticalWin(BuildGameField *gamefield);
	bool checkForHorizontalWin(BuildGameField *gamefield);

	//Schaut ob von rechts unten nach rechts oben ein Diagonaler Win vorliegt
	bool checkForDiagonalWinRight(BuildGameField *gamefield);

	//Schaut ob von links unten nach links oben ein Diagonaler Win vorliegt
	bool checkForDiagonalWinLeft(BuildGameField *gamefield);

	bool winLogic(int MinusHeight, int MinusWidth, BuildGameField *gamefield);
};

