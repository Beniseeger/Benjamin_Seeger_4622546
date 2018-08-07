#include "stdafx.h"
#include "LowestColumnBot.h"


LowestColunmBot::LowestColunmBot(int playerid, int icon)
	: Player(playerid, icon)
{
}


LowestColunmBot::~LowestColunmBot()
{
}

int LowestColunmBot::getleastChippedColumn(BuildGameField * gamefield)
{
	int insertinColumn = 0;
	for (int i = 1; i < 7; i++) {
		if (gamefield->getColumnHeights(insertinColumn) < gamefield->getColumnHeights(i)) {
			insertinColumn = i;
		}
	}

	//man muss hier +1 machen, da das Spielfeld zahlen von 1-7 nimmt
	return insertinColumn +1;
}

int LowestColunmBot::getPositionForColumn(BuildGameField * gamefield)
{
	return getleastChippedColumn(gamefield);
}
