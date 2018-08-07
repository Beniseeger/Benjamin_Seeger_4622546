#include "stdafx.h"
#include "LeftRowBot.h"


LeftRowBot::LeftRowBot(int playerid, int icon)
	: Player(playerid, icon)
{
}


LeftRowBot::~LeftRowBot()
{
}


int LeftRowBot::getPositionForColumn(BuildGameField *gamefield)
{
	while (!gamefield->canInsert(insertinColumn)) {
		insertinColumn++;
	}

	//return die column, in der er inserten kann
	return insertinColumn;
}
