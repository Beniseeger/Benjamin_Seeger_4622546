#pragma once
#include "Player.h"
#include "ConsoleOut.h"
#include "ConsoleUtils.h"

class HumanPlayer	: public Player
{
public:
	HumanPlayer(int playerid, int zeichen);
	~HumanPlayer();

	int getPositionForColumn(BuildGameField *gamefield);
private:
	int selectedColumn;
};

