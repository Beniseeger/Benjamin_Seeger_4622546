#pragma once
#include "Player.h"
#define MITTE 4
#define NoWinDetected -1 
#define NoLossDetected -1
#define NoMoving 0
#define MoveLeft -1
#define MoveUp -1
#define MoveRight 1

class SmartBot : public Player
{
public:
	SmartBot(int playerid, int icon);
	~SmartBot();
	
	int getPositionForColumn(BuildGameField *gamefield) override;

private:
	int winningPathHorizontal = 0;
	int loosingPathHorizontal = 0;
	int winningPathVertikalright = 0;
	int winningPathVertikalleft = 0;
	int loosingPathVertikalleft = 0;
	int loosingPathVertikalright = 0;

	std::array<int, 7> probabilityForColumn;
	int winSmartBot = 1; 
	int insertinColumn = 1;

	void setProbabilitysToZero();
	int getMaximum(std::array<int, 7> probabilityForColumn);

	void checkForPossibleWin(BuildGameField *gamefield);
	void checkForPossibleLose(BuildGameField *gamefield);

	int BothasChanceForWin(int MinusHeight, int MinusWidth, BuildGameField *gamefield);
	int EnemyhasChanceForWin(int MinusHeight, int MinusWidth, BuildGameField *gamefield);
};
